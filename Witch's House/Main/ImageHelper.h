#pragma once
#include <opencv2/highgui.hpp>


using namespace cv;


class OpencvHelper
{
public:
	static Mat ReadImage(const string& path, int flag = 1)
	{
		Mat result = imread(path, flag);

		return result;
	}
};
