#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include <vector>

class Canvas : public Object{
private:
	std::vector<GUI*> UI;
public:
	Canvas() noexcept;
	~Canvas() noexcept;
	void Update() noexcept;
	void Draw() noexcept;
	void AddUI(GUI& obj) noexcept;
};