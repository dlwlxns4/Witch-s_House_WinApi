// Singleton.h

// 싱글톤 패턴 : 프로그램에서 하나만 존재하는 객체가 필요할 때 사용되는 패턴
// 예시 ) 키 매니저 (관리하는 객체), 씬 매니저, 플레이어 데이터...

#pragma once

//goto

template <typename T>
/*static*/ class Singleton
{
public:
	virtual ~Singleton() = default;

public:
	static T* GetSingleton()
	{
		static T instance;

		return &instance;
	}
protected:
	Singleton() {}		// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
};