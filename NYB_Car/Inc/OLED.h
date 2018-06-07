#ifndef _OLED_H
#define _OLED_H

typedef unsigned char byte;
typedef unsigned int word;

 extern byte lanzhou96x64[768];
 extern void LCD_Init(void);
 extern void LCD_CLS(void);
 extern void LCD_P6x8Str(unsigned char  x,unsigned char  y,char  ch[]);
 //void LCD_P8x16Str(uint8  x,uint8  y,uint8  ch[]);
 //void LCD_P14x16Str(uint8  x,uint8  y,uint8  ch[]);
 //void LCD_Print(uint8  x, uint8  y, uint8  ch[]);
 void LCD_PutPixel(unsigned char  x,unsigned char  y);
 void LCD_PutPixel1(unsigned char  x,unsigned char  y);
 void LCD_Rectangle(unsigned char  x1,unsigned char  y1,unsigned char  x2,unsigned char  y2,unsigned char  gif);

 void Draw_BMP(unsigned char  x0,unsigned char  y0,unsigned char  x1,unsigned char  y1,unsigned char  bmp[]); 
 void LCD_Fill(unsigned char  dat);
 void Dly_ms(int ms) ;
 void Dis_Num(unsigned char  y, unsigned char  x, unsigned int num,uint8  N);
 void LCD_P8x16Str(unsigned char x,unsigned y,char ch[]);
 void LCD_Set_Pos(unsigned char x, unsigned char  y);
 void LCD_WrDat(unsigned char data);
 extern void LCD_Draw_One_Row(unsigned char  x,unsigned char  y,char row);

 
#endif

