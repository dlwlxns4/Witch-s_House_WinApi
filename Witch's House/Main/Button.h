
#pragma once
#include "Config.h"
#include "GameObject.h"


typedef void (*pVoidFunc)(void);
typedef int (*pIntFunc)(int, int);
//typedef void (ButtonFunction::*FuncPtr)(void);

enum class Button_Type { LayerButton, GotoBattle, GotoResult, Close, etc };
enum class Button_State { None, Down, Up };		// FSM : Finite State Machine 유한 상태 기계
class Button : public GameObject
{
private:
	Button_Type type = {};
	Button_State state = {};

	//void (*funcPtr)(void);

public:
	virtual ~Button() = default;

	virtual HRESULT Init() override;
	virtual HRESULT Init(Button_Type type, int posX, int posY, Image* image);
	virtual void Update() override;
	void AddLayer();
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

