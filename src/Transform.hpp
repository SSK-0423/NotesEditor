#pragma once
#include "Game.hpp"
#include "DxLib.h"

class Transform : public Component {
private:
	Position<float> position;
	Size2D<int> size;
public:
	Transform() {};
	~Transform() {};
	Position<float> GetPosition() {
		return position;
	}
	Size2D<int> GetSize() {
		return size;
	}
	void SetPosition(const float& x, const float& y) {

	}
};