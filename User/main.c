#include <math.h>

#include <stdio.h>

#include <string.h>

#include "ht6xxx_reset.h"

#include "TypeMeter.h"

#include "TypeRAM.h"

//#include <stdlib.h>

#include "TypeE2p.h"

//#include "msp430x54x.h"

//#include "In430.h"

#include "ht6xxx_lib.h"

//#include "DLT698.h"					

#include "Port.h"

#include "TypeFRAM.h"

#include "TypeFlash.h"

#include "Data.h"

#include "Interrupt.h"

#include "General.h"

#include "Time.h"

#include "Mem.h"

#include "Power.h"

#include "Initial.h"

#include "serial.h"

#include "IEC101.h"



#define EC_E2_W E2P_WAdj

#define EC_E2_R E2P_RAdj



short Get_CEVENT(int ch,int No,unsigned char *buf)

{

  if(ReadRecord(CEVENT0_USEADDR+ch*6,buf,No)==0)

    return ONE_RECORD_LEN;

  else

    return 0;

}

short Save_CEVENT(int ch)

{

  unsigned int i,year;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  

  if(Get_CEVENT(ch,0,tmp_buf))

    memcpy(&i,tmp_buf+6,4);

  else

  {

    i=0;

  }

  ++i;

  MoveCurrentTimeBCD_Hex();

  tmp_buf[0]=Clk.SecH;

  tmp_buf[1]=Clk.MinH;

  tmp_buf[2]=Clk.HourH;

  tmp_buf[3]=Clk.DayH;

  tmp_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  tmp_buf[5]=year-2000;

  memcpy(tmp_buf+6,&i,4);

  LoadRecord(CEVENT0_USEADDR+ch*6,tmp_buf);

  return 0;

}



int CEVENT_Record_Num(ch)

{

  int Num;

  Num = Get_Record_Num(CEVENT0_USEADDR+ch*6);

  return Num;

}





short Get_JIAOSHI(int No,unsigned char *buf)

{

  if(ReadRecord(TIME_USEADDR,buf,No)==0)

    return ONE_RECORD_LEN;

  else

    return 0;

}

short Save_JIAOSHI(unsigned char *Time_buf)

{

  unsigned int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  if(Get_JIAOSHI(0,tmp_buf))

    memcpy(&i,tmp_buf+6,4);

  else

  {

    i=0;

  }

  ++i;

  memcpy(tmp_buf,Time_buf,6);

  memcpy(tmp_buf+6,&i,4);

  LoadRecord(TIME_USEADDR,tmp_buf);

  return 0;

}



int JIAOSHI_Record_Num()

{

  int Num;

  Num = Get_Record_Num(TIME_USEADDR);

  return Num;

}





void Clear_Save(int ch)

{

  unsigned short m_e2_ptr,m_e2_buf,year;

  unsigned char ptr_buf[4],tmp_buf[64];

  MoveCurrentTimeBCD_Hex();

  tmp_buf[0]=Clk.SecH;

  tmp_buf[1]=Clk.MinH;

  tmp_buf[2]=Clk.HourH;

  tmp_buf[3]=Clk.DayH;

  tmp_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  tmp_buf[5]=year-2000;

  memcpy(tmp_buf+10,&Energy_Data[ch],ONE_RECORD_LEN-6);

  LoadRecord(CH0_CLR_USEADDR+ch*48,tmp_buf);

}



int GetClear_num(int ch)

{

  int Num;

  Num = Get_Record_Num(CH0_CLR_USEADDR+ch*48);

  return Num;

}



int GetClear_Record(int ch,int No,unsigned char *buf)

{

  if(ReadRecord(CH0_CLR_USEADDR+ch*48,buf,No))

    return 0;

  return 88;

}

//第一个字节指针

//第二个字节数量

void Pn_Event_Save(int ch,int phase,unsigned char flag)

{

  unsigned short m_e2_ptr,m_e2_buf,year;

  unsigned char ptr_buf[4],tmp_buf[48];

  MoveCurrentTimeBCD_Hex();

  tmp_buf[0]=Clk.SecH;

  tmp_buf[1]=Clk.MinH;

  tmp_buf[2]=Clk.HourH;

  tmp_buf[3]=Clk.DayH;

  tmp_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  tmp_buf[5]=year-2000;

  

  if(flag)

  {

    memcpy(tmp_buf+6,&SM.PQNum[ch][phase],4);

    memcpy(tmp_buf+10,&Energy_Data[ch],32);

    LoadRecord(CH0_PAP_USEADDR+ch*78+phase*3,tmp_buf);

  }

  else

  {

    memcpy(tmp_buf+6,&Energy_Data[ch],32);

    LoadRecord(CH0_PAN_USEADDR+ch*78+phase*3,tmp_buf);

  }

}



int GetPn_Event_num(int ch,int phase)

{

  int Num;

  Num = Get_Record_Num(CH0_PAP_USEADDR+ch*78+phase*3);

  return Num;

}



int GetPn_Event_Record(int ch,int phase,int No,unsigned char *buf)

{

  if(ReadRecord(CH0_PAP_USEADDR+ch*78+phase*3,buf,No))

    return 0;

  ReadRecord(CH0_PAN_USEADDR+ch*78+phase*3,buf+42,No);

  return 88;

}



void Pt_Event_Save(int ch)
{
  unsigned short m_e2_ptr,m_e2_buf,year;
  unsigned char ptr_buf[4],tmp_buf[48];
  MoveCurrentTimeBCD_Hex();
  tmp_buf[0]=Clk.SecH;
  tmp_buf[1]=Clk.MinH;

  tmp_buf[2]=Clk.HourH;

  tmp_buf[3]=Clk.DayH;

  tmp_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  tmp_buf[5]=year-2000;

  SM.PQNum[ch][3]++;

  memcpy(tmp_buf+6,&SM.PQNum[ch][3],4);

  memcpy(tmp_buf+10,&Energy_Data[ch],32);

  LoadRecord(CH0_PTD_USEADDR+ch*78,tmp_buf);
  if(SM.CalibCount != CALIBCOUNT1)
  {
    Insert_Push(TREND_TYPE,ch);
  }

}



