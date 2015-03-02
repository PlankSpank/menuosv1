/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include "menu.h"
#include "static.h"    //���� �����������

uint8_t brCrumbs[MAXDEPTH+1][3]={0};//������ ������� ������. ���������� 1 ���� - ����� ���������, ������ - ��������� �������
uint8_t level=0;//����� �������� ������
uint8_t fileNumb=0;//����� �������� �����
uint8_t fileData[4]; //� � ���� ���������� ����� ������� ��������� ��������.
uint8_t Positions[4]={0};//������� �����. X,Y ���������, X,Y �������
char FileName[18];

//��������� ������ ������ �����
void Menu.Setup(){
	BSlot(BUTTONSLOTLEFT,MenuButtonLeft);//�������  �����
	BSlot(BUTTONSLOTRIGHT,MenuButtonRight);//�������  �����
	BSlot(BUTTONSLOTUP,MenuButtonUp);//�������  �����
	BSlot(BUTTONSLOTDOWN,MenuButtonDown);//�������  �����
	BSlot(BUTTONSLOTRETURN,MenuButtonReturn);//�������  �����
	BSlot(BUTTONSLOTENTER,MenuButtonEnter);//�������  �����		
	Positions[0]=POSXMIN;
	Positions[1]=POSXMAX;
	GLCD.SelectFont(MENUFONT);
	FileReturn();
}
//������������� ������ � ����������� �������.

void MenuStartUp(){
//��������� ������ ����������
MenuButtonEnter();
}


void DispString(uint8_t str, char* textstr)
{
  if ((str>=0) && (str<DISPSTR)){//��������� ������� ������
    GLCD.CursorToXY(POSXMIN+1,POSYMIN+1+str*MENUFOTNHIGHT);//������ ������
    GLCD.Puts(textstr);//�����
  }
}
void MenuHeader(){
	GLCD.CursorToXY(0,0);
	GLCD.Puts(FileName);
	GLCD.DrawHLine(0,8,127,BLACK);

}


//������� ������ ������� ������
void PageList(){
  GLCD.FillRect(0,0,GLCD.Width,GLCD.Height,WHITE);
  MenuHeader();
  char buff[LCDCOL-5];
  char buff2[LCDCOL-3];
  uint8_t currs;
  uint8_t fstart;
  switch (fileData[0]){
  case T_FOLDER://������� �����..
    if ((brCrumbs[level][1]&LCDINVBITS)==((fileData[2])&LCDINVBITS)) currs=(fileData[2])&LCDBITS;//��� ������������ ��������� ������� �� ��������� ��������
    else currs=LCDBITS;
    fstart=fileData[1]+(brCrumbs[level][1]&LCDINVBITS);//����� ����� ��� ������ ������.
    for (uint8_t i=0;i<=currs;i++)//����� �� ������� ��� ����������� �����
    {
 	strlcpy_P(buff, (char*)pgm_read_word(&(fileNames[i+fstart])),sizeof(buff));//��������� ���
    DispFile(i,i+fstart,buff);
    }
    break;
  case T_DFOLDER://������������ �����
    if ((brCrumbs[level][1]&LCDINVBITS)==((fileData[2])&LCDINVBITS)) currs=(fileData[2])&LCDBITS;//��� ������������ ��������� ������� �� ��������� ��������
    else currs=LCDBITS; 
    strcpy_P(buff, (char*)pgm_read_word(&(fileNames[fileData[1]])));//������ ����� ��������
    for (uint8_t i=0;i<=currs;i++)
    {
      sprintf(buff2, "%s %d", buff, (brCrumbs[level][1]&LCDINVBITS)+i);
      DispString(i,buff2);
    }
    break;
  case T_SFOLDER://����� ������ ���������
    uint8_t config_folder_view = pgm_read_byte(&fileStruct[FILEREW*fileData[1]+1]);//������ ���� ������.
    uint16_t config_folder_data =  ConfigReadWord(brCrumbs[level][0]+config_folder_view);//������ �������� ������
    if (config_folder_data>fileData[2]) config_folder_data=fileData[2];
    if (config_folder_view<0) config_folder_view=0;	 
    if (brCrumbs[level][2]==0){
      brCrumbs[level][1]=config_folder_data;//������ ������ � ��������� �������.
      brCrumbs[level][2]=1;
    }
    if ((brCrumbs[level][1]&LCDINVBITS)==((fileData[2])&LCDINVBITS)) currs=(fileData[2])&LCDBITS;//��� ������������ ��������� ������� �� ��������� ��������
    else currs=LCDBITS;	
    fstart=fileData[1]+(brCrumbs[level][1]&LCDINVBITS);//����� ����� ��� ������ ������.
    for (uint8_t i=0;i<=currs;i++)//����� �� ������� ��� ����������� �����
    {
      strlcpy_P(buff, (char*)pgm_read_word(&(fileNames[i+fstart])),sizeof(buff));//��������� ���
      DispString(i,buff);//����� �� �������
    }
    break;
  }   
	GLCD.InvertRect(0,POSYMIN+(brCrumbs[level][1]&LCDBITS)*MENUFOTNHIGHT,128,MENUFOTNHIGHT);
}

