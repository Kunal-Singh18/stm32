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
void tim4_pd12_output_compare(void);

void tim1_pa8_input_capture(void);

#define SR_CC1IF   (1U<<1)

#endif /* TIMER_H_ */