int GetPt_Event_num(int ch)

{

  int Num;

  Num = Get_Record_Num(CH0_PTD_USEADDR+ch*78);

  return Num;

}



int GetPt_Event_Record(int ch,int No,unsigned char *buf)

{

  if(ReadRecord(CH0_PTD_USEADDR+ch*78,buf,No))

    return 0;

  return 42;

}



short Save_Data(unsigned char *Time_buf)

{

  int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  memcpy(tmp_buf,Time_buf,6);

  for(i=0;i<MAX_CH_NUM;++i)

  {

    if(SM.CalibCount != CALIBCOUNT1)

    {

      Insert_Push(LOAR_TYPE,i);

    }

    memcpy(tmp_buf+6,&Energy_Data[i],ONE_RECORD_LEN-6);

    LoadRecord(LOAD0_USEADDR+i*30,tmp_buf);

  }

  return 0;

}



short Get_LoadData(int No,int ch,unsigned char *buf)

{

  if(ch>MAX_CH_NUM)

    return 0;

  ReadRecord(LOAD0_USEADDR+30*ch,buf,No);

  return ONE_RECORD_LEN;

}



int Load_Record_Num()

{

  int Num;

  Num = Get_Record_Num(LOAD0_USEADDR);

  return Num;

}



short Read_LastData(int ch,unsigned char *buf)

{

  if(ch>MAX_CH_NUM)

    return 0;

  ReadRecord(LOAD0_USEADDR+30*ch,buf,0);

  return ONE_RECORD_LEN;

}



short Save_DayData(unsigned char *Time_buf)

{

  int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  memcpy(tmp_buf,Time_buf,6);  

  for(i=0;i<MAX_CH_NUM;++i)

  {

    memcpy(tmp_buf+6,&Energy_Data[i],ONE_RECORD_LEN-6);

    LoadRecord(FRZD0_USEADDR+i*30,tmp_buf);

  }

  return 0;

}



short Get_DayData(int No,int ch,unsigned char *buf)

{

  if(ch>MAX_CH_NUM)

    return 0;

  ReadRecord(FRZD0_USEADDR+30*ch,buf,No);

  return ONE_RECORD_LEN;

}

void compensate_day()

{

 unsigned char tmp_buf[ONE_RECORD_SIZE]; 

 unsigned char time_buf[8];

 int year;

 int i,j,k;

 for(i=0;i<MAX_CH_NUM;++i)

 {
  if(Day_Record_Num()==0)
     break;
   ReadRecord(FRZD0_USEADDR+30*i,tmp_buf,0);

   memcpy(time_buf,tmp_buf,6); 
   tmp_buf[0] = 0;
   tmp_buf[1] = 0;
   tmp_buf[2] = 0;
   tmp_buf[3] = Clk.DayH;

   tmp_buf[4] = Clk.Month;

   year = Clk.YearH;

   year = year*256 + Clk.YearL;

   tmp_buf[5]=year-2000;

   for(j=0;j<7;++j)

   {

     if((tmp_buf[3] == time_buf[3]) && (tmp_buf[4] == time_buf[4]) && (tmp_buf[5] == time_buf[5]))

     {

       break;

     }

     --tmp_buf[3];

     if(tmp_buf[3]==0)

     {

       --tmp_buf[4];

       if(tmp_buf[4]==0)

       {

         tmp_buf[4] = 12;

         --tmp_buf[5];

       }

       if((tmp_buf[4]==2) && (tmp_buf[5]%4==0))

        tmp_buf[3] = 29;

       else

        tmp_buf[3] = MonTab[tmp_buf[4]]; 

     }

   }



   for(j=0;j<7;++j)

   {

     if((tmp_buf[3] == Clk.DayH) && (tmp_buf[4] == Clk.Month) && (tmp_buf[5] == (year-2000)))

     {

       break;

     }

     ++tmp_buf[3];

     if(tmp_buf[3] > (((tmp_buf[4]==2 ) && ((tmp_buf[5]%4)==0))? 29:MonTab[tmp_buf[4]]))

     {

       tmp_buf[3]=1;

       ++tmp_buf[4];

       if(tmp_buf[4]>12)

       {

         tmp_buf[4] = 1;

         ++tmp_buf[5];

       }

     }	

     LoadRecord(FRZD0_USEADDR+i*30,tmp_buf);

   }

 }

}



int Day_Record_Num()

{

  int Num;

  Num = Get_Record_Num(FRZD0_USEADDR);

  return Num;

}



short Save_HourData(unsigned char *Time_buf)

{

  int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  memcpy(tmp_buf,Time_buf,6);  

  for(i=0;i<MAX_CH_NUM;++i)

  {

    memcpy(tmp_buf+6,&Energy_Data[i],ONE_RECORD_LEN-6);

    LoadRecord(SHRP0_USEADDR+i*30,tmp_buf);

  } 

  return 0;

}



short Get_HourData(int No,int ch,unsigned char *buf)

{

  if(ch>MAX_CH_NUM)

    return 0;

  ReadRecord(SHRP0_USEADDR+30*ch,buf,No);

  return ONE_RECORD_LEN;

}



int Hour_Record_Num()

{       

  int Num;

  Num = Get_Record_Num(SHRP0_USEADDR);

  return Num;

}



short Save_MonthData(unsigned char *Time_buf)

{

  int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  memcpy(tmp_buf,Time_buf,6);  

  for(i=0;i<MAX_CH_NUM;++i)

  {

    memcpy(tmp_buf+6,&Energy_Data[i],E2ONE_RECORD_LEN-6);

    LoadRecord(MOND0_USEADDR+i*30,tmp_buf);

  } 

  return 0;

}



short Get_MonthData(int No,int ch,unsigned char *buf)

{

  if(ch>8)

    return 0;

  ReadRecord(MOND0_USEADDR+30*ch,buf,No);

  return E2ONE_RECORD_LEN;

}





void compensate_month()

