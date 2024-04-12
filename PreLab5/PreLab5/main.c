//***********************************************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Héctor Martínez - 22369
// Proyecto: prelab 5
// Hardware: ATmega328p
//***********************************************************************************************

	#define F_CPU 16000000UL
    #include <avr/io.h>
    #include <util/delay.h>

    #define SERVO_MIN_POS 1999 // 0 grados
    #define SERVO_MAX_POS 3999 // 180 grados

    uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);

    int main(void)
    {
	    DDRB |= (1<<PB1); //Configurar PB1 como salida

	    ADMUX |= (1<<REFS0) | (1<<MUX0); // Establece el voltaje de referencia en AVCC y selecciona ADC1 como entrada
	    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Habilita ADC y establece el prescaler en 64

	    TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM no invertido
	    TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM
	    ICR1=39999;   // Período PWM de 20 ms

	    while (1){
		    ADCSRA |= (1<<ADSC); // Iniciar la conversión ADC
		    while (ADCSRA & (1<<ADSC)); 
		    uint8_t pot_val = ADC; 
		    uint8_t servo_pos = map(pot_val, 0, 1023, SERVO_MIN_POS, SERVO_MAX_POS); // Asigna posición del servo
		    OCR1A = servo_pos;
		    _delay_ms(1000); // Delay para posición de servo
	    }
    }

    uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max)
    {
	    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

