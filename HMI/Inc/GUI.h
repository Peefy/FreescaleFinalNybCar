/*****************************************************************
#include "GUI.h"
******************************************************************/

#ifndef GUI_H
#define GUI_H

#include "GUIcustom.h"


enum Command{PageUp,PageDown,
             Select,Exit,
             SelectUp,SelectDown,
             Save,
             Minus,Add,
             DoCmd,
             ModeUp,ModeDown,
             None};
enum CommandState{Begin,Finished,Sleep};

enum ProgramSate{Changing,Saved,CMDstate};

enum ChangeState{Once,Continue};

typedef struct GUIStatusType
{
const uint8 ItemNumMaxInPage;
const uint8 ItermTotal;
uint8 index_FirstItermInPage;
uint8 ItermNum;
uint8 ItermIndex;
}GUIStatusType;


extern enum Command ActCommand;
extern enum CommandState ActCommandState;
extern enum ProgramSate  ActProgramSate;
extern enum ChangeState  ActChangeState;
#ifdef PANNEL_SEND_DATA
extern s32 GUI_ParaFromCOM[Iterm_TOTAL];
extern s32 Para16s[Iterm_TOTAL];
#endif
extern GUIStatusType GUI_PublicStatus;

void Gui(void);
void GUI_Sleep(void);
uint8 GUI_IsSleep(void);


#endif