{

 unsigned char tmp_buf[ONE_RECORD_SIZE]; 

 unsigned char time_buf[8];

 int year;

 int i,j,k;

 for(i=0;i<MAX_CH_NUM;++i)

 {
  if(Month_Record_Num()==0)
     break;
   ReadRecord(MOND0_USEADDR+30*i,tmp_buf,0);

   memcpy(time_buf,tmp_buf,6); 

   tmp_buf[0] = 0;
   tmp_buf[1] = 0;
   tmp_buf[2] = 0;
   tmp_buf[3] = 1;//Clk.DayH;

   tmp_buf[4] = Clk.Month;

   year = Clk.YearH;

   year = year*256 + Clk.YearL;

   tmp_buf[5]=year-2000;

   for(j=0;j<12;++j)

   {

     if((tmp_buf[4] == time_buf[4]) && (tmp_buf[5] == time_buf[5]))

     {

       break;

     }

     --tmp_buf[4];

     if(tmp_buf[4]==0)

     {

       tmp_buf[4] = 12;

       --tmp_buf[5];

     }

   }

   memcpy(tmp_buf+6,&Energy_Data[i],E2ONE_RECORD_LEN-6);

   for(j=0;j<12;++j)

   {

     if((tmp_buf[4] == Clk.Month) && (tmp_buf[5] == (year-2000)))

     {

       break;

     }

     ++tmp_buf[4];

     if(tmp_buf[4]>12)

     {

       tmp_buf[4] = 1;

       ++tmp_buf[5];

     }	

     LoadRecord(MOND0_USEADDR+i*30,tmp_buf);

   }

 }

}





int Month_Record_Num()

{

  int Num;

  Num = Get_Record_Num(MOND0_USEADDR);

  return Num;

}



short Save_RandData(unsigned char *Time_buf)

{

  int i;

  unsigned char tmp_buf[64];  //秒、分、时、日、月、年、记录 

  memcpy(tmp_buf,Time_buf,6);  

  for(i=0;i<MAX_CH_NUM;++i)

  {

    memcpy(tmp_buf+6,&Energy_Data[i],E2ONE_RECORD_LEN-6);

    LoadRecord(RAND0_USEADDR+i*30,tmp_buf);

  } 

  return 0;

}

short Get_RandData(int No,int ch,unsigned char *buf)

{

  if(ch>MAX_CH_NUM)

    return 0;

  ReadRecord(RAND0_USEADDR+30*ch,buf,No);

  return E2ONE_RECORD_LEN;

}

int Rand_Record_Num()

{

  int Num;

  Num = Get_Record_Num(RAND0_USEADDR);

  return Num;

}



  

    

int Get_LoadFile_Msg_Len(void)

{

  int Len,rec_ptr;

  rec_ptr=Load_Record_Num();

  Len = 51+rec_ptr*189; 

  return Len; 

}



int Get_LoadFile_Xml_Len(void)

{

  int Len,rec_ptr;

  rec_ptr=Load_Record_Num();

  Len = 100+rec_ptr*256; 

  return Len; 

}



void Save_ECRamBufAds()

{

  int i;

  unsigned short* ECRamBufAdsPtr;

  unsigned char* ECRamBufChkAdsPtr;

  unsigned short ECEAds;

  

  for( i=0;i<ECUnitNum;++i)

  {

    ECRamBufAdsPtr = ECRgTab[i].ECRamBufAds;

    ECRamBufChkAdsPtr = ECRgTab[i].ECRamBufChkAds;

    ECEAds = ECRgTab[i].ECFAds;

    if( *ECRamBufChkAdsPtr == ChkNum( (unsigned char*)ECRamBufAdsPtr, 2 ) )

    {

      EC_E2_W(ECEAds,(unsigned char*)ECRamBufAdsPtr,2);

    }

  }

}



void ReLoad_ECRamBufAds()

{

  int i;

  unsigned short* ECRamBufAdsPtr;

  unsigned char* ECRamBufChkAdsPtr;

  unsigned short ECEAds;

  

  for( i=0;i<ECUnitNum;++i)

  {

    ECRamBufAdsPtr = ECRgTab[i].ECRamBufAds;

    ECRamBufChkAdsPtr = ECRgTab[i].ECRamBufChkAds;

    ECEAds = ECRgTab[i].ECFAds;

    EC_E2_R((unsigned char*)ECRamBufAdsPtr,ECEAds,2);

    *ECRamBufChkAdsPtr = ChkNum( (unsigned char*)ECRamBufAdsPtr, 2 );

  }

}



void EC_MeasA(void)

{

  int i;

  unsigned short* ECRamBufAdsPtr;

  unsigned char* ECRamBufChkAdsPtr;

  unsigned long* ECRAds;

  unsigned short ECEAds;

  unsigned int Ps2;

  Ps2 = MSpec.RMeterConst/EN_DOTS;

  for( i=0;i<ECUnitNum;++i)

  {

    ECRamBufAdsPtr = ECRgTab[i].ECRamBufAds;

    ECRamBufChkAdsPtr = ECRgTab[i].ECRamBufChkAds;

    ECRAds = ECRgTab[i].ECRAds;

    if( *ECRamBufChkAdsPtr != ChkNum( (unsigned char*)ECRamBufAdsPtr, 2 ) )

    {

      *ECRamBufAdsPtr = 0;

      *ECRamBufChkAdsPtr = 0;

    }

    if(*ECRamBufAdsPtr>=Ps2)

    {

      *ECRAds += (*ECRamBufAdsPtr/Ps2);//*ECRamBufAdsPtr;

      ECEAds = ECRgTab[i].ECEAds;

      EC_E2_W(ECEAds,(unsigned char*)ECRAds,4);

      *ECRamBufAdsPtr %= Ps2;

      *ECRamBufChkAdsPtr = ChkNum((unsigned char*)ECRamBufAdsPtr,2);

    }

  }

}

void EC_ClearA(void)

