#pragma once


#include "GameEntity.h"
#include <iostream>

using namespace std;

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos = {};
	RECT shape = {};
	float moveSpeed = 0.0f;
	int bodySize = 0;

	Image* img = nullptr;

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }
	inline RECT GetShape() { return this->shape; }
	inline RECT* GetShapeAddress() { return &this->shape; }


	virtual void Write(ostream& os) const
	{
		os << pos.x << endl;
		os << pos.y << endl;
		os << shape.left << endl;
		os << shape.top << endl;
		os << shape.right << endl;
		os << shape.bottom << endl;

		os << moveSpeed << endl;
		os << bodySize << endl;

	}

	virtual void Read(istream& is)
	{
		is >> pos.x
			>> pos.y
			>> shape.left
			>> shape.top
			>> shape.right
			>> shape.bottom

			>> moveSpeed
			>> bodySize;
	}
};

ostream& operator<<(ostream& os, const GameObject& obj);

istream& operator>>(istream& is,  GameObject& obj);
