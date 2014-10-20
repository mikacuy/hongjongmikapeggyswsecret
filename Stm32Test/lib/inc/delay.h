#ifndef __DELAY_H
#define __DELAY_H
#include <stdint.h>
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

void _delay_us( uint32_t nus);
void _delay_ms( uint16_t nms );

void simple_delay1_ms( void );
void simple_delay10_us( void  );
#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H */

