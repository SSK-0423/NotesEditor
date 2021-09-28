#pragma once
#include "IScene.hpp"

namespace Scene
{
	class ISceneChanger;

	//�V�[���̊��N���X
	class BaseScene : public IScene {
	protected:
		ISceneChanger* sceneChanger;

	public:
		BaseScene(ISceneChanger* changer);
		virtual ~BaseScene() {}
		virtual void Init() override {};
		virtual void Update() override {};
		virtual void Draw() override {};
	};
}
