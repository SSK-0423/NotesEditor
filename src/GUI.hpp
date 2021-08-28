#pragma once
#include "Game.hpp"

class GUI {
protected:
	// 画像ハンドル
	Image imageHandle;
	// オブジェクトの高さ、幅
	Size2D<int> size;
public:
	Position<float> position;
	void SetImageHandle(const char& fileName) noexcept;
	virtual void Draw() {}
	virtual void Update() {}
};