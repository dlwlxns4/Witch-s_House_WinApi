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
		os << pos.x;
		os << pos.y;
		os << shape.left;
		os << shape.top;
		os << shape.right;
		os << shape.bottom;

		os << moveSpeed;
		os << bodySize;

		os << img;
	}
	
	ostream& operator<<(ostream& os)
	{
		this->Write(os);
		return os;
	}
};


