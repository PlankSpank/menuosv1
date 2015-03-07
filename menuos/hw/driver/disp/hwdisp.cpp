/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#include "hwdisp.h"

/*===================================================================
					DISPLAY HW ROUTINE ACCESS
===================================================================*/
#if defined (TEXT_DISPLAY)

	LiquidCrystal lcd;

#endif


 
uint8_t HwDispSetup(void){
	#if defined(TEXT_DISPLAY)
		lcd.begin(16,2);
	#endif
	
	#if defined(GRAPH_DISPLAY)
		GLCD.Init(NON_INVERTED);
		GLCD.ClearScreen();
		GLCD.SelectFont(MENUFONT);
	#endif
	return 0;
}

uint8_t HwDispPutChar(uint8_t row, uint8_t col, char symbol){
//check stirng bound
if ((row >= 0) && (row < DISPSTRNUMB)){
	#if defined(TEXT_DISPLAY)
		lcd.setCursor(col, row);
		lcd.print(symbol);
	#endif
	
	#if defined(GRAPH_DISPLAY)
		HwDispClearString(row, col, DISPSTRNUMB-col);
		GLCD.CursorToXY(XINDENT+1+col*MENUFONTWIDTH,YINDENT+1+row*MENUFONTHEIGHT);//set cursor
		GLCD.PutChar(symbol);//write
	#endif
	
}
return 0;	
}


uint8_t HwDispPutString(uint8_t row, uint8_t col, char* text, uint8_t length){
	//check stirng bound
	if ((row >= 0) && (row < DISPSTRNUMB)){
		#if defined(TEXT_DISPLAY)
			col+=1;//make left position free
			lcd.setCursor(col, row);
			lcd.print(text);
		#endif
	
		#if defined(GRAPH_DISPLAY)
			HwDispClearString(row, col, DISPSTRNUMB-col);
			GLCD.CursorToXY(XINDENT+1+col*MENUFONTWIDTH,YINDENT+1+row*MENUFONTHEIGHT);//set cursor
			GLCD.Puts(text);//write
		#endif
		
	}
	return 0;
}

uint8_t HwDispClearString(uint8_t row, uint8_t col, uint8_t length){
	//check stirng bound
	if ((row >= 0) && (row < DISPSTRNUMB)){
	#if defined(TEXT_DISPLAY)
		for (uint8_t i = col; i < col + length; i++){
			HwDispPutChar(row, i, ' ');//put spaces
		}
	#endif
	
	#if defined(GRAPH_DISPLAY)
		GLCD.FillRect(XINDENT, YINDENT + row * MENUFONTHEIGHT, LCDWIDTH - XINDENT, MENUFONTHEIGHT, WHITE);
						
	#endif
		
	}	
	return 0;
}

uint8_t HwDispSelectString(uint8_t row){
//check stirng bound
	if ((row >= 0) && (row < DISPSTRNUMB)){
	#if defined(TEXT_DISPLAY)
		lcd.setCursor(0, row);
		lcd.print(">");
	#endif
	
	#if defined(GRAPH_DISPLAY)
		GLCD.InvertRect(XINDENT, YINDENT + row*MENUFONTHEIGHT, LCDWIDTH - XINDENT,MENUFONTHEIGHT);
	#endif
		
	}
	return 0;
}

uint8_t HwDispDrawCursor(uint8_t row, uint8_t col, uint8_t length){
	if ((row >= 0) && (row < DISPSTRNUMB)){
		#if defined(TEXT_DISPLAY)
			lcd.setCursor(0, row);
			lcd.print(">");
		#endif
		
		#if defined(GRAPH_DISPLAY)
			GLCD.DrawRect(XINDENT + col*MENUFONTWIDTH, YINDENT + row*MENUFONTHEIGHT, length * MENUFONTWIDTH, MENUFONTHEIGHT);
		#endif
		
	}
	return 0;	
}


void HwDispClearScreen(void){
	#if defined(TEXT_DISPLAY)
		lcd.clear();
	#endif
	
	#if defined(GRAPH_DISPLAY)
		GLCD.ClearScreen();
	#endif	
}

uint8_t HwDispGetStringsNumb(void){
	return DISPSTRNUMB;
}

uint8_t HwDispGetStringsLength(void){
	return DISPSTRLENGTH;
}
