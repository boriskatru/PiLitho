#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>

#include "DAC.h"
#include "vecters.h"
using namespace std;

class PiezoPositioners
{
	Vecter last_move;
	Vecter position_V;
	Vecter position_nm;
	Vecter calibration_constant; // nm/V
	DAC X_DAC;
	DAC Y_DAC;
	DAC Z_DAC;
	//double coarse_pos;
	void UpdatePos(Vecter position, char unit = 'V');
	void UpdatePos(double positionZ, char unit = 'V');
public:
	double capacity;
	double resistivity;
	double cutoff_freq;
	double crit_jump;
	Vecter V_uplimit, V_downlimit;
	PiezoPositioners(double _capacity = 0.000001, double _resistivity = 0, double _cutoff_freq = 200000, Vecter _calibration = Vecter(300, 750, 750));
	~PiezoPositioners();

	double Position(char axis = 'Z', char unit = 'V');
	void Jump(Vecter step, const char unit = 'V');
	void JumpTo(Vecter position, const char unit = 'V');
	void ZJump(double step, const char unit = 'V');
	void ZJumpTo(double position, const char unit = 'V');
	void Move(Vecter distance, double delay_micro, double djump, double (*check)(double) = NULL);
	void MoveTo(Vecter destination, double delay_micro, double djump, double (*check)(double) = NULL);

};