#ifndef _GAME_H
#define _GAME_H

extern uint8 Game_Mode;
extern uint8 Game_Mode_;
extern uint8 Game_Key;
#define game_NO    0
#define game_UP    1
#define game_DOWN  2 
#define game_LEFT  3
#define game_RIGHT 4
typedef enum GameStatus
{ 
  ING,OVER,START
}GST;

typedef enum Move_Flag
{ 
  Left,Right,Up,Down
}MF;

typedef struct BoxArrays   /*存放所有蛇的位置*/
{
    char x;
    char y;
    char color;
}BA;

typedef enum GameMode
{ 
  NUMSnake,NUMBTrix
}GM; 

extern GST Gamestatus;
extern GST Gamestatus_Pre;
extern void Snake(void);
extern void Telecontrol(void);
extern uint16 Data[125];
extern uint16 AD_Data;

//#define Game_EN 1

#endif