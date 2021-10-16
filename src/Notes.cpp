#include "Notes.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"

NotesEditor::Notes::Notes() : timing(0.f),lane(0)
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

bool NotesEditor::Notes::Collision(float x, float y)
{
	return collision->Collision(x, y, *collider);
}