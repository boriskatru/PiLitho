// PiLitho.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include  <wiringPi.h> //подключаем заголовочный файл библиотеки

//#include "setup.h"
#include "controller.h"
#include "encoders.h"
#include "piezoPositioners.h"
#include "mask.h"
#include "motors.h"

using namespace std;

int main()
{
    controller litho;
    std::cout << "Hello World!\n";
}
