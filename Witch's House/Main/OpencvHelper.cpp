#include "ImageHelper.h"
#include <string>

class OpencvHelper
{

public:
	Mat Read_Image(String path)
	{
		return imread(path);
	}
};