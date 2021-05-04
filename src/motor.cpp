#include <motor.h>

/* class func definition */
/* initial func */
void Motor::MotorInit(uint16_t fre, uint8_t range)
{
    ledcSetup(motor_f_c, fre, range); // 0~128
    ledcAttachPin(motor_f, motor_f_c);

    ledcSetup(motor_b_c, fre, range);
    ledcAttachPin(motor_b, motor_b_c);

    ledcWrite(motor_f_c, 0);
    ledcWrite(motor_b_c, 0);
}
/* 使用该函数前请确保输出限幅 */
void Motor::MotorGo(int8_t pwm_value){
    if(pwm_value > 0){
        // straight
        ledcWrite(motor_f_c, pwm_value);
        ledcWrite(motor_b_c, 0);
    } else if(pwm_value < 0){
        // back
        ledcWrite(motor_f_c, 0);
        ledcWrite(motor_b_c, -pwm_value);
    }
}

