/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#include <ks0108.h>
#include <SystemFont5x7.h>
#include <Wire.h>
#include <DS1307.h>

//char[][]={Sun,Mon,Tue,Wen,Thu,Fri,Sat};
/*
��������� ��������� �������
 ����� ������������ ���:
 Time:
 00:00:00 
 Date:
 00/00/0000 Mon
 */
uint8_t workType;
uint8_t rtcState;//�������������� �������
int rtc[7];

void ClockDispData()
{
  if(rtc[4]<10)
    GLCD.CursorTo(3,3);
  else  
    GLCD.CursorTo(2,3);
  GLCD.PrintNumber(rtc[4]);//�����
  if(rtc[5]<10)
    GLCD.CursorTo(6,3);
  else  
    GLCD.CursorTo(5,3);
  GLCD.PrintNumber(rtc[5]);//������
  GLCD.CursorTo(8,3);
  GLCD.PrintNumber(rtc[6]);//����
  GLCD.CursorTo(13,3);
  switch (rtc[3])
  {
  case 1:
    GLCD.Puts("Mon");
    break;
  case 2:
    GLCD.Puts("Tue");
    break;
  case 3:
    GLCD.Puts("Wen");
    break;
  case 4:
    GLCD.Puts("Thu");
    break;
  case 5:
    GLCD.Puts("Fri");
    break;
  case 6:
    GLCD.Puts("Sat");
    break;
  case 7:
    GLCD.Puts("Sun");
    break;
  }
}
void ClockDispTime()
{
  if(rtc[2]<10)
    GLCD.CursorTo(3,5);
  else  
    GLCD.CursorTo(2,5);
  GLCD.PrintNumber(rtc[2]);//����
  if(rtc[1]<10)
    GLCD.CursorTo(6,5);
  else  
    GLCD.CursorTo(5,5);
  GLCD.PrintNumber(rtc[1]);//������
  if(rtc[0]<10)
    GLCD.CursorTo(9,5);
  else  
    GLCD.CursorTo(8,5);
  GLCD.PrintNumber(rtc[0]);//�������

}
void ClockDispStatic()
{
  GLCD.ClearScreen();
  GLCD.DrawHoriLine(0, 8, 127, BLACK);//������� ���������
  GLCD.DrawHoriLine(0, 54, 127, BLACK);//������ ���������
  GLCD.CursorTo(0,7);
  GLCD.Puts("  <    -    +     >  ");//������
  //���������� ����� ��������
  GLCD.DrawVertLine(30, 55, 8, BLACK);
  GLCD.DrawVertLine(60, 55, 8, BLACK);
  GLCD.DrawVertLine(90, 55, 8, BLACK);
  GLCD.InvertRect(0, 55, 127, 8);//����� � �������(��� ������ � �����?)
  GLCD.CursorTo(0,0);//������ ������
  GLCD.Puts("Data/Time setup");
  GLCD.CursorTo(2,2);//������ ������
  GLCD.Puts("Date");
  GLCD.CursorTo(4,3);//������ ������
  GLCD.Puts("/  /");
  GLCD.CursorTo(2,4);//������ ������
  GLCD.Puts("Time");
  GLCD.CursorTo(4,5);//������ ������
  GLCD.Puts("h  m  s");
  //GLCD.Puts(datatime);//�����

}
void dispDraw()//������ ����������, � ������
{
  GLCD.DrawHoriLine(0, 54, 127, BLACK);//������� ���������
  GLCD.CursorTo(0,7);
  GLCD.Puts("  <    -    +     >  ");//������
  //���������� ����� ��������
  GLCD.DrawVertLine(30, 55, 8, BLACK);
  GLCD.DrawVertLine(60, 55, 8, BLACK);
  GLCD.DrawVertLine(90, 55, 8, BLACK);
  GLCD.InvertRect(0, 55, 127, 8);//������ ���������
}

