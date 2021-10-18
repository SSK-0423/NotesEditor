#include "Notes.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Transform.hpp"
#include "BarLine.hpp"
#include "DxLib.h"
#include <algorithm>

NotesEditor::Notes::Notes() : timing(0.f), lane(0), barNum(0), lineNum(0)
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

int NotesEditor::Notes::GetBarNum()
{
	return barNum;
}

int NotesEditor::Notes::GetLineNum()
{
	return lineNum;
}

bool NotesEditor::Notes::Collision(float x, float y)
{
	return collision->Collision(x, y, *collider);
}