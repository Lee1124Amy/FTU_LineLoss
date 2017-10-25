/*
*********************************************************************************************************
*                                              HT6XXX
*                                           Library Function
*
*                                   Copyright 2013, Hi-Trend Tech, Corp.
*                                        All Rights Reserved
*                                         
*
* Project      : HT6xxx
* File         : ht6xxx_flash.c
* By           : Hitrendtech_SocTeam
* Version      : V1.0.1
* Description  : 
*********************************************************************************************************
*/

#define  __HT6XXX_FLASH_C

#include "ht6xxx_flash.h"

/*
*********************************************************************************************************
*                                           ���غ�/�ṹ��
*********************************************************************************************************
*/

#define M8(adr)     (*((uint8_t * ) (adr)))
#define M16(adr)    (*((uint16_t *) (adr)))
#define M32(adr)    (*((uint32_t *) (adr)))

static const uint32_t RegisterWriteProtect[]={CMU_WPREG_Protected, CMU_WPREG_UnProtected};

/*
*********************************************************************************************************
*                                             ���ر���
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           ���غ�������
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FLASH BYTE WRITE
*
* ����˵��: Flash�ֽ�д
*
* ��ڲ���: pWriteByte    ָ��д���ݵ��׵�ַ
*
*           Address       ���ݽ�Ҫд��Flash�ĵ�ַ
*
*           Num           д���ݳ��ȣ����ֽ�Ϊ��λ
*
* ���ز���: ��                                      
* 
* ����˵��: �û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*********************************************************************************************************
*/
void HT_Flash_ByteWrite(const uint8_t* pWriteByte, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
    
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_UnLocked;                            /*!< Flash����              */
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_WRITE;                             /*!< Flashд                */
    
    for(i=0; i<Num; i++)
    {
        M8(Address+i) = pWriteByte[i];                                     /*!< ִ��Flashд            */
        while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                       /*!< �ȴ�д���             */
    }
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
} 

/*
*********************************************************************************************************
*                                         FLASH BYTE READ
*
* ����˵��: Flash�ֽڶ�
*
* ��ڲ���: pReadByte     ָ��洢���������ݵ��׵�ַ
*
*           Address       ��Flash���׵�ַ
*
*           Num           �����ݳ��ȣ����ֽ�Ϊ��λ
*
* ���ز���: ��                                      
* 
* ����˵��: �û���ע��������ݲ�Ҫ��������ķ�Χ���Է����
*********************************************************************************************************
*/
void HT_Flash_ByteRead(uint8_t* pReadByte, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    
    for(i=0; i<Num; i++)
    {
        pReadByte[i] = M8(Address+i);                                      /*!< ִ��Flash��            */
    }
     
} 

/*
*********************************************************************************************************
*                                         FLASH HALF WORD WRITE
*
* ����˵��: Flash����д
*
* ��ڲ���: pWriteHalfWord    ָ��д���ݵ��׵�ַ
*
*           Address           ���ݽ�Ҫд��Flash�ĵ�ַ
*
*           Num               д���ݳ��ȣ��԰���Ϊ��λ
*
* ���ز���: ��                                      
* 
* ����˵��: 1)�û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*           2)�û�Ӧ��֤���ݸ������ĵ�ַΪ���ٰ��ֶ���  
*********************************************************************************************************
*/
void HT_Flash_HalfWordWrite(const uint16_t* pWriteHalfWord, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
    
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_UnLocked;                            /*!< Flash����              */
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_WRITE;                             /*!< Flashд                */
    
    Address &= 0xFFFFFFFE;                                                 /*!< ��֤���ֶ���           */
    for(i=0; i<Num; i++)
    {
        M16(Address+i*2) = pWriteHalfWord[i];                              /*!< ִ��Flashд            */
        while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                       /*!< �ȴ�д���             */
    }
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
}

/*
*********************************************************************************************************
*                                         FLASH HALF WORD READ
*
* ����˵��: Flash���ֶ�
*
* ��ڲ���: pReadHalfWord ָ��洢���������ݵ��׵�ַ
*
*           Address       ��Flash���׵�ַ
*
*           Num           �����ݳ��ȣ��԰���Ϊ��λ
*
* ���ز���: ��                                      
* 
* ����˵��: 1)�û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*           2)�û�Ӧ��֤���ݸ������ĵ�ַΪ���ٰ��ֶ���  
*********************************************************************************************************
*/
void HT_Flash_HalfWordRead(uint16_t* pReadHalfWord, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    Address &= 0xFFFFFFFE;                                                 /*!< ��֤���ֶ���           */
    for(i=0; i<Num; i++)
    {
        pReadHalfWord[i] = M16(Address+i*2);                               /*!< ִ��Flash��            */
    }
     
}

/*
*********************************************************************************************************
*                                         FLASH WORD WRITE
*
* ����˵��: Flash��д
*
* ��ڲ���: pWriteWord    ָ��д���ݵ��׵�ַ
*
*           Address       ���ݽ�Ҫд��Flash�ĵ�ַ
*
*           Num           д���ݳ��ȣ�����Ϊ��λ 
*
* ���ز���: ��                                      
* 
* ����˵��: 1)�û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*           2)�û�Ӧ��֤���ݸ������ĵ�ַΪ�����ֶ���
*********************************************************************************************************
*/
void HT_Flash_WordWrite(const uint32_t* pWriteWord, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
    
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_UnLocked;                            /*!< Flash����              */
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_WRITE;                             /*!< Flashд                */
    
    Address &= 0xFFFFFFFC;                                                 /*!< ��֤�ֶ���             */   
    for(i=0; i<Num; i++)
    {
        M32(Address+i*4) = pWriteWord[i];                                  /*!< ִ��Flashд            */
        while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                       /*!< �ȴ�д���             */
    }
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
}

