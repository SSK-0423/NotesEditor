#include "LaneManager.hpp"
#include "Lane.hpp"

NotesEditor::LaneManager::LaneManager()
{
	lanePosX[0] = 307.f;
	lanePosX[1] = 390.f;
	lanePosX[2] = 472.f;
	lanePosX[3] = 555.f;
	lanePosX[4] = 637.f;
	lanePosX[5] = 720.f;

	for (int i = 0; i < MAXLANENUM; i++)
	{
		laneList.push_back(new Lane(i, lanePosX[i]));
	}
}

NotesEditor::LaneManager::~LaneManager()
{
	for (auto lane : laneList)
	{
		delete lane;
	}
	laneList.clear();
	laneList.shrink_to_fit();
}

void NotesEditor::LaneManager::Update()
{
	for (auto lane : laneList)
	{
		lane->Update();
	}
}

void NotesEditor::LaneManager::Draw()
{
	for (auto lane : laneList)
	{
		lane->Draw();
	}
}

float NotesEditor::LaneManager::Collision(float x, float y)
{
	float putPosX;
	for (auto lane : laneList)
	{
		putPosX = lane->Collision(x, y);
		if (putPosX != -1.f) return putPosX;
	}
	return -1.f;
}

int NotesEditor::LaneManager::GetLane(float x)
{
	for (int i = 0; i < MAXLANENUM; i++)
	{
		if (x == lanePosX[i])
			return i;
	}
	return -1;
}

void NotesEditor::LaneManager::Delete()
{
	for (auto lane : laneList)
	{
		delete lane;
	}
	laneList.clear();
	laneList.shrink_to_fit();
}
