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

	// TODO: ���⿡ return ���� �����մϴ�.
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
