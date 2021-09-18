#pragma once
#include "IScene.hpp"
#include "ISceneChanger.hpp"
#include "InputDeviceContainer.hpp"

namespace Game{
	
	//シーンの基底クラス
	class BaseScene : public IScene{
	protected:
		System::ISceneChanger* sceneChanger;

	public:
		BaseScene(System::ISceneChanger* changer);
		virtual ~BaseScene(){}
		virtual void Init() override {};
		virtual void Update() override {};
		virtual void Draw() override{};
		virtual void Input(const Input::InputDeviceContainer& inputDeviceContainer) override {};
	};
}