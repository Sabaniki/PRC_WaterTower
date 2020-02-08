//
// Created by 澤田開杜 on 2020/02/08.
//
#include "PinDefs.h"
#include "Variables.h"
#include "Arduino.h"
#include "UltrasonicSensor.h"
#include "Servo.h"

void setup() {
    // Serial.begin(9600);
}

void loop() {
    auto ultrasonicSensor = UltrasonicSensor(TRIGGER_PIN, ECHO_PIN);
    auto servo = Servo();
    servo.attach(SERVO_PIN);
    while (true) {    // 汽車が来るまで時間を無限に潰します
        double distance = 0.0;
        for (int i = 0; i < TIMES; i++) distance += ultrasonicSensor.readDistance();
        distance /= TIMES;
        if (distance < DETECTION_STANDARD_DISTANCE) break;
    }
    delay(WAITING_TIME);    // 汽車回転待ち
    servo.write(SERVO_ANGLE);
    while (true);    // 終了後に無限に捕まえる
}