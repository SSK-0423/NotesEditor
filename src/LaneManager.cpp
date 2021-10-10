#include "LaneManager.hpp"
#include "NotesManager.hpp"
#include "Lane.hpp"

NotesEditor::LaneManager::LaneManager()
{
	lanePosX[0] = 307.f;
	lanePosX[1] = 348.f;
	lanePosX[2] = 390.f;
	lanePosX[3] = 431.f;
	lanePosX[4] = 472.f;
	lanePosX[5] = 513.f;
	lanePosX[6] = 555.f;
	lanePosX[7] = 596.f;
	lanePosX[8] = 637.f;
	lanePosX[9] = 678.f;
	lanePosX[10] = 720.f;

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
	int laneIndex = 0;
	int step = 2;

	// スライドノーツ設置時は設置可能なレーンを増やす
	if (NotesManager::Instance().GetPutNotesType() == NOTESTYPE::SLIDE_NOTES)
	{
		step = 1;
	}

	// 初期の最小値設定
	float min = abs(lanePosX[0] - x);

	for (int i = 0; i < 11; i += step)
	{
		if (min > abs(lanePosX[i] - x))
		{
			min = abs(lanePosX[i] - x);
			laneIndex = i;
		}
	}
	
	return lanePosX[laneIndex];
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
