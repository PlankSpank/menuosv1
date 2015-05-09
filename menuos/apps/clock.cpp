/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/



#include "clock.h"


static char weekday[8][4]={"Nul","Mon","Tue","Wen","Thu","Fri","Sat","Sun"};
/*
��������� ��������� �������
 ����� ������������ ���:
 Time:
 00:00:00 
 Date:
 00/00/0000 Mon
 */


MClock::MClock(){
	
}

MClock::~MClock(){
	
}

uint8_t MClock::Setup(uint8_t argc, uint8_t *argv)
{
	Buttons.Add(ClockButtonsHandler);
	GLCD.ClearScreen();
	RTC.get(rtc,true);//�������� ������ �����
	RTC.stop();
	DrawStatic();//������ �������
	DrawDate();//����� ����
	DrawTime();//����� �����
	DrawCursor();
	
	return 0;
}


void ClockButtonsHandler(uint8_t button)
{
	Clock.ButtonsLogic(button);
}

uint8_t MClock::ButtonsLogic(uint8_t button){
	
	switch (button){
		case BUTTONLEFT:
		 log_trace("Button Left");
			cursorSt--;
			if (cursorSt < 0){
				cursorSt = 7;
			}			
		break;
		case BUTTONRIGHT:
			log_trace("Button Right");
			cursorSt++;
				if (cursorSt > 7){
					cursorSt = 0;
				}
		break;
		case BUTTONRETURN:
			log_trace("Return");
			Return();
		break;
		//Menu start from top to bottom, so we has inverted buttons implementation
		case BUTTONUP:
			log_trace("Button Up");
			ButtonUp();
		break;
		case BUTTONDOWN:
			log_trace("Button Down");
			ButtonDown();
		break;
		default:
		
		break;
		
	}
	DrawStatic();//������ �������
	DrawDate();//����� ����
	DrawTime();//����� �����
	DrawCursor();
	return 0;
}

void MClock::DrawDate()
{
	GLCD.CursorTo(2,2);//������ ������
	GLCD.Puts("Date");
	GLCD.CursorTo(4,3);//������ ������
	GLCD.Puts("/  /");
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
  GLCD.Puts(weekday[rtc[3]]);
}

void MClock::DrawTime()
{
  GLCD.CursorTo(2,4);//������ ������
  GLCD.Puts("Time");
  GLCD.CursorTo(4,5);//������ ������
  GLCD.Puts("h  m  s");
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
void MClock::DrawStatic()
{
  GLCD.ClearScreen();
  GLCD.DrawHLine(0, 8, 127, BLACK);//������� ���������
  GLCD.DrawHLine(0, 54, 127, BLACK);//������ ���������
  GLCD.CursorTo(0,7);
  GLCD.Puts("  <    -    +     >  ");//������
  //���������� ����� ��������
  GLCD.DrawVLine(30, 55, 8, BLACK);
  GLCD.DrawVLine(60, 55, 8, BLACK);
  GLCD.DrawVLine(90, 55, 8, BLACK);
  GLCD.InvertRect(0, 55, 127, 8);
  GLCD.CursorTo(0,0);//������ ������
  GLCD.Puts("Data/Time setup");
}


void MClock::ButtonUp()
{
  switch (cursorSt)
  {
  case 0:
    Return();
    break;
  case 1://�������
    if (rtc[0]<59) 
		rtc[0]++;
    else 
		rtc[0]=0;
    break;
  case 2://������
    if (rtc[1]<59) 
		rtc[1]++;
    else 
		rtc[1]=0;
    break;
  case 3://����
    if (rtc[2]<23) 
		rtc[2]++;
    else 
		rtc[2]=0;
    break;
  case 4://��� ������
    if (rtc[3]<7) 
		rtc[3]++;
    else 
		rtc[3]=1;
    break;
  case 5://����
    if (rtc[4]<31) 
		rtc[4]++;
    else 
		rtc[4]=1;
    break;
  case 6://�����
    if (rtc[5]<12) 
		rtc[5]++;
    else 
		rtc[5]=1;
    break;
  case 7://���
    if (rtc[6] < 2038)
		rtc[6]++;	
    break;
  }
}


void MClock::DrawCursor()
{
	switch (cursorSt)
	{
		case 0://return
		GLCD.InvertRect(7, 56, 16, 6);
		break;
		case 1://seconds
		GLCD.DrawHLine(48,47, 10, BLACK);
		break;
		case 2://minutes
		GLCD.DrawHLine(29,47, 10, BLACK);
		break;
		case 3://hour
		GLCD.DrawHLine(12,47, 10, BLACK);
		break;
		case 4://dow
		GLCD.DrawHLine(78,31, 15, BLACK);
		break;
		case 5://day
		GLCD.DrawHLine(12,31, 10, BLACK);
		break;
		case 6://mounth
		GLCD.DrawHLine(29,31, 10, BLACK);
		break;
		case 7://year
		GLCD.DrawHLine(48,31, 24, BLACK);
		break;
	}
}

void MClock::ButtonDown()
{
  switch (cursorSt)
  {
  case 0:
    Return();
    break;
  case 1://�������
    if (rtc[0]>0) 
		rtc[0]--;
    else 
		rtc[0]=59;
    
    break;
  case 2://������
    if (rtc[1]>0) 
		rtc[1]--;
    else 
		rtc[1]=59;
    
    break;
  case 3://����
    if (rtc[2]>0) 
		rtc[2]--;
    else 
		rtc[2]=23;    
    break;
  case 4://��� ������
    if (rtc[3]>1) 
		rtc[3]--;
    else 
		rtc[3]=7;    
    break;
  case 5://����
    if (rtc[4]>1) 
		rtc[4]--;
    else 
		rtc[4]=31;
    break;
  case 6://�����
    if (rtc[5]>1) 
		rtc[5]--;
    else 
		rtc[5]=12;
    break;
  case 7://���
    if (rtc[6]>2000) 
		rtc[6]--;   
    break;
  }
 
}



void MClock::Return(){
	RTC.set(0,rtc[0]);
	RTC.set(1,rtc[1]);
	RTC.set(2,rtc[2]);
	RTC.set(3,rtc[3]);
	RTC.set(4,rtc[4]);
	RTC.set(5,rtc[5]);
	RTC.set(6,rtc[6]-2000);
	RTC.start();
	Buttons.Clear();
	Task.ActiveApp = 0;	
}






