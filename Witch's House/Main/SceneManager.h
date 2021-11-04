#pragma once
#include "Config.h"
#include "Singleton.h"
#include <unordered_map>

class GameEntity;
class SceneManager : public Singleton<SceneManager>
{
private:
	std::unordered_map<string, GameEntity*>	mapScenes;
	std::unordered_map<string, GameEntity*>	mapLoadingScenes;

public:
	virtual ~SceneManager() = default;

	static GameEntity* currScene;		// 현재 출력 중인 씬
	static GameEntity* readyScene;		// 준비 중인 씬
	static GameEntity* loadingScene;	// 로딩 씬

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddScene(string key, GameEntity* scene);
	void AddLoadingScene(string key, GameEntity* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);
};

