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

	// TODO: 여기에 return 문을 삽입합니다.
}


