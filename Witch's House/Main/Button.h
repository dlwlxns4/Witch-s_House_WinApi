
#pragma once
#include "Config.h"
#include "GameObject.h"

/* �Լ� ������

	������ (���� ������)

	int a = 10;
	int* pA = &a;

	(*pA) = 20;


	void Func(void);		// �Լ��� ����
	void (*pF)(void);	// ����Ÿ�԰� �Ű������� ������ �Լ��� �ּҸ� ���� �� �ִ� �Լ�������
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
enum class Button_State { None, Down, Up };		// FSM : Finite State Machine ���� ���� ���
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

