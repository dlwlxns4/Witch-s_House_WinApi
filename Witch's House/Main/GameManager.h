#pragma once


enum class PlayerState{ None, Walk, Run, Chat};

class GameManager
{
private:
	PlayerState playerState = PlayerState::None;


public:
	PlayerState GetPlayerState() { return playerState; }

};

