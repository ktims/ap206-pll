#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// 11.0592 MHz / 32 (clkps) = 345.6 KHz
// 345.6 KHz / 64 (timps) = 5.4 KHz
// 5.4 KHz / 20 = 135 | / 27 = 100
#define OCR_33  (135 - 1)
#define OCR_45  (100 - 1)

FUSES = {
    .low = 0xff,
    .high = 0xdf,
    .extended = EFUSE_DEFAULT,
};

void set_speed() {
    OCR0A = (PINB & _BV(PB1)) ? OCR_33 : OCR_45;
}

void init_io() {
    DDRB = _BV(DDB0); // OCR0A
    PORTB = _BV(PB1); // 33/45 switch pullup
}

void init_timer() {
    // Toggle & clear on compare match
    TCCR0A = _BV(COM0A0) | _BV(WGM01);
    
    // Set speed based on switch setting
    set_speed();
}

void init_interrupt() {
    GIMSK = _BV(PCIE);
    PCMSK = _BV(PCINT1);
    sei();
}

void start_timer() {
    TCCR0B = _BV(CS01) | _BV(CS00);
}

int main() {
    init_io();
    init_interrupt();
    init_timer();

    clock_prescale_set(clock_div_32);

    start_timer();

    set_sleep_mode(SLEEP_MODE_IDLE);

    for (;;)
        sleep_enable();
}

ISR(PCINT0_vect) {
    // No need to check pin state, just set speed
    set_speed();
}