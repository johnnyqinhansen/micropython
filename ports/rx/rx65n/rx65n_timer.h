/*
 * Copyright (c) 2018, Kentaro Sekimoto
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  -Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *  -Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RX65N_TIMER_H_
#define RX65N_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MICROPY_HW_MCU_PCLK
#define MICROPY_HW_MCU_PCLK 60000000
#endif

#define DEF_CLKDEV  8
#define TENUSEC_COUNT   (MICROPY_HW_MCU_PCLK / DEF_CLKDEV / 100000)
#define MSEC_COUNT      (MICROPY_HW_MCU_PCLK / DEF_CLKDEV / 100)

#define CLKDEV  DEF_CLKDEV
#if CLKDEV == 8
#define CMT_VAL 0x0040;     // CMIE is Enable,CKS is PCLK/8     clk=1/6(us)
#elif CLKDEV == 32
#define CMT_VAL 0x0041;     // CMIE is Enable,CKS is PCLK/32    clk=1/1.5(us)
#elif CLKDEV == 128
#define CMT_VAL 0x0042;     // CMIE is Enable,CKS is PCLK/128   clk=32/12(us)
#else
#define CMT_VAL 0x0043;     // CMIE is Enable,CKS is PCLK/512   clk=128/3(us)
#endif

/*
 * Prescale: 8
 * freq = 1000(1/s) = 1000(us) -> 7500
 * freq = 10000(1/s) = 100(us) -> 750
 * freq = 100000(1/s) = 10(us) -> 75
 */

#include <stdint.h>
typedef void (*CMT_TIMER_FUNC)(void *);

void cmt_timer_init(unsigned int ch, unsigned int prescale);
void cmt_timer_deinit(unsigned int ch);
void cmt_timer_disable_clk(unsigned int ch);
void cmt_timer_eable_clk(unsigned int ch);
unsigned int cmt_timer_get_prescale(unsigned int ch);
void cmt_timer_set_prescale(unsigned int ch, unsigned int prescale);
unsigned int cmt_timer_get_counter(unsigned int ch);
void cmt_timer_set_counter(unsigned int ch, unsigned int count);
void cmt_timer_set_callback(unsigned int ch, CMT_TIMER_FUNC func, void *param);
void cmt_timer_callback(unsigned int ch);
unsigned long cmt_timer_get_cnt(unsigned int ch);
void cmt_timer_set_cnt(unsigned int ch, unsigned long cnt);
unsigned long cmt_timer_get_period(unsigned int ch);
void cmt_timer_set_period(unsigned int ch, unsigned long period);

void udelay_init(void);
void udelay(int m);
void mdelay(int m);
unsigned long utick(void);
unsigned long mtick(void);

#ifdef __cplusplus
}
#endif

#endif /* RX65N_TIMER_H_ */
