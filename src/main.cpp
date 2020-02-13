//
// Created by 澤田開杜 on 2020/02/08.
//
#include "PinDefs.h"
#include "Variables.h"
#include "Arduino.h"
#include "UltrasonicSensor.h"
#include "Servo.h"

void setup() {
    Serial.begin(9600);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void loop() {
    Serial.println("start");
    delay(50);
    auto ultrasonicSensor = UltrasonicSensor(TRIGGER_PIN, ECHO_PIN);
    auto servo = Servo();
    servo.attach(SERVO_PIN);
    Serial.println("init was done.");

    while (true) {    // 汽車が来るまで時間を無限に潰します
        double distance = 0.0;
        for (int i = 0; i < TIMES; i++) distance += ultrasonicSensor.readDistance();
        distance /= TIMES;
        Serial.print("distance: ");
        Serial.print(distance);
        Serial.println("cm");
        if (DETECTION_STANDARD_DISTANCE_MIN < distance && distance < DETECTION_STANDARD_DISTANCE_MAX) break;
    }
    delay(WAITING_FOR_TRAIN_TIME);    // 汽車回転待ち
    Serial.println("waiting for train done");
    servo.write(SERVO_ANGLE);
    delay(WAITING_FOR_WATER_SUPPLY);
    servo.write(0);
    Serial.println("done");
    while (true);    // 終了後に無限に捕まえる
}
#pragma clang diagnostic pop