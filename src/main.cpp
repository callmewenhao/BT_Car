/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 如果使用 ESP8266 接入 Blinker,
 * 请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
 * https://github.com/esp8266/Arduino/releases
 * 
 * 如果使用 ESP32 接入 Blinker,
 * 请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * 文档: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************/

#define BLINKER_BLE

#include <Blinker.h>
#include <motor.h>

#define BUTTON_1 "go1"
#define JOY_1 "handler1"

#define LEFT_EN 5
#define RIGHT_EN 27

int16_t y_value = 0;
int16_t x_value = 0;
int16_t left_pwm_value = 0;
int16_t right_pwm_value = 0;

BlinkerButton Button1(BUTTON_1);
BlinkerJoystick JOY1(JOY_1);

Motor left_motor(25, 8, 26, 9);
Motor right_motor(18, 10, 19, 11);

void SpeedControl(uint8_t xAxis, uint8_t yAxis);
void button1_callback(const String & state)
{
    //Serial.println("OK!");
    /* 该段代码用于停车，有待完善 */
    ledcWrite(8, 0);
    ledcWrite(9, 0);

    ledcWrite(10, 0);
    ledcWrite(11, 0);
}

void joystick1_callback(uint8_t xAxis, uint8_t yAxis)
{
    SpeedControl(xAxis, yAxis);
}

void setup()
{
    Serial.begin(115200);
    Blinker.begin();
    Button1.attach(button1_callback);
    JOY1.attach(joystick1_callback);
    
    pinMode(LEFT_EN, OUTPUT);
    digitalWrite(LEFT_EN, LOW);
    pinMode(RIGHT_EN, OUTPUT);
    digitalWrite(RIGHT_EN, LOW);

    left_motor.MotorInit(13*1000, 8); //0~255
    right_motor.MotorInit(13*1000, 8); //0~255
}

void loop()
{
    Blinker.run();
}

/* Output Limitation */
int16_t OutputLimitation(int16_t pwm_value){
    if(pwm_value < -255)
        return -255;
    else if (pwm_value > 255)
        return 255;
    else
        return pwm_value;
}

void SpeedControl(uint8_t xAxis, uint8_t yAxis){
    y_value = 128 - yAxis; // up 128, down -127
    x_value = 128 - xAxis; // left 128, right -127

    left_pwm_value = y_value - x_value;
    right_pwm_value = y_value + x_value;

    /* Output limitation */
    left_pwm_value = OutputLimitation(left_pwm_value);
    right_pwm_value = OutputLimitation(right_pwm_value);

    /* Go */
    left_motor.MotorGo(left_pwm_value);
    right_motor.MotorGo(right_pwm_value);
    // Serial.print(left_pwm_value);
    // Serial.println(right_pwm_value);

}