{

  int i;

  unsigned long* ECRAds;

  unsigned short ECEAds;

  unsigned char tmpbuf[8];

  memset(tmpbuf,0,8);

  for( i=0;i<ECUnitNum;++i)

  {

    ECRAds = ECRgTab[i].ECRAds;

    ECEAds = ECRgTab[i].ECEAds;

    EC_E2_W(ECEAds,tmpbuf,4);

    *ECRAds = 0;

  }

}

void Read_E2R()

{

  int i;

  unsigned long* ECRAds;

  unsigned short ECEAds;

  for( i=0;i<ECUnitNum;++i)

  {

    ECRAds = ECRgTab[i].ECRAds;

    ECEAds = ECRgTab[i].ECEAds;

    EC_E2_R((unsigned char*)ECRAds,ECEAds,4);

  }

}



void Clear_E2R(int chan)

{

  int i,j;

  unsigned long* ECRAds;

  unsigned short ECEAds;

  unsigned char tmpbuf[8];

  memset(tmpbuf,0,8);

  if(chan==0)

  {

    chan=ECUnitNum;

    for(i=0;i<MAX_CH_NUM;++i)

    {

      Clear_Save(i);

    }

    i = 0; 

  }

  else

  {

    Clear_Save(chan-1);

    i = 8*(chan-1);

    chan = 8*chan;

  }

  while(i<chan)

  {

    ECRAds = ECRgTab[i].ECRAds;

    ECEAds = ECRgTab[i].ECEAds;

    EC_E2_W(ECEAds,tmpbuf,4);

    *ECRAds = 0;

    ++i;

  }

}



void Clear_EVTC(int chan)

{

  int i;

  unsigned char ptr_buf[4];

  memset(ptr_buf,0,4);

  if(chan==0)

  {

    chan=48*MAX_CH_NUM;

    i = 0; 

  }

  else

  {

    i = 48*(chan-1);

    chan = 48*chan;

  }

  while(i<chan)

  {

    EC_E2_W(CH0_PAP_USEADDR+3*i,ptr_buf,2);

    ++i;

  }

}



void Clear_EVT2R(int chan)

{

  int i;

  unsigned char ptr_buf[4];

  memset(ptr_buf,0,4);

  if(chan==0)

  {

    chan=16*MAX_CH_NUM;

    for(i=0;i<MAX_CH_NUM;++i)

    {

      Save_CEVENT(i);

    }

    i = 0; 

  }

  else

  {

    Save_CEVENT(chan-1);

    i = 16*(chan-1);

    chan = 16*chan;

  }

  while(i<chan)

  {

    if((i+1)%8)

      EC_E2_W(CH0_PAP_USEADDR+3*i,ptr_buf,2);

    ++i;

  }

}



void Read_E2R1()

{

  int i;

  unsigned char ptr_buf[4];

  memset(ptr_buf,0,4);

  for( i=0;i<26*MAX_CH_NUM;++i)

  {

    EC_E2_W(LOAD0_USEADDR+3*i,ptr_buf,2);

  }

}

void ProcThirdSec(void)
{
  unsigned int tmp_p;
  short Quad;
  unsigned long Ps2;
  Flag.Clk &= ~F_ThirdSec;
  if((Flag.Power & F_PwrUp) == 0)
      return;
  if(SM.sigle_pt)
  {
      //Ps2 = MSpec.RMeterConst/10000;
      //Ps2=230400000000/MSpec.RMeterConst;  //1/64s
       Ps2=MSpec.RMeterConst/1000;
       Ps2=3600000000/Ps2;   //1ms
      if(Real_Data[0].Pt>20)
      {
        //tmp_p = 7200000/Real_Data[0].Pt;
        //tmp_p = 360000000/Real_Data[0].Pt;
        //tmp_p = 5625000/Real_Data[0].Pt;
        //tmp_p = 16875000/Real_Data[0].Pt;
        //tmp_p = 56250*MSpec.RMeterConst/Real_Data[0].Pt;
        tmp_p=Ps2/Real_Data[0].Pt;
        //SM.pplus++;
        if(SM.pplus>=tmp_p)
        {
          NVIC_DisableIRQ(TIMER_0_IRQn);
          SM.pplus -= tmp_p;
          NVIC_EnableIRQ(TIMER_0_IRQn);
          //SM.pplus = 0;
          ECP.PL_CumPp[0] += 1;
          ECP.PL_ChkPp[0]=ChkNum((unsigned char*)&ECP.PL_CumPp[0],2);
        }
      }
      if(Real_Data[0].Pt<-20)
      {
        //tmp_p = 7200000/(Real_Data[0].Pt*-1);
        //tmp_p = 16875000/(Real_Data[0].Pt*-1);
        tmp_p=Ps2/(Real_Data[0].Pt*-1);
        //SM.pplus++;
        if(SM.pplus>=tmp_p)
        {
          NVIC_DisableIRQ(TIMER_0_IRQn);
          SM.pplus -= tmp_p;
          NVIC_EnableIRQ(TIMER_0_IRQn);
          //SM.pplus = 0;
          ECP.PL_CumPn[0] += 1;
          ECP.PL_ChkPn[0]=ChkNum((unsigned char*)&ECP.PL_CumPn[0],2);
        }
      }
      if(Real_Data[0].Qt>20)
      {
        //tmp_p = 7200000/Real_Data[0].Qt;
       tmp_p=Ps2/(Real_Data[0].Qt);
        //SM.qplus++;
        if(SM.qplus>=tmp_p)
        {
          //SM.qplus = 0;
          NVIC_DisableIRQ(TIMER_0_IRQn);
          SM.qplus -= tmp_p;
          NVIC_EnableIRQ(TIMER_0_IRQn);
          ECP.PL_CumQp[0] += 1;
          ECP.PL_ChkQp[0]=ChkNum((unsigned char*)&ECP.PL_CumQp[0],2);
          if(Real_Data[0].Pt>0)
          {
            ECP.PL_CumQ[0][0] += 1;
            ECP.PL_ChkQ[0][0]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][0],2);
          }
          else
          {
            ECP.PL_CumQ[0][1] += 1;
            ECP.PL_ChkQ[0][1]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][1],2);
          }
        }
      }
      if(Real_Data[0].Qt<-20)
      {
        //tmp_p = 7200000/(Real_Data[0].Qt*-1);
        tmp_p=Ps2/(Real_Data[0].Qt*-1);
        //SM.qplus++;
        if(SM.qplus>=tmp_p)
        {
         // SM.qplus = 0;
          NVIC_DisableIRQ(TIMER_0_IRQn);
          SM.qplus -= tmp_p;
          NVIC_EnableIRQ(TIMER_0_IRQn);
          ECP.PL_CumQn[0] += 1;
          ECP.PL_ChkQn[0]=ChkNum((unsigned char*)&ECP.PL_CumQn[0],2);
          if(Real_Data[0].Pt>0)
          {
            ECP.PL_CumQ[0][3] += 1;
            ECP.PL_ChkQ[0][3]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][3],2);
          }
          else
          {
            ECP.PL_CumQ[0][2] += 1;
            ECP.PL_ChkQ[0][2]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][2],2);
          }
        }
      }
  }
}

