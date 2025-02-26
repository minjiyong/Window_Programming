#include "MyH.h"
#include <iostream>
#include <random>
#include <Windows.h>

MyH::MyH()
{
}

MyH::~MyH()
{
}

int MyH::Randint(int start, int end)
{
    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(start, end);

    return dis(gen);
}

float MyH::Radian(float degree)
{
    float pi = 3.14159265359;
    return degree * pi / 180;
}