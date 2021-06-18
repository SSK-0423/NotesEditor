#pragma once
#include "GameObject.hpp"
#include "DxLib.h"
#include <vector>

class Canvas : public GameObject{
private:
	std::vector<GameObject> Gui;
	//std::vector<GUI> gui;
public:
	void Update() noexcept;
	void Draw() noexcept;
	void AddUIObj(GameObject* obj) noexcept;
};