void ProcHalfSec(void)
{
  int i;
  unsigned int tmp_p;
  short Quad;
  unsigned int Ps2;
  Flag.Clk &= ~F_HalfSec;
  if((Flag.Power & F_PwrUp) == 0)
      return;

  HT_GPIO_BitsToggle(HT_GPIOA,GPIO_Pin_4);
  
  //if(((Real_Data[0].Ua>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Uc<80)) || ((Real_Data[0].Uc>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Ua<80)))
  if(SM.sigle_pt)
  {
#if 0   
      Ps2 = MSpec.RMeterConst/10000;
      if(Real_Data[0].Pt>20)
      {
        //tmp_p = 7200000/Real_Data[0].Pt;
        //tmp_p = 360000000/Real_Data[0].Pt;
        tmp_p = 5625000/Real_Data[0].Pt;
        //SM.pplus++;
        if(SM.pplus>=tmp_p)
        {
          SM.pplus -= tmp_p;
          ECP.PL_CumPp[0] += Ps2;
          ECP.PL_ChkPp[0]=ChkNum((unsigned char*)&ECP.PL_CumPp[0],2);
        }
      }
      if(Real_Data[0].Pt<-20)
      {
        //tmp_p = 7200000/(Real_Data[0].Pt*-1);
        tmp_p = 5625000/(Real_Data[0].Pt*-1);
        //SM.pplus++;
        if(SM.pplus>=tmp_p)
        {
          SM.pplus -= tmp_p;
          ECP.PL_CumPn[0] += Ps2;
          ECP.PL_ChkPn[0]=ChkNum((unsigned char*)&ECP.PL_CumPn[0],2);
        }
      }
      if(Real_Data[0].Qt>20)
      {
        //tmp_p = 7200000/Real_Data[0].Qt;
        tmp_p = 5625000/Real_Data[0].Qt;
        //SM.qplus++;
        if(SM.qplus>=tmp_p)
        {
          //SM.qplus = 0;
          SM.qplus -= tmp_p;
          ECP.PL_CumQp[0] += Ps2;
          ECP.PL_ChkQp[0]=ChkNum((unsigned char*)&ECP.PL_CumQp[0],2);
          if(Real_Data[0].Pt>0)
          {
            ECP.PL_CumQ[0][0] += Ps2;
            ECP.PL_ChkQ[0][0]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][0],2);
          }
          else
          {
            ECP.PL_CumQ[0][1] += Ps2;
            ECP.PL_ChkQ[0][1]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][1],2);
          }
        }
      }
      if(Real_Data[0].Qt<-20)
      {
        //tmp_p = 7200000/(Real_Data[0].Qt*-1);
        tmp_p = 5625000/(Real_Data[0].Qt*-1);;
        //SM.qplus++;
        if(SM.qplus>=tmp_p)
        {
          //SM.qplus = 0;
          SM.qplus -= tmp_p;
          ECP.PL_CumQn[0] += Ps2;
          ECP.PL_ChkQn[0]=ChkNum((unsigned char*)&ECP.PL_CumQn[0],2);
          if(Real_Data[0].Pt>0)
          {
            ECP.PL_CumQ[0][3] += Ps2;
            ECP.PL_ChkQ[0][3]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][3],2);
          }
          else
          {
            ECP.PL_CumQ[0][2] += Ps2;
            ECP.PL_ChkQ[0][2]=ChkNum((unsigned char*)&ECP.PL_CumQ[0][2],2);
          }
        }
      }
#endif      
  }
  else
  for(i=0;i<MAX_CH_NUM;++i)
  {

    ATT7022RdReg(ATVoltFlag,(unsigned char*)&(SM.State[i]),i);

    ATT7022RdReg(ATPZ,(unsigned char*)&tmp_p,i);

    tmp_p &= 0xffffff;

    if(tmp_p>100)
      tmp_p =0;
    if(tmp_p)
    {
      if(SM.State[i]&0x1000)
      {

        ECP.PL_CumPn[i] += tmp_p;

        ECP.PL_ChkPn[i]=ChkNum((unsigned char*)&ECP.PL_CumPn[i],2);

      }

      else

      {

        ECP.PL_CumPp[i] += tmp_p;

        ECP.PL_ChkPp[i]=ChkNum((unsigned char*)&ECP.PL_CumPp[i],2);

      }

    }

    ATT7022RdReg(ATQZ,(unsigned char*)&tmp_p,i);

    tmp_p &= 0xffffff;

    if(tmp_p>100)
      tmp_p =0;
    
    if(tmp_p)

    {

      if(SM.State[i]&0x2000)

      {

        ECP.PL_CumQn[i] += tmp_p;

        ECP.PL_ChkQn[i]=ChkNum((unsigned char*)&ECP.PL_CumQn[i],2);

      }

      else

      {

        ECP.PL_CumQp[i] += tmp_p;

        ECP.PL_ChkQp[i]=ChkNum((unsigned char*)&ECP.PL_CumQp[i],2);

      }

      Quad=GetMQuad((SM.State[i]>>12)&0x3,0);

      //Quad = (SM.State[i]>>12)&0x3;

      ECP.PL_CumQ[i][Quad] += tmp_p;

      ECP.PL_ChkQ[i][Quad]=ChkNum((unsigned char*)&ECP.PL_CumQ[i][Quad],2);

    }
  }

  EC_MeasA();

}

