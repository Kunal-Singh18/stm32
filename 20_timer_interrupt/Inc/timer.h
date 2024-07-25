/*
 * timer.h
 *
 *  Created on: Jul 13, 2024
 *      Author: kunal
 */

#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIF  (1U<<0)

void tim3_1hz_init(void);
void tim3_1hz_interrupt_init(void);


#endif /* TIMER_H_ */
