#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "main.h"

/**
*@brief Button configuration (PA0)
*/
void button_init(void);

/**
*@brief Read push button (PA0)
*
*@return Button state (0 or 1)
*/
uint8_t button_read(void);

#endif /* __BUTTON_H__ */