//���������� ��� ��� ���� ����
void DispFile(uint8_t str, uint8_t _fnumber, char* _buff){
	uint8_t _FileType=pgm_read_byte(&fileStruct[FILEREW*_fnumber]);//������ ��� �����
	uint8_t _ConfNumb;
	switch (_FileType)//���� ��������� � ����������� �� ���� �����.
  {
  //case T_FOLDER:
  //   break;
 // case T_APP:
  //  break;
  case T_CONF:
	_ConfNumb=pgm_read_byte(&fileStruct[FILEREW*_fnumber+1]);//������ ����� ������� 
	if ((str>=0) && (str<DISPSTR))//��������� ������� ������
 	 ConfigView(POSXMIN,POSYMIN+str*MENUFOTNHIGHT,_buff,_ConfNumb,0);
    break;
 // case T_DCONF:
 //   break;
 // case T_DFOLDER:
 //   break;
//  case T_SFOLDER:
 //   break;
 // case T_SCONF://���������� �������
 //   break;
	default:
      DispString(str,_buff);//����� �� �������
	break;
  }
	
}

//����� ��������� �����
void MenuButtonUp(){
	if (brCrumbs[level][1]>0){ 
		brCrumbs[level][1]--;

	}
    else{ 
		brCrumbs[level][1]=fileData[2];//����� �� ������, ������ � �����.	
	}
	PageList();
}

void MenuButtonDown(){
	if (brCrumbs[level][1]<fileData[2])
		brCrumbs[level][1]++;
    else
		brCrumbs[level][1]=0;//�� ����� ��� �� �����? ����� ��������� � ����. �����? �����, �������� �������
	PageList();
}

void MenuButtonLeft(){
	//��� ��������
}

void MenuButtonRight(){
	//��������� ��������������
	MenuButtonEnter();
}

void MenuButtonEnter(){
	if (!fileData[0])//������� �����. � ��� ��� ������ ������
  {
    fileNumb=fileData[1]+brCrumbs[level][1];//����� ����� ���������� ����� � ���������� ������� �� ���� ���������.
  }
  else //������������ ����� ��� ��� ��� �����
  {
    fileNumb=fileData[1];//����!
  }
  if (MAXDEPTH>level){//������ �� ����� �� ������� ������� ������� ������.
	level++;//�� ������� ������
  brCrumbs[level][0]=fileNumb;//����� ������? �����, ������� ���� � ����� ��������������.
  brCrumbs[level][1]=0;
  brCrumbs[level][2]=0;
  FileGet(fileNumb);//��������� ���������� 
  }  
  switch (fileData[0])//���� ��������� � ����������� �� ���� �����.
  {
  case T_FOLDER:
    PageList();
    break;
  case T_APP:
    ApplicationStart(fileData[2]);
    break;
  case T_CONF:
  	//������� ����� ������ �� ����������
	TManager.WorkType=1;
	TManager.TReload(3,*ApplicationStop,1);//�������� �����.	
   ConfigSetup(POSXMIN,POSYMIN+(brCrumbs[level-1][1]&LCDBITS)*MENUFOTNHIGHT,FileName,fileData[1],0);
    break;
  case T_DCONF:
  	//������� ����� ������ �� ����������
	TManager.WorkType=1;
	TManager.TReload(3,*ApplicationStop,1);//�������� �����.	
   ConfigSetup(POSXMIN,POSYMIN+(brCrumbs[level-1][1]&LCDBITS)*MENUFOTNHIGHT,FileName,fileData[1],brCrumbs[level-1][1]);
    break;
  case T_DFOLDER:
    PageList();
    break;
  case T_SFOLDER:
    PageList();
    break;
  case T_SCONF://���������� �������
    ConfigWriteWord(fileData[1]+brCrumbs[level-1][0],brCrumbs[level-1][1]);
ApplicationStart(0xFA);
    break;
  }
	
}

void MenuButtonReturn(){
	FileReturn();
}

void FileReturn(){
//�� ������, ������ ������� ���������� � ��������������:
  brCrumbs[level][0]=0;
  brCrumbs[level][1]=0;
  brCrumbs[level][2]=0;
  //�������� �� ������� �����, ������ ���� �� ��� ������ ����. � �� ����� ����� � ������.
  if (level>0) level--;//�������� �� ������ ����, ��� ����� �������� ���� � ��������:
  fileNumb=brCrumbs[level][0];//��� ���� ��������� ������� �� ������������! �� �������� ����, ������ ������.
  FileGet(fileNumb);//������ ���� � �����.
  PageList();	

}


//������� ��������� ������ � �����
void FileGet(uint8_t fnumb){
  for (uint8_t i=0;i<FILEREW;i++)
    fileData[i]=pgm_read_byte(&fileStruct[FILEREW*fnumb+i]);//��������� ������� ��������
  strlcpy_P(FileName, (char*)pgm_read_word(&(fileNames[fnumb])),sizeof(FileName));//��������� ��������	
	
}

//��� ���������� ���������� ������� ���������� �� 3 ����� ����������, ��������� ��������� ����������.
void ApplicationStop(){
	if (!TManager.WorkType)//���������� �����������.
		{
		TManager.TReload(3,*ApplicationStop,0);//��������� �����.
		GLCD.ClearScreen();
		MenuSetup();//��������� ������
		}

}

//��� ���������� ������������ ����.
void ApplicationStart(uint8_t AppNumber){
	//������� ����� ������ �� ����������
	TManager.WorkType=1;
	TManager.TReload(3,*ApplicationStop,1);//�������� �����.	
	switch (AppNumber){
		case 1:
		MotionViewSetup();
			//�������� ���������
		break;
		case 2:
			DriveTestSetup();
		break;
		case 0xFA://������� Saved �� �����
		GLCD.FillRect(46,28,36,8,WHITE);
		GLCD.CursorToXY(46,28);
		GLCD.Puts("Saved!");
		TManager.TReload(2,AppSaved,100);//�� 1 �������
		break;
		
	}
}

void AppSaved(){
	TManager.TReload(2,AppSaved,0);
	TManager.WorkType=0;
}