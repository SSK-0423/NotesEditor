#include "Notes.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Transform.hpp"
#include "BarLine.hpp"
#include "DxLib.h"
#include <algorithm>

NotesEditor::Notes::Notes() : timing(0.f), lane(0)
{
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();
}

NotesEditor::Notes::~Notes()
{
	delete collider;
	delete collision;
}

float NotesEditor::Notes::GetTiming()
{
	return timing;
}

int NotesEditor::Notes::GetLane()
{
	return lane;
}

void NotesEditor::Notes::ChangedSize(float scaleHeight)
{
	float beforeScale = transform->GetSize().scaleHeight;
	if (scaleHeight == beforeScale) return;
	float ratio = scaleHeight / beforeScale;

	if (beforeScale < scaleHeight)
	{
		// 座標とスケールの更新
		transform->SetPosition(transform->GetPosition().x,
			transform->GetPosition().y - 192.f - 24.f);
		//transform->Translate(0.f, -192.f);
	}
	else
	{
		transform->SetPosition(transform->GetPosition().x,
			transform->GetPosition().y * ratio);
		//transform->Translate(0.f, 192.f);
	}



	transform->Scaling(0.f, scaleHeight);
	collider->Update();
}

bool NotesEditor::Notes::Collision(float x, float y)
{
	return collision->Collision(x, y, *collider);
}