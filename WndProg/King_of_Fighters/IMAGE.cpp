#include "IMAGE.h"
#include <iostream>
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console") 

IMAGE::IMAGE() {};
IMAGE::~IMAGE() {};

void IMAGE::ImageInitialize() {
	img_width = img.GetWidth();
	img_height = img.GetHeight();

	std::cout << "�̹������� ��, ���̰� �ʱ�ȭ��" << std::endl;
}