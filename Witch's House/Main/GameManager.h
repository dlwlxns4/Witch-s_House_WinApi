#pragma once

#include "Singleton.h"

enum class PlayerState{ None, ShowUI, Walk, Run, Chat};

class GameManager : public Singleton<GameManager>
{
private:
	PlayerState playerState = PlayerState::None;


public:
	PlayerState GetPlayerState() { return playerState; }
	void SetPlayerState(PlayerState state) { playerState = state; }
};

