/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#ifndef MENU_H_
#define MENU_H_

//#define MENUITEMSONPAGE 6 //not sypported yet
#include "MTask.h"
#include "buttons.h"   
#include "definitions.h"
#include "config.h"	

struct filedata{
	uint8_t type;
	uint8_t parent;
	char name[20];
	uint8_t mode1;
	uint8_t mode2;
};

class MMenu{
	private:
	
	//current menulevel position
	uint8_t level;
	
	//current cursor position
	uint8_t cursor;
	
	//Breadcrumbs:
	//byte 0 - 
	//byte 1 - 
	//byte 2 - 
	uint8_t brCrumbs[MAXDEPTH+1][3];
	
	//file info structure
	filedata file;
	
	uint8_t Positions[4]={0};//������� �����. X,Y ���������, X,Y �������
		
	public:
		Menu();
		
		~Menu();

};

extern MMenu Menu;


void MenuSetup(void);
void CursorSet(void);
void PageList(void);
void MenuButtonUp(void);
void MenuButtonDown(void);
void MenuButtonLeft(void);
void MenuButtonRight(void);
void MenuButtonEnter(void);
void MenuButtonReturn(void);
void FileReturn(void);
void DispFile(uint8_t str, uint8_t _fnumber, char _buff[LCDCOL-5]);
void FileGet(uint8_t FileNumb);
void ApplicationStop(void);
void ApplicationStart(uint8_t AppNumber);
void AppSaved(void);
void MenuHeader(void);
void MenuStartUp(void);

#endif /* MENU_H_ */