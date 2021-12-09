#include "GameObject.h"
#include "Component.h"

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
}

HRESULT GameObject::Init()
{
	//for (Component* comp : _components)
	//{
	//	comp->Init();
	//}
	return S_OK;
}

void GameObject::Update()
{
	//for (Component* comp : _components)
	//{
	//	comp->Update();
	//}
}

void GameObject::Render(HDC hdc)
{
}

void GameObject::Release()
{
}
