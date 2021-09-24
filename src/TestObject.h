#pragma once
#include "Transform.hpp"
#include "Texture.hpp"
#include "BoxCollider.hpp"

class TestObject {
private:
	Game::Component::Transform transform;
	Game::Component::Texture texture;
	Game::Component::Collider::BoxCollider collider;

public:
	TestObject() : texture(transform,"image/ShortNotes03.png"), collider(transform)
	{
		float width, height;
		texture.GetTextureSize(width,height);
		transform.SetSize(width,height);
	}
	
	void Draw() 
	{
		texture.Draw();
		collider.Draw();
	}
	Game::Component::Transform& GetTransform() 
	{
		return transform;
	}
};