/*
*********************************************************************************************************
*                                         FLASH WORD READ
*
* ����˵��: Flash�ֶ�
*
* ��ڲ���: pReadWord     ָ��洢���������ݵ��׵�ַ
*
*           Address       ��Flash���׵�ַ
*
*           Num           �����ݳ��ȣ�����Ϊ��λ
*
* ���ز���: ��                                      
* 
* ����˵��: 1)�û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*           2)�û�Ӧ��֤���ݸ������ĵ�ַΪ�����ֶ���
*********************************************************************************************************
*/
void HT_Flash_WordRead(uint32_t* pReadWord, uint32_t Address, uint32_t Num)
{
    /*  assert_param  */
    
    uint32_t i;
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    Address &= 0xFFFFFFFC;                                                 /*!< ��֤�ֶ���             */     
    for(i=0; i<Num; i++)
    {
        pReadWord[i] = M32(Address+i*4);                                   /*!< ִ��Flash��            */
    }
     
}

/*
*********************************************************************************************************
*                                         FLASH PAGE ERASE
*
* ����˵��: Flashҳ����
*
* ��ڲ���: EraseAddress    ҳ������ַ
*
* ���ز���: ��                                      
* 
* ����˵��: �û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬���䣬1K bytes/page
*********************************************************************************************************
*/
void HT_Flash_PageErase(uint32_t EraseAddress)
{
    /*  assert_param  */
    
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
    
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_UnLocked;                            /*!< Flash����              */
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_PAGEERASE;                         /*!< Flashҳ����            */  
    
    EraseAddress &= 0xFFFFFFFC;                                            /*!< ��֤�ֶ���             */
    M32(EraseAddress) = 0xFF;                                              /*!< ִ��Flashҳ����        */
    while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                           /*!< �ȴ�д���             */

    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
}

/*
*********************************************************************************************************
*                                         FLASH CHIP ERASE
*
* ����˵��: Flashȫ����
*
* ��ڲ���: ��
*
* ���ز���: ��                                      
* 
* ����˵��: �û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬����
*********************************************************************************************************
*/
void HT_Flash_ChipErase(void)
{
    /*  assert_param  */
    
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
    
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_UnLocked;                            /*!< Flash����              */
    
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_CHIPERASE;                         /*!< Flashҳ����            */  

    M32(0x1000) = 0xFF;                                                    /*!< ִ��Flashȫ����        */
    while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                           /*!< �ȴ�д���             */

    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
}

#if defined  HT502x
/*
*********************************************************************************************************
*                                         FLASH PAGE ERASE WITH SECTION UNLOCK
*
* ����˵��: Flashҳ����(��Section����)
*
* ��ڲ���: EraseAddress    ҳ������ַ
*
* ���ز���: ��                                      
* 
* ����˵��: �û�Ӧ��֤����ִ�й����мĴ���д����״̬�Լ�Flash����״̬���䣬1K bytes/page
*********************************************************************************************************
*/
void HT_Flash_PageEraseWithSectionUnlock(uint32_t EraseAddress)
{
    /*  assert_param  */
    
    uint32_t writeProtect = RegisterWriteProtect[HT_CMU->WPREG & 0x01];    /*!< ���浱ǰд����״̬     */
    
    HT_CMU->WPREG = CMU_WPREG_UnProtected;                                 /*!< �ر�д��������         */
	
	  if (EraseAddress <= 0x00001FFF )                                        /*!< Flash����              */
		{
			 HT_CMU->FS1LOCK = CMU_FS1LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00002000) && (EraseAddress <= 0x00007FFF ))
		{
			 HT_CMU->FS2LOCK = CMU_FS2LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00008000) && (EraseAddress <= 0x0000FFFF ))
		{
			 HT_CMU->FS3LOCK = CMU_FS3LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00010000) && (EraseAddress <= 0x00017FFF ))
		{
			 HT_CMU->FS4LOCK = CMU_FS4LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00018000) && (EraseAddress <= 0x0001FBFF ))
		{
			 HT_CMU->FS5LOCK = CMU_FS5LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x0001FC00) && (EraseAddress <= 0x0001FFFF ))
		{
			 HT_CMU->FSALOCK = CMU_FSALOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00020000) && (EraseAddress <= 0x00027FFF ))
		{
			 HT_CMU->FS6LOCK = CMU_FS6LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00028000) && (EraseAddress <= 0x0002FFFF ))
		{
			 HT_CMU->FS7LOCK = CMU_FS7LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00030000) && (EraseAddress <= 0x00037FFF ))
		{
			 HT_CMU->FS8LOCK = CMU_FS8LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x00038000) && (EraseAddress <= 0x0003FBFF ))
		{
			 HT_CMU->FS9LOCK = CMU_FS9LOCK_UnLocked;
		}
		else if ((EraseAddress >= 0x0003FC00) && (EraseAddress <= 0x0003FFFF ))
		{
			 HT_CMU->FSBLOCK = CMU_FSBLOCK_UnLocked;
		}
				
    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_PAGEERASE;                         /*!< Flashҳ����            */  
    
    EraseAddress &= 0xFFFFFFFC;                                            /*!< ��֤�ֶ���             */
    M32(EraseAddress) = 0xFF;                                              /*!< ִ��Flashҳ����        */
    while(HT_CMU->FLASHCON & CMU_FLASHCON_BUSY);                           /*!< �ȴ�д���             */

    HT_CMU->FLASHCON = CMU_FLASHCON_FOP_READ;                              /*!< Flash��                */
    HT_CMU->FLASHLOCK = CMU_FLASHLOCK_Locked;                              /*!< Flash����              */
    
    HT_CMU->WPREG = writeProtect;                                          /*!< �ָ�֮ǰд��������     */
     
}
#endif