/***************************************************

	Working for Every Second

	1. Decreasing Second Timer

	2. Energy Measurement

	3. Maxium Demand Measurement

	4. Even Log File

***************************************************/

void ProcSec(void)

{

  char Buff[8];

  char* Point;

  int i,j,flag_p;

  signed long *si_val;

  unsigned int i_val;
  double f1,f2,f3;

  Flag.Clk &= ~F_Sec;

  Point = Buff;

  

  memset( Point,0,6 );

//  Buff[0]=0xaa;

//        Buff[1]=0x55;

//        Buff[2]=0x00;

//        Buff[3]=0x11;

//        Buff[4]=0x22;

//        Serial_Write(0,Buff,5);

  if((Flag.Power & F_PwrUp) != 0)

  {

    if(SM.TestCnt != 0)

    {

       SM.TestCnt--;

    }

    if(SM.TestDisCnt != 0)

    {

       SM.TestDisCnt--;

       if(SM.TestDisCnt==0 && SM.rebootflag)

      {

          NVIC_SystemReset();

      }

    }

    

    for(i=0;i<MAX_CH_NUM;++i)

    {

      ATT7022RdReg(PFlag,(unsigned char*)&(SM.PQFlag[i]),i);

      Read_ATTValue(ATPWPA,(unsigned char *)&Energy_Data[i].Pa,i);

      Read_ATTValue(ATPWPB,(unsigned char *)&Energy_Data[i].Pb,i);

      Read_ATTValue(ATPWPC,(unsigned char *)&Energy_Data[i].Pc,i);

      Read_ATTValue(ATPWPZ,(unsigned char *)&Energy_Data[i].Pt,i);
      if(SM.PQFlag[i]&0x1)
      {
        Energy_Data[i].Pa *=-1;
      }
      if(SM.PQFlag[i]&0x2)
      {
        Energy_Data[i].Pb *=-1;
      }
      if(SM.PQFlag[i]&0x4)
      {
        Energy_Data[i].Pc *=-1;
      }
      if(SM.PQFlag[i]&0x8)
      {
        Energy_Data[i].Pt *=-1;
      }
      Real_Data[i].Pa = Energy_Data[i].Pa;

      Real_Data[i].Pb = Energy_Data[i].Pb;

      Real_Data[i].Pc = Energy_Data[i].Pc;

      Read_ATTValue(ATPWQA,(unsigned char *)&Real_Data[i].Qa,i);

      Read_ATTValue(ATPWQB,(unsigned char *)&Real_Data[i].Qb,i);

      Read_ATTValue(ATPWQC,(unsigned char *)&Real_Data[i].Qc,i);

      

      if(SM.PQFlag[i]&0x10)

      {

        Real_Data[i].Qa *=-1;

      }

      if(SM.PQFlag[i]&0x20)

      {

        Real_Data[i].Qb *=-1;

      }
      if(SM.PQFlag[i]&0x40)
      {
        Real_Data[i].Qc *=-1;
      }

      Read_ATTValue(ATPWSA,(unsigned char *)&Real_Data[i].Sa,i);

      Read_ATTValue(ATPWSB,(unsigned char *)&Real_Data[i].Sb,i);

      Read_ATTValue(ATPWSC,(unsigned char *)&Real_Data[i].Sc,i);

      Read_ATTValue(ATPWSZ,(unsigned char *)&Real_Data[i].St,i);

      Read_ATTValue(ATFreq,(unsigned char *)&Real_Data[i].AFreq,i);

      Read_ATTValue(ATUrmsA,(unsigned char *)&Real_Data[i].Ua,i);

      Read_ATTValue(ATUrmsB,(unsigned char *)&Real_Data[i].Ub,i);

      Read_ATTValue(ATUrmsC,(unsigned char *)&Real_Data[i].Uc,i);

      Read_ATTValue(ATIrmsA,(unsigned char *)&Real_Data[i].Ia,i);

      Read_ATTValue(ATIrmsB,(unsigned char *)&Real_Data[i].Ib,i);

      Read_ATTValue(ATIrmsC,(unsigned char *)&Real_Data[i].Ic,i);

      Read_ATTValue(ATFactorA,(unsigned char *)&Real_Data[i].Pfa,i);

      Read_ATTValue(ATFactorB,(unsigned char *)&Real_Data[i].Pfb,i);

      Read_ATTValue(ATFactorC,(unsigned char *)&Real_Data[i].Pfc,i);

      Read_ATTValue(ATFactorZ,(unsigned char *)&Real_Data[i].Pft,i);

      Read_ATTValue(ATAngleA,(unsigned char *)&SM.Angle_Ia[i],i);

      Read_ATTValue(ATAngleB,(unsigned char *)&SM.Angle_Ib[i],i);

      Read_ATTValue(ATAngleC,(unsigned char *)&SM.Angle_Ic[i],i);
      Read_ATTValue(ATPWQZ,(unsigned char *)&Real_Data[i].Qt,i);
      if(SM.PQFlag[i]&0x80)
      {
        Real_Data[i].Qt *=-1;
      }
      Real_Data[i].Pt = Energy_Data[i].Pt;
      
      if(((Real_Data[0].Ua>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Uc<80)) || ((Real_Data[0].Uc>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Ua<80)))
      { 
        if((Real_Data[0].Ua>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Uc<80))
        {
          f1 = SM.Angle_Ia[i];
          if(SM.Angle_Ia[i]>300)
          {
            f1 = SM.Angle_Ia[i]-300;
          }
          else
          {
            f1 = 300-SM.Angle_Ia[i];
          }
          f2 = cos(f1*3.1415926/1800);
          if(f2<0)
            Real_Data[i].Pft = f2*-1000;
          else
            Real_Data[i].Pft = f2*1000;
          f2 = Real_Data[0].Ua*(Real_Data[0].Ia+Real_Data[0].Ib+Real_Data[0].Ic)*f2/1732;
          Real_Data[i].Pt = f2;
          f2 = sin(f1*3.1415926/1800);
          if(fabs(f2)<0.01)
            Real_Data[i].Qt =0;
          else
          {  
            f2 = Real_Data[0].Ua*(Real_Data[0].Ia+Real_Data[0].Ib+Real_Data[0].Ic)*f2/1732;
            Real_Data[i].Qt = f2;
          }
        }
        if((Real_Data[0].Uc>8000) && (Real_Data[0].Ub<80) && (Real_Data[0].Ua<80))
        {
          f1 = SM.Angle_Ic[i];
          if(SM.Angle_Ic[i]>=3300)
          {
            f1 = SM.Angle_Ic[i]-3300;
          }
          else
          {
            f1 = 300+SM.Angle_Ic[i];
          }
          f2 = cos(f1*3.1415926/1800);
          if(f2<0)
            Real_Data[i].Pft = f2*-1000;
          else
            Real_Data[i].Pft = f2*1000;
          f2 = Real_Data[0].Uc*(Real_Data[0].Ia+Real_Data[0].Ib+Real_Data[0].Ic)*f2/1732;
          Real_Data[i].Pt = f2;
          f2 = sin(f1*3.1415926/1800);
          if(fabs(f2)<0.01)
            Real_Data[i].Qt =0;
          {
            f2 = Real_Data[0].Uc*(Real_Data[0].Ia+Real_Data[0].Ib+Real_Data[0].Ic)*f2/1732;
            Real_Data[i].Qt = f2;
          }
        }
        SM.sigle_pt  = 1;
      }
      else
      {
        SM.sigle_pt  = 0;
       // Real_Data[0].Pt = 1000000;
      //  Real_Data[0].Qt = 1000000;
      }
    }

#if  0  

    //Pn_Event_Save(0,1,1);

    Pt_Event_Save(0);

#else    

    for(i=0;i<MAX_CH_NUM;++i)

    {

      i_val = 0;

      for(j=0;j<3;++j)

      {

        if(*((&Real_Data[i].Ia)+j)==0)

        {

          *((&Real_Data[i].Pfa)+j)=0;

        }

        i_val += *((&Real_Data[i].Ia)+j);

      }

      if(i_val==0)

        Real_Data[i].Pft = 0;

      i_val = 0;

      for(j=0;j<3;++j)

      {

        i_val += *((&Real_Data[i].Ua)+j);

      }

      if(i_val==0)

        Real_Data[i].AFreq = 50000;

      

      flag_p = SM.PQFlag[i]^SM.PQFlag_b[i];

      SM.PQFlag_b[i]=SM.PQFlag[i];

      if((flag_p&0xf))
      {
        si_val = &Real_Data[i].Pa;
        for(j=0;j<4;++j)
        {
          if(flag_p&(1<<j))
          {
            if(abs(si_val[j])>40)
            {
              SM.P_Time[i][j]=60;
            }
          }
        }
      }

      for(j=0;j<3;++j) //功率方向

      {

        if(SM.P_Time[i][j])

        {

          --SM.P_Time[i][j];

          if(SM.P_Time[i][j]==0)

          {

            Pn_Event_Save(i,j,SM.PQFlag[i]&(1<<j));

          }

        }

      }
//      if(SM.P_Time[i][3]==0)
//        SM.P_Time[i][3]=30;

      if(SM.P_Time[i][3]) //潮流
      {
        --SM.P_Time[i][3];
        if(SM.P_Time[i][3]==0)
        {
            Pt_Event_Save(i);

        }
      }
    }

#endif

  }

  else

  {

    HT_GPIO_BitsToggle(HT_GPIOA,GPIO_Pin_4);

  }

}





