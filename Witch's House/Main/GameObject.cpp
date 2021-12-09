#include "GameObject.h"
#include "Component.h"
#include <algorithm>

ostream& operator<<(ostream& os, const GameObject& obj)
{		
	obj.Write(os);

	return os;
}

istream& operator>>(istream& is, GameObject& obj)
{
	obj.Read(is);

	return is;

	// TODO: 여기에 return 문을 삽입합니다.
}

void GameObject::AddComponent(Component* component)
{
	this->_components.push_back(component);
	sort(_components.begin(), _components.end(),
		[](const Component* lhs, const Component* rhs)
		{
			return lhs->GetOrder() < rhs->GetOrder();
		});
}

HRESULT GameObject::Init()
{
	for (Component* comp : _components)
	{
		comp->Init();
	}
	return S_OK;
}

void GameObject::Update()
{
	for (Component* comp : _components)
	{
		comp->Update();
	}
}



void GameObject::RemoveComponent(Component* component)
{
	remove(_components.begin(), _components.end(), component);
}


void GameObject::Render(HDC hdc)
{
}

void GameObject::Release()
{
}
