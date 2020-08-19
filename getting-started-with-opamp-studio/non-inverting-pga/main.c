/*
 * \file main.c
 *
 * \brief Main source file.
 *
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms,you may use this software and
 *  any derivatives exclusively with Microchip products.It is your responsibility
 *  to comply with third party license terms applicable to your use of third party
 *  software (including open source software) that may accompany Microchip software.
 *
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 *  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 *  PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 *  ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 *  THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */


#include <avr/io.h>
#include <avr/cpufunc.h>
#include "src/rtc.h"
#include "src/adc.h"
#include "src/dac.h"
#include "src/uart.h"

/*Configure system fuses ensuring known start condition for MCU*/

FUSES = {
    .WDTCFG = FUSE_WDTCFG_DEFAULT,
    .BODCFG = FUSE_BODCFG_DEFAULT,
    .OSCCFG = FUSE_OSCCFG_DEFAULT,
    .SYSCFG0 = FUSE_SYSCFG0_DEFAULT,
    .SYSCFG1 = (1 << FUSE_MVSYSCFG0_bp) | SUT_64MS_gc,
    .CODESIZE = FUSE_CODESIZE_DEFAULT,
    .BOOTSIZE = FUSE_BOOTSIZE_DEFAULT
};

void GPIO_init(void);
void OPAMP0_init(void);

int main(void)
{
    /* Set Main Clock to 24 MHz */
    ccp_write_io((void*)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc);

    GPIO_init();

    LED0_init();

    RTC_init();     /*1s interrupt timer*/

    DAC0_init();    /*Creates and outputs the sine waveform*/

    USART_init();   /*Streams data into Data Visualizer*/

    ADC0_init();    /*Acquire Signal from OPAMP0 output*/

    /*Start the timer controlling the sine waveform generator 
    and the timer controlling the acquisition */
    SINE_WAVE_TIMER.CTRLA |= TCB_ENABLE_bm;
    ADC_SAMPLE_TIMER.CTRLA |= TCB_ENABLE_bm;

    OPAMP0_init();

    RTC_enable();

    sei();          /*Enable global interrupts*/

    while (1) 
    {
        ;
    }
}

#define OPAMP_TIMEBASE_US     (ceil(F_CPU /1e6)-1)

void OPAMP0_init (void)
{
    /* Configure the Timebase */
    OPAMP.TIMEBASE = OPAMP_TIMEBASE_US;

    /* Configure the Op Amp n Control A */
    OPAMP.OP0CTRLA = OPAMP_OP0CTRLA_OUTMODE_NORMAL_gc | OPAMP_ALWAYSON_bm;

    /* Configure the Op Amp n Input Multiplexer */
    OPAMP.OP0INMUX = OPAMP_OP0INMUX_MUXNEG_WIP_gc | OPAMP_OP0INMUX_MUXPOS_DAC_gc;

    /* Configure the Op Amp n Resistor Wiper Multiplexer */
    /* WIP3 => R1 = 8R, R2 = 8R */
    /* Gain = 1 + R2/R1 = 2 */
    OPAMP.OP0RESMUX =  OPAMP_OP0RESMUX_MUXBOT_GND_gc | OPAMP_OP0RESMUX_MUXWIP_WIP3_gc | OPAMP_OP0RESMUX_MUXTOP_OUT_gc;

    /* Configure the Op Amp n Settle Time*/
    OPAMP.OP0SETTLE = 0x7F;

    /* Enable OPAMP peripheral */
    OPAMP.CTRLA = OPAMP_ENABLE_bm;

    /* Wait for the operational amplifiers to settle */
    while (!(OPAMP.OP0STATUS & OPAMP_SETTLED_bm))
    {
        ;
    }
}

void GPIO_init(void)
{
    /* Disable digital input buffer*/
    PORTD.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
}
