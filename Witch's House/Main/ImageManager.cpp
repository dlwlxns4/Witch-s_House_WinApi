#include "ImageManager.h"
#include "Image.h"
#include "ImageHelper.h"
#include <filesystem>

vector<Image*> vecLayerBtnImage;
vector<string> btnName;

void ImageManager::Init()
{
	AddImage("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	//버튼 초기화
	string dir = "Image/Graphics/TilemapTool/";
	int i = 0;
	for (auto& p : filesystem::directory_iterator(dir))
	{
		btnName.push_back(p.path().string().substr());

		cout << p.path().string().substr() << endl;
		Mat img = imread(p.path().string());
		cout << img.rows << " " << img.cols << endl;
		vecLayerBtnImage.push_back(ImageManager::GetSingleton()->AddImage(p.path().string().c_str(), img.cols, img.rows, img.cols / BTN_SIZE_X, img.rows / BTN_SIZE_Y, true, RGB(255, 255, 255)));
	}

}

void ImageManager::Release()
{
	for (auto& elem : mapImages)
	{
		SAFE_RELEASE(elem.second);
	}

	mapImages.clear();
}

//void ImageManager::AddImage()
//{
//	// 추가하려는 이미지를 자료구조에서 찾는다.
//
//	// 있으면 종료.
//
//	// 없으면 추가한다.
//	//new Image();
//	//img->Init
//
//}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (Image* findImage=FindImage(fileName))
	{
		return findImage;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::AddImage(const char* fileName, int width, int height,
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX,
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));
	cout << fileName << "의 이미지가 추가되었습니다." << endl;

	return img;
}

Image* ImageManager::FindImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		cout << fileName << "을 찾지못하였습니다" << endl;
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);	// Image*	// Image 동적할당 해제
	mapImages.erase(it);		// 맵에서 노드 삭제
}
