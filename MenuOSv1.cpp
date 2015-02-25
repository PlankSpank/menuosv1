/*Copyright (c) 2010, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

extern "C" void __cxa_pure_virtual() { while (1); }
	

#define LEDDIGITS 4
#define LABELS 4
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
//#include <math.h>
#include "taskmanager.h"//���������� ���������� ���������� �����
//#include "filters.h"//���������� ���������� ��������
#include "drive.h"
  #include "glcd/glcd.h"
  #include "glcd/glcd_Buildinfo.h"
  #include "glcd/glcd_Config.h"
  #include "glcd/fonts/SystemFont5x7.h"
#include "buttons.h"
#include "menu.h"
//uint8_t _Label=0;
/*
������������ ����� ���������:
0 -ButtonSearch - ���������� ������
1 -
2 -AppSaved - ��������� ��������� ������ ����������
3 -ApplicationStop - ��������� ��������� ������ � ����
4 -DriveIntencivity - ��������� ��������� �������������. �������� �� ���������� ��������� �������.
5 - MotionWork - ���������� ������ ������������
6 -
7 -
*/

int main(void)
{
	TManager.TSetup();//��������� �������
	ButtonSetup();//����������� ������, ������� ����� ������, ��������� ������������� �����. 0 ����������� ���� �������
	GLCD.Init();
	MenuSetup();
	MenuStartUp();
	//MotionViewSetup();
	DriveSetup();
	TManager.TStart();//������ ����������
	sei();//���������� ������ ����������.
   while(1)
    {
        //TODO:: Please write your application code 
    }
}