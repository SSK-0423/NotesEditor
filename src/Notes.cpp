#include "Notes.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"

NotesEditor::Notes::~Notes()
{
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