/***************************************************

	Working for Every Minute

	1. Decreasing Minute Timer

	2. Fee judgement

	3. Load Profile

***************************************************/

void ProcMin(void)

 {
    int i;
    unsigned char Time_buf[8];

    unsigned short year;

    Flag.Clk &= ~F_Min;

    if((Flag.Power & F_PwrUp) == 0)

      return;

    //GetTime();

    MoveCurrentTimeBCD_Hex();

    Time_buf[0]=Clk.SecH;

    Time_buf[1]=Clk.MinH;

    Time_buf[2]=Clk.HourH;

    Time_buf[3]=Clk.DayH;

    Time_buf[4]=Clk.Month;

    year = Clk.YearH;

    year = year*256 + Clk.YearL;

    Time_buf[5]=year-2000;

    if((Clk.MinH%15)==0)

    {

      Save_Data(Time_buf);

    }

    Load_InfoData();

    //Save_RandData(Time_buf);

    ATT7022EStateCheckRun(Clk.MinH%MAX_CH_NUM);
    if((Real_Data[0].Ua>8000) && (Real_Data[0].Ub<80))
    {
      if(Para.PW==0x34)
      {
        Para.PW=0x33;
        HT_GPIO_BitsReset(HT_GPIOA,GPIO_Pin_7);
        for(i=0;i<MAX_CH_NUM;i++)
        {
          ATT7022Init(i);	
        }
      }
    }
    else
    {
      if(Para.PW==0x33)
      {
        Para.PW=0x34;
        HT_GPIO_BitsSet(HT_GPIOA,GPIO_Pin_7);
        for(i=0;i<MAX_CH_NUM;i++)
        {
          ATT7022Init(i);
        }
      }
    }
}	



/***************************************************

	Working for Every Minute

	1. Decreasing Minute Timer

***************************************************/

void ProcHour(void)

{

  unsigned char Time_buf[8];

  unsigned short year;

  Flag.Clk &= ~F_Hour;

  if((Flag.Power & F_PwrUp) == 0)

      return;

  GetTime();

  MoveCurrentTimeBCD_Hex();

  Time_buf[0]=Clk.SecH;

  Time_buf[1]=Clk.MinH;

  Time_buf[2]=Clk.HourH;

  Time_buf[3]=Clk.DayH;

  Time_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  Time_buf[5]=year-2000;

  Save_HourData(Time_buf);

}



