#include "IMAGE.h"

IMAGE::IMAGE() {};
IMAGE::~IMAGE() {};

void IMAGE::ImageInitialize(){
	 img_width = img.GetWidth();
	 img_height = img.GetHeight();

	 img_right = img_left + img_width;
	 img_bottom = img_top + img_height;
}