void ClockUpButton(uint8_t cursorSt)
{
  RTC.stop();
  switch (cursorSt)
  {
  case 0:
    workType=0;
    break;
  case 1://�������
    if (rtc[0]<59) rtc[0]++;
    else rtc[0]=0;
    RTC.set(0,rtc[0]);
    break;
  case 2://������
    if (rtc[1]<59) rtc[1]++;
    else rtc[1]=0;
    RTC.set(1,rtc[1]);
    break;
  case 3://����
    if (rtc[2]<23) rtc[2]++;
    else rtc[2]=0;
    RTC.set(2,rtc[2]);
    break;
  case 4://��� ������
    if (rtc[3]<7) rtc[3]++;
    else rtc[3]=1;
    RTC.set(3,rtc[3]);
    break;
  case 5://����
    if (rtc[4]<31) rtc[4]++;
    else rtc[4]=1;
    RTC.set(4,rtc[4]);
    break;
  case 6://�����
    if (rtc[5]<12) rtc[5]++;
    else rtc[5]=1;
    RTC.set(5,rtc[5]);
    break;
  case 7://���
    rtc[6]++;
    RTC.set(6,rtc[6]-2000);
    break;
  }
  RTC.start();
}

void ClockDownButton(uint8_t cursorSt)
{
  RTC.stop();
  switch (cursorSt)
  {
  case 0:
    workType=0;
    break;
  case 1://�������
    if (rtc[0]>0) rtc[0]--;
    else rtc[0]=59;
    RTC.set(0,rtc[0]);
    break;
  case 2://������
    if (rtc[1]>0) rtc[1]--;
    else rtc[1]=59;
    RTC.set(1,rtc[1]);
    break;
  case 3://����
    if (rtc[2]>0) rtc[2]--;
    else rtc[2]=23;
    RTC.set(2,rtc[2]);
    break;
  case 4://��� ������
    if (rtc[3]>1) rtc[3]--;
    else rtc[3]=7;
    RTC.set(3,rtc[3]);
    break;
  case 5://����
    if (rtc[4]>1) rtc[4]--;
    else rtc[4]=31;
    RTC.set(4,rtc[4]);
    break;
  case 6://�����
    if (rtc[5]>1) rtc[5]--;
    else rtc[5]=12;
    RTC.set(5,rtc[5]);
    break;
  case 7://���
    if (rtc[6]>2000) rtc[6]--;//���� ����� �� ����� ��������! :)
    RTC.set(6,rtc[6]-2000);
    break;
  }
  RTC.start(); 
}


void clockCursor(uint8_t cursorSt)
{
  switch (cursorSt)
  {
  case 0://return
    GLCD.InvertRect(7, 56, 16, 6);
    break;
  case 1://seconds
    GLCD.DrawHoriLine(48,47, 10, BLACK);
    break;
  case 2://minutes
    GLCD.DrawHoriLine(29,47, 10, BLACK);
    break;
  case 3://hour
    GLCD.DrawHoriLine(12,47, 10, BLACK);
    break;
  case 4://dow
    GLCD.DrawHoriLine(78,31, 15, BLACK);
    break;
  case 5://day
    GLCD.DrawHoriLine(12,31, 10, BLACK);
    break;
  case 6://mounth
    GLCD.DrawHoriLine(29,31, 10, BLACK);
    break;
  case 7://year
    GLCD.DrawHoriLine(48,31, 24, BLACK);
    break;
  }
}


void setup()
{
  DDRB=B00000000;
  // Serial.begin(9600);
  GLCD.Init(NON_INVERTED);   // initialise the library, non inverted writes pixels onto a clear screen
  GLCD.ClearScreen();  
  GLCD.SelectFont(System5x7);
}

void loop()
{
  RTC.get(rtc,true);//�������� ������ �����
  switch (buttonsStat())
  {
  case 3://������  +
  ClockUpButton(rtcState);
    break;
  case 1://������  <
  if (rtcState>0) rtcState--;
    break;
  case 2://-
    ClockDownButton(rtcState);
    break;
  case 4://>
    if (rtcState<7) rtcState++;
    break;      
  }
  ClockDispStatic();//������ �������
  ClockDispData();//����� ����
  ClockDispTime();//����� �����
  clockCursor(rtcState);
  _delay_ms(250);
}



//���������� ������
uint8_t buttonsStat()
{
  uint8_t button=0;
  uint8_t buttons=(~PINB)&B00001111;
  if (buttons)
  {
    switch (buttons)
    {
    case 1://������  +
      button=3;
      break;
    case 2://������  > 
      button=4;
      break;
    case 4://������  <
      button=1;
      break;
    case 8://������  -
      button=2;
      break;
    }
  }
  return button;
}

