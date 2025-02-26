#pragma once
#include <atlImage.h>

class IMAGE {
public:
	CImage img{};
	int img_width{};
	int img_height{};
	int img_left{};
	int img_top{};
	int img_right{};
	int img_bottom{};

	int dir{};

	IMAGE();
	~IMAGE();

	void ImageInitialize();
};