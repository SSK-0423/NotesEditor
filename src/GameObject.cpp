#include "GameObject.hpp"
#include "DxLib.h"

GameObject::GameObject() noexcept : imageHandle(-1), width(0),height(0) {
	position.x = 0;
	position.y = 0;
	collisionPos.x = 0;
	collisionPos.y = 0;
}

GameObject::~GameObject() noexcept {
}

void GameObject::Update() noexcept {
}

void GameObject::Draw() noexcept {
}
void GameObject::SetHandle(int handle) noexcept {
	imageHandle = handle;
}

void GameObject::SetPosition(float x, float y) noexcept {
	position.x = x;
	position.y = y;
}

int GameObject::GetObjHeight() noexcept {
	return height;
}

int GameObject::GetObjWidth() noexcept {
	return width;
}