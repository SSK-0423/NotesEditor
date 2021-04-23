#include "GameObject.hpp"
#include "DxLib.h"

GameObject::GameObject() {
	position.x = 0;
	position.y = 0;
	imageHandle = -1;
	width = 0;
	height = 0;
	collisionPos.x = 0;
	collisionPos.y = 0;
}

GameObject::~GameObject() {
}

void GameObject::Update() {
}

void GameObject::Draw() {
	DrawFormatString(700, 0, GetColor(0, 255, 0), "GameObject");
}