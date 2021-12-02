#pragma once

#include "Singleton.h"
#include "Config.h"

class PhysicsManager : public Singleton<PhysicsManager>
{
private:
	RECT* collider[MAP_SIZE_X][MAP_SIZE_Y] = { nullptr, };

	bool showCollider = false;
public:
	void AddCollider(RECT* rect, int posX, int posY) 
	{
		collider[posY][posX] = rect; 
	}
	RECT* GetRect(int posX, int posY) { return collider[posY][posX]; }
	bool CheckCollider(int posX, int posY)
	{
		if (collider[posY][posX] == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void SetColliderNullptr(int posX, int posY) 
	{
		collider[posY][posX] = nullptr; 
	}
	void Render(HDC hdc);

};

