#pragma once

#include <iostream>
#include  <wiringPi.h> //подключаем заголовочный файл библиотеки

#include "controller.h"
#include "encoders.h"
#include "piezoPositioners.h"
#include "mask.h"
#include "motors.h"

class controller {
public:
	MotorStack motors;
	Mask mask;
	Encoders encoders;
	PiezoPositioners piezo;
	controller():
		motors(X_DIR_PIN, Y_DIR_PIN, X_STEP_PIN, Y_STEP_PIN,EN_PIN)	{
		wiringPiSetup();
		pinMode(X_DIR_PIN, OUTPUT);
		pinMode(Y_DIR_PIN, OUTPUT);
		pinMode(X_STEP_PIN, OUTPUT);
		pinMode(X_STEP_PIN, INPUT);
		pinMode(EN_PIN, INPUT);

	};
	void print() {};
};

