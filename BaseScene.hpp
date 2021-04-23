#pragma once
#include "Task.hpp"
#include "ISceneChanger.hpp"

//�V�[���̊��N���X
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