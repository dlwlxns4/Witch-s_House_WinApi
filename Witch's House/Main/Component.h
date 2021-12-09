#pragma once

#include <Windows.h>

#include "GameEntity.h"

class GameObject;

class Component : public GameEntity
{
public:
	Component(GameObject* owner, INT32 order);
	virtual ~Component() noexcept;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	//virtual void OnCollision() override;

	GameObject*		GetOwner() noexcept;
	INT32			GetOrder() const noexcept;
protected:
	GameObject*		_owner = nullptr;
private:
	INT32			_order = 100;
};