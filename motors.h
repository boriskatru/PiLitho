#pragma once

#include <iostream>
#include <wiringPi.h>
#include "vecters.h"

#define FORWARD HIGH
#define BACKWARD LOW
#define ENABLE HIGH
#define DISABLE LOW

#define X_DIR_PIN 0
#define Y_DIR_PIN 0
#define X_STEP_PIN 0
#define Y_STEP_PIN 0
#define EN_PIN 0

#define STEPS_PER_CIRCLE 200	// шагов на полный оборот
#define SCREW_PITCH 1000		// шаг винтав микронах


inline bool H_step(double x) {
	if (x < 0)return 0;
	return 1;
}
using namespace std;
class uart {};
class Motor {
public:
	int dir_pin;
	int en_pin;
	int step_pin;
	int microstep;
	int step_delay;		// задержка шага в микросекундах
	double position;
	uart uart_port;
	/// <summary>
	/// конструктор класса
	/// </summary>
	/// <param name="dir"> direction pin</param>
	/// <param name="en"> enable pin</param>
	/// <param name="step"></param>
	/// <param name="stp_per_crcl"></param>
	/// <param name="microstp"></param>
	/// <param name="scr_pitch"></param>
	Motor(int dir, int en,int step, int delay = 100, int microstp = 256) :
		dir_pin(dir),
		en_pin(en),
		step_pin(step),
		position(0),
		step_delay(delay),
		microstep(microstp) {
		driver_on();
	}
	/// <summary>
	/// отключает драйвер мотора
	/// </summary>
	void driver_off() {
		digitalWrite(en_pin, DISABLE);
	}
	/// <summary>
	/// включает драйвер мотора
	/// </summary>
	void driver_on() {
		digitalWrite(en_pin, ENABLE);
	}
	/// <summary>
	/// Единичный шаг
	/// </summary>
	void step() {
		digitalWrite(step_pin, HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(step_pin, LOW);
		delayMicroseconds(step_delay);
	}
	/// <summary>
	/// Перемещение В заданную позицию
	/// </summary>
	/// <param name="pos"> конечная позиция</param>
	void move_to(double pos) {
		digitalWrite(dir_pin, H_step(pos - position));
		for (int i = 0; i < abs(pos - position) * microstep / SCREW_PITCH * STEPS_PER_CIRCLE; i++) {
			step();
		}
		position = pos;
	}
	/// <summary>
	/// Перемещение НА заданную дистанцию
	/// </summary>
	/// <param name="dist">дистанция для перемещения</param>
	void move(double dist) {
		move_to(dist + position);
	}
	

};

class MotorStack{
public:
	int x_step_pin;
	int x_dir_pin;
	int y_step_pin;
	int y_dir_pin;
	int microstep;
	// int z_step_pin;
	// int z_dir_pin;
	Vecter position;
	Vecter uplimit, downlimit;
	int en_pin;
	int step_delay;		// задержка шага в микросекундах
	MotorStack(int x_dir_pin, int y_dir_pin, int x_step_pin, int y_step_pin,/* int z_dir_pin, int z_step_pin*/ int en_pin , int delay = 100, int microstp = 256):
		x_dir_pin(x_dir_pin),
		y_dir_pin(y_dir_pin),
		en_pin(en_pin),
		x_step_pin(x_step_pin),
		y_step_pin(y_step_pin),
		step_delay(delay),
		microstep(microstp){
		driver_on();
	}
	/// <summary>
	/// отключает драйвер мотора
	/// </summary>
	void driver_off() {
		digitalWrite(en_pin, DISABLE);
	}
	/// <summary>
	/// включает драйвер мотора
	/// </summary>
	void driver_on() {
		digitalWrite(en_pin, ENABLE);
	}
	void set_position(Vecter pos) {
		position = pos;
	}
	void set_position(double x_pos, double y_pos, double z_pos=0) {
		position = Vecter(x_pos,y_pos,z_pos);
	}
	void step_X() {
		digitalWrite(x_step_pin, HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(x_step_pin, LOW);
		delayMicroseconds(step_delay);
	}
	void step_Y() {
		digitalWrite(y_step_pin, HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(y_step_pin, LOW);
		delayMicroseconds(step_delay);
	}
	/*void step_Z() {
		digitalWrite(z_step_pin, HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(z_step_pin, LOW);
		delayMicroseconds(step_delay);
	}*/
	void sync_step() {
		digitalWrite(x_step_pin, HIGH);
		digitalWrite(y_step_pin, HIGH);
		//digitalWrite(z_step_pin, HIGH);
		delayMicroseconds(step_delay);
		digitalWrite(x_step_pin, LOW);
		digitalWrite(y_step_pin, LOW);
		//digitalWrite(z_step_pin, LOW);
		delayMicroseconds(step_delay);
	}
	/// <summary>
	/// Перемещение В заданную позицию
	/// </summary>
	/// <param name="pos"> конечная позиция</param>
	void move_to(Vecter pos) {
		driver_on();

		digitalWrite(x_dir_pin, H_step((pos - position).x_proj));
		digitalWrite(y_dir_pin, H_step((pos - position).y_proj));
		//digitalWrite(z_dir_pin, H_step((pos - position).z_proj));
		double x_mv = (pos - position).x_proj;
		double y_mv = (pos - position).y_proj;
		double min_mv = min(x_mv, y_mv);
		double max_mv= max(x_mv, y_mv);
		for (int i = 0; i < min_mv * microstep / SCREW_PITCH * STEPS_PER_CIRCLE; i++) {
			sync_step();
		}
		for (int i = 0; i < (max_mv - min_mv) * microstep / SCREW_PITCH * STEPS_PER_CIRCLE; i++) {
			if (max_mv == x_mv) step_X();
			else step_Y();
		}
		position = pos;
	}
	/// <summary>
	/// Перемещение НА заданную дистанцию
	/// </summary>
	/// <param name="dist">дистанция для перемещения</param>
	void move(Vecter dist) {
		move_to(dist + position);
	}
};
