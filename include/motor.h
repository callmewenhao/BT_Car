#ifndef __MOTOR_H
#define __MOTOR_H

#include <Arduino.h>

class Motor
{
    public:
        Motor(uint8_t f, uint8_t f_c, uint8_t b, uint8_t b_c):
            motor_f(f), motor_b(b), motor_f_c(f_c), motor_b_c(b_c) {}
        void MotorInit(uint16_t fre, uint8_t range);
        void MotorGo(int8_t pwm_value);
    private:
        uint8_t motor_f;//attention: the sequence of initlizing parameters must match the definition sequence
        uint8_t motor_b;
        uint8_t motor_f_c;
        uint8_t motor_b_c;
};

#endif
