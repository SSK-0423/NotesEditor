#pragma once
#include "Transform.hpp"

class TestObject {
private:
	Game::Component::Transform transform;
public:
	Game::Component::Transform& GetTransform() {
		return transform;
	}
};