#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include <vector>

class Canvas{
private:
	std::vector<GUI*> UIObj;
public:
	Canvas() noexcept;
	~Canvas() noexcept;
	virtual void Initialize() = 0;
	void Update() noexcept;
	void Draw() noexcept;
	void AddGUIObj(GUI& obj) noexcept;
};