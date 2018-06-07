#ifndef __SOUND_H__
#define __SOUND_H__

extern void sound_init(void);
void kaiji_fmq(void);
//void key_fmq(void);
extern void up_fmq(void);
extern void down_fmq(void);
extern void left_fmq(void);
extern void right_fmq(void);
extern void ok_fmq(void);
extern void ok_hold_fmq(void);
extern void Warning_fmq(void);
extern void FMQ_ON(void);
extern void FMQ_OFF(void);
void  delay_fmq(uint32  ms);

#define  BEE_OPEN  FMQ_ON()
#define  BEE_CLOSE FMQ_OFF()
#define  offWARNING FMQ_OFF()
#define  WARNING Warning_fmq()

#endif
