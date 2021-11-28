#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class PlayerObj : public GameObject
{
private:
	//referenceID
	int referenceID=0;

public:
	PlayerObj() = default;
	virtual ~PlayerObj() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();


	void SetImage(Image* image) { this->img = image; }
	void Move();
};

