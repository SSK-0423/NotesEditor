#pragma once
#include "ISceneChanger.hpp"
#include "BaseScene.hpp"

class SceneManager : public ISceneChanger, Task {
private:
	BaseScene* mScene;	//シーン管理変数
	eScene mNextScene; // 次のシーン管理変数

public:
	SceneManager();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	// ISceneChangerインターフェイス
	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;
};