void ProcDay(void)

{

  unsigned char Time_buf[8];

  unsigned short year;

  Flag.Clk &= ~F_Day;

  if((Flag.Power & F_PwrUp) == 0)

      return;

  Time_buf[0]=Clk.SecH;

  Time_buf[1]=Clk.MinH;

  Time_buf[2]=Clk.HourH;

  Time_buf[3]=Clk.DayH;

  Time_buf[4]=Clk.Month;

  year = Clk.YearH;

  year = year*256 + Clk.YearL;

  Time_buf[5]=year-2000;

  Save_DayData(Time_buf);

  if(Clk.DayH==1)

  {

    Save_MonthData(Time_buf);

  }

}	

//#define COM_PARITY   UartParity_Disable  

#define COM_PARITY   UartParity_EVEN

void main(void)

{

  unsigned int i;

  unsigned char flash_id[16];

  HT_FreeDog();

  //i = 5000;

  i=E2END_DATA_ADDR;

  while(i--);

  fnTarget_Init();

 // Flag.BatState=0;

  while(1)

  {	

    HT_FreeDog();

    for(i=0;i<5000;i++)

    {

      HT_FreeDog();

      __NOP();

    }



    GetTime();

    MoveCurrentTimeBCD_Hex();																									//10.11.22

    while (1)

    {

      //GetTime();

      HT_FreeDog();						

      if(((Flag.Power & F_PwrUp) == 0) && ( PowerCheck() == 1 ))		

      {

        PwrOnInit();

        VarInit();

        InitPara();			

        InitPara5();

        Serial_Open(0,9600,8,COM_PARITY);

        //Serial_Open(0,9600,8,UartParity_EVEN);

        Load_InfoData();

	InitPara6();   

        InitIEC101Prot();

#if 0        

        Read_FlashID(flash_id);   

        memset(flash_id,0x51,16);

        E2P_WFM(0,flash_id,16);

        memset(flash_id,0,10);

        E2P_RFM(flash_id,0,16);

        memset(flash_id,0x52,16);

        E2P_WFM(0,flash_id,16);

        memset(flash_id,0,10);

        E2P_RFM(flash_id,0,16);

        memset(flash_id,0,10);

        E2P_RFM(flash_id,0,16);

        memset(flash_id,0,10);

        E2P_RFM(flash_id,0,16);

        BlockErase(0);

        Read_Flash(flash_id,0,10);

        memset(flash_id,0xaa,10);

        Write_Flash(0,flash_id,10);

        memset(flash_id,0,10);

        Read_Flash(flash_id,0,10);

        memset(flash_id,0,10);

        Read_Flash(flash_id,0,10);

        memset(flash_id,0,10);

        Read_Flash(flash_id,0,10);

        memset(flash_id,0x55,16);

        E2P_PWData(0,flash_id,16);

        memset(flash_id,0,10);

        E2P_PRData(flash_id,0,16);

        memset(flash_id,0x33,16);

        E2P_WData(0,flash_id,16);

        memset(flash_id,0,10);

        E2P_RData(flash_id,0,16);

        memset(flash_id,0,10);

        E2P_WData(LoadRecord_Time,flash_id,8);

        E2P_WData(RandRecord_Time,flash_id,8);

        E2P_WData(FrzdRecord_Time,flash_id,8);

        E2P_WData(ShrpdRecord_Time,flash_id,8);

        E2P_WData(MonthdRecord_Time,flash_id,8);

#endif

//        flash_id[0] = 0x20;

//        flash_id[1] = 0x18;

//        flash_id[2] = 0x07;

//        flash_id[3] = 0x19;

//        flash_id[4] = 0x00;

//        flash_id[5] = 0x01;

//        EC_E2_W(ID_ADDR,flash_id,6);

        //EC_ClearA();

        //Read_E2R1();

        //Clear_EVTC(0);

        Read_E2R();

        //ReLoad_ECRamBufAds();

        for(i=0;i<MAX_CH_NUM;i++)

        {

          ATT7022Init(i);	//Test

        }

        compensate_day();

        compensate_month();

       // Clear_E2R(0);

       // Clear_EVT2R(0);
        SM.qplus=0;
        SM.pplus=0;
        break;

      }	

      if(((Flag.Power & F_PwrUp) != 0) && ( PowerCheck() == 0 ))

      {

       // Save_ECRamBufAds();

//       // Flag.BatState=1;

//        //PwrDnInit();

      }	

    

      

      if(( Flag.Clk & F_ThirdSec )) 	
      {		
        //Flag.Clk &= ~F_ThirdSec;
        ProcThirdSec();
      }

      if(Flag.Clk& F_HalfSec)
      {
        ProcHalfSec();
      }

      if (Flag.Clk & F_Sec) 

      {

        ProcSec();	

      }

      if (Flag.Clk & F_Min) ProcMin();

      if (Flag.Clk & F_Hour) ProcHour();

      if (Flag.Clk & F_Day) ProcDay();

      

      if(Flag.Power & F_IrmsCheck)

      {

        Flag.Power &= ~F_IrmsCheck;

        udelay(10000);

        Serial_Open(0,115200,8,UartParity_Disable);

        xmodemReceive();

        udelay(10000);

        Serial_Open(0,9600,8,COM_PARITY);

      }

      else

      {	

        IEC101Process();

      }			

#if 0     

      if(((Flag.Power & F_PwrUp) == 0))

      { 

        unsigned int wakeif;

        Flag.Run |= F_Hold;

        EnterHold();

        wakeif = HT_PMU->WAKEIF;

        //if((HT_PMU->WAKEIF&0x001000f4))

        if(wakeif&0x001000f4)

        {	

          if((Flag.Run & F_Hold)!=0)

          {

            Flag.Run &= ~F_Hold;

            ExitHold();

            HT_FreeDog();						

          }

        }				

      }

#endif      

    }

  }

}