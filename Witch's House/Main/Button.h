
#pragma once
#include "Config.h"
#include "GameObject.h"

/* 함수 포인터

	포인터 (변수 포인터)

	int a = 10;
	int* pA = &a;

	(*pA) = 20;


	void Func(void);		// 함수의 원형
	void (*pF)(void);	// 리턴타입과 매개변수가 동일한 함수의 주소를 담을 수 있는 함수포인터
*/

//int AddNum(int a, int b)
//{
//	return a + b;
//}
////
//int MinusNum(int a, int b)
//{
//	return a - b;
//}
////
//int (*pF)(int, int);


typedef void (*pVoidFunc)(void);
typedef int (*pIntFunc)(int, int);
//typedef void (ButtonFunction::*FuncPtr)(void);

enum class Button_Type { LayerButton, GotoBattle, GotoResult, Close, etc };
enum class Button_State { None, Down, Up };		// FSM : Finite State Machine 유한 상태 기계
class Button : public GameObject
{
private:
	Button_Type type;
	Button_State state;

	//void (*funcPtr)(void);

public:
	virtual ~Button() = default;

	virtual HRESULT Init() override;
	virtual HRESULT Init(Button_Type type, int posX, int posY, Image* image);
	virtual void Update() override;
	void AddLayer();
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	//void SetNum(int num) { this->num = num; }
	//void SetFunc(void (*funcPtr)(void)) { this->funcPtr = funcPtr; }
	//void SetFunc(pF funcPtr) { this->funcPtr = funcPtr; }
};

