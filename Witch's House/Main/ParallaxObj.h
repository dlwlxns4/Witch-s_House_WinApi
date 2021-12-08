#include "GameObject.h"
#include "Config.h"

#pragma once
class ParallaxObj : public GameObject
{
	BLENDFUNCTION ftn = {};

	string filePath = "";

	int renderPosX = 0;
	int renderPosY = 0;
	int renderDelayTime = 0;

public:
	ParallaxObj() = default;
	virtual ~ParallaxObj() = default;

	virtual HRESULT Init();
	HRESULT Init(const char* filePath);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void SetImage();

	virtual void Write(ostream& os) const override
	{
		os << 3 << "\t"; // tileType;

		GameObject::Write(os);

		os << ftn.AlphaFormat << endl;
		os << ftn.BlendFlags << endl;
		os << ftn.BlendOp << endl;
		os << ftn.SourceConstantAlpha << endl;
		
		os << filePath << endl;

		os << renderPosX << endl;
		os << renderPosY << endl;
		os << renderDelayTime << endl;
	}

	virtual void Read(istream& is) override
	{
		GameObject::Read(is);

		is >> ftn.AlphaFormat
			>> ftn.BlendFlags
			>> ftn.BlendOp
			>> ftn.SourceConstantAlpha

			>> filePath

			>> renderPosX
			>> renderPosY
			>> renderDelayTime;
	}
};

