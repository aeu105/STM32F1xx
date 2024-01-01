#ifndef __BSP_MUSIC_H__
#define __BSP_MUSIC_H__


#include <stm32f10x.h>


extern unsigned int tone[];
extern unsigned int star[];
extern unsigned int little_star[][2];

void Display_Sound(unsigned int fre);


#endif	/* __BSP_MUSIC_H__ */
