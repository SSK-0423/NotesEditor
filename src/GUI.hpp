#pragma once
#include "Game.hpp"
#include "Transform.hpp"

class GUI {
protected:
	Transform transform;

public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
};