#pragma once

#include <iostream>
#include <wiringPi.h>

using namespace std;
class image {
};
class port{};
class Mask{
public:
	Mask() {};

	port port;
	image current_image;

	void update();
	void clear_image();
	int test();
	void set_image(image image);
};

