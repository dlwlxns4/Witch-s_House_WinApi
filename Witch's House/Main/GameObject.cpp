#include "GameObject.h"

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


