#pragma once
#include "Task.hpp"
#include "ISceneChanger.hpp"

//シーンの基底クラス
class BaseScene : public Task {
protected:
	int mImageHandle;
	ISceneChanger* mSceneChanger;
public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene(){}
	virtual void Initialize() override{}
	virtual void Finalize() override;
	virtual void Update() override{}
	virtual void Draw() override;
};