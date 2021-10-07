#include "LaneManager.hpp"
#include "Lane.hpp"

NotesEditor::LaneManager::LaneManager()
{
	lanePosX[0] = 307;
	lanePosX[1] = 390;
	lanePosX[2] = 472;
	lanePosX[3] = 555;
	lanePosX[4] = 637;
	lanePosX[5] = 720;

	for (int i = 0; i < Lane::MAXLANENUM; i++)
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

void NotesEditor::LaneManager::Collision(float x, float y)
{
	for (auto lane : laneList)
	{
		lane->Collision(x, y);
	}
}
