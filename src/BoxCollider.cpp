#include "BoxCollider.hpp"

Game::Component::Collider::BoxCollider::BoxCollider()
{
}

Game::Component::Collider::BoxCollider::~BoxCollider()
{
}

void Game::Component::Collider::BoxCollider::Draw()
{
}

Game::Component::Collider::COLLIDERTYPE Game::Component::Collider::BoxCollider::GetColliderType()
{
    return COLLIDERTYPE::COLLIDERTYPE_BOX;
}
