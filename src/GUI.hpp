#pragma once
#include "Game.hpp"

class GUI {
protected:
	// �摜�n���h��
	Image imageHandle;
	// �I�u�W�F�N�g�̍����A��
	Size2D<int> size;
public:
	Position<float> position;
	void SetImageHandle(const char& fileName) noexcept;
	virtual void Draw() {}
	virtual void Update() {}
};