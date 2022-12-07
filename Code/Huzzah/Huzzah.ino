//LCD imports
#include <SPI.h>
#include "LCD_Driver.h"
#include "LCD_GUI_Paint.h"
#include "LCD_Images.h"

void setup() {
  initialiseLCDScreen();
}


void loop() {
    drawFlagOnScreen();
}


//Preparing & clearing LCD screen
void initialiseLCDScreen(){
  Config_Init();
  LCD_Init();
  
  LCD_SetBacklight(1000);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);
  Paint_Clear(BLACK);
}

//LCD screen output
void drawFlagOnScreen(){
    Paint_Clear(BLACK);
    Paint_DrawImage(gImage_Brazil, 0, 0, 120, 240); 
    Paint_DrawImage(gImage_Ghana, 120, 0, 240, 240); 
}
