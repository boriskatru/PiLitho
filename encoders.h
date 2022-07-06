#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>

#include "vecters.h"
#include "ADC.h"
using namespace std;
class Encoders{
public:
	ADC X_ADC;
	ADC Y_ADC;
//	ADC Z_ADC;
	Encoders() {}
	Vecter get_pos() {};
};

