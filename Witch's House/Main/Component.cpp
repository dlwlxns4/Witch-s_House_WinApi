#include "Component.h"
#include "GameObject.h"
//
// 
//HRESULT Component::Init()
//{
//	return E_NOTIMPL;
//}
//
//void Component::Update()
//{
//}
//
//void Component::Render(HDC hdc)
//{
//}
//
//void Component::Release()
//{
//}
//
//

Component::Component(GameObject* owner, INT32 order)
	: _owner{ owner }, _order{ order }
{
	_owner->AddComponent(this);
}

Component::~Component() noexcept
{
	_owner->RemoveComponent(this);
	_owner = nullptr;
}

HRESULT Component::Init()
{
	return S_OK;
}

void Component::Update()
{
}

void Component::Render(HDC hdc)
{
}

void Component::Release()
{
}

GameObject* Component::GetOwner() noexcept
{
	return _owner;
}

INT32 Component::GetOrder() const noexcept
{
	return _order;
}
