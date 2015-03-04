/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

/***
 *  This file define any links to hardware API or drivers.
 *  This file is used for RLN electro buttons and text LCD definition 
 *  
 */
 #ifndef HWI_H_
 #define HWI_H_
 
 //main system definitions
 #include "hwdef.h"
 
 //main menu definitions
 #include "menudef.h"

 //file structure file
 #include "static.h"
  
/*===================================================================
					BUTTONS HW ROUTINE ACCESS
===================================================================*/
 /**
 *  \brief Return number of buttons
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
 uint8_t HwButtonsCount();  
 
 /**
 *  \brief Configure buttons port
 *  
 *  \param [in] mode not used
 *  \return buttons mask
 *  
 *  \details Details
 */
uint8_t HwButtonsSetup(uint8_t mode);


/**
 *  \brief Return pressed buttons mask
 *  
 *  \param [in] mode not used
 *  \return current buttons mask
 *  
 *  \details Details
 */
uint8_t HwButtonsState(uint8_t mode); 
 
 
/*===================================================================
					DISPLAY HW ROUTINE ACCESS
===================================================================*/

 /**
 *  \brief Display Setup
 *  
 *  \return 0 if good
 *  
 *  \details Details
 */
uint8_t HwDispSetup(void);

/**
 *  \brief Put symbol to position
 *  
 *  \param [in] row selected row
 *  \param [in] col selected column
 *  \param [in] symbol symbol to put out
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwDispPutChar(uint8_t row, uint8_t col, char symbol);

/**
 *  \brief Put string to position
 *  
 *  \param [in] row selected row for first symbol
 *  \param [in] col selected column for first symbol
 *  \param [in] symbols text string
 *  \param [in] length string length
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwDispPutString(uint8_t row, uint8_t col, char* symbols, uint8_t length);

/**
 *  \brief Draw Cursor at defined position
 *  
 *  \param [in] row selected row
 *  \param [in] col selected column
 *  \param [in] length cursor length
 *  \return 0
 *  
 *  \details 
 */
uint8_t HwDispDrawCursor(uint8_t row, uint8_t col, uint8_t length);

/**
 *  \brief Add string selection.
 *  
 *  \param [in] row selected row
 *  \return 0
 *  
 *  \details 
 *  for symbolic LCD add > symbol to left position
 *  for GLCD - invert all string
 */
uint8_t HwDispSelectString(uint8_t row);

/**
 *  \brief Clear selected string
 *  
 *  \param [in] row selected row
 *  \param [in] col start column
 *  \param [in] length clear length
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwDispClearString(uint8_t row, uint8_t col, uint8_t length);

/**
 *  \brief Return strings count
 *  
 *  \return strings count
 *  
 *  \details Details
 */
uint8_t HwDispGetStringsNumb(void);

uint8_t HwDispGetStringsLength(void);

void HwDispClearScreen(void);


/*===================================================================
					FILE STRUCTURE ACCESS
===================================================================*/

/**
 *  \brief Return file info
 *  
 *  \param [in] filenumber number of selected file
 *  \param [in] file filedata structure
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwFileGetInfo(uint8_t filenumber, filedata* file);

/**
 *  \brief Return file info
 *  
 *  \param [in] filenumber number of selected file
 *  \param [in] file byte position to read
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwFileGetInfo(uint8_t filenumber, uint8_t pos);

/**
 *  \brief Read file name from memory
 *  
 *  \param [in] filenumb file number id
 *  \param [in] name char array
 *  \return 0
 *  
 *  \details Details
 */
uint8_t HwFileGetName(uint8_t filenumb, char* name);

/**
 *  \brief Get file type
 *  
 *  \param [in] filenumb file number id
 *  \return file type
 *  
 *  \details Details
 */
uint8_t HwFileGetType(uint8_t filenumb);


/*===================================================================
					CONFIG STRUCTURE ACCESS
===================================================================*/

/**
 *  \brief Read config data from structure and memory
 *  
 *  \param [in] configid config number
 *  \param [in] config config strtucture
 *  \param [in] shift dynamic config shift
 *  \return 0 if success, 1 in any error
 *  
 *  \details Details
 */
uint8_t HwConfigGetData(uint8_t configid, configdata* config, uint16_t shift);

/**
 *  \brief Store config value in memory
 *  
 *  \param [in] configid config number
 *  \param [in] config config structure
 *  \param [in] shift dynamic config shift
 *  \return 0 if success, 1 in any error
 *  
 *  \details Details
 */
uint8_t HwConfigSetData(uint8_t configid, configdata* config, uint16_t shift);
 
 #endif //HWI_H_
 