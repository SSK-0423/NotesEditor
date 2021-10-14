#include "LaneManager.hpp"
#include "NotesManager.hpp"
#include "Lane.hpp"

NotesEditor::LaneManager::LaneManager()
{
	// ショート、ロングノーツのレーン座標
	lanePosX[0] = 307.f;
	lanePosX[1] = 390.f;
	lanePosX[2] = 472.f;
	lanePosX[3] = 555.f;
	lanePosX[4] = 637.f;
	lanePosX[5] = 720.f;

	// スライドノーツのレーン座標
	slideLanePosX[0] = 307.f;
	slideLanePosX[1] = 348.f;
	slideLanePosX[2] = 390.f;
	slideLanePosX[3] = 431.f;
	slideLanePosX[4] = 472.f;
	slideLanePosX[5] = 513.f;
	slideLanePosX[6] = 555.f;
	slideLanePosX[7] = 596.f;
	slideLanePosX[8] = 637.f;
	slideLanePosX[9] = 678.f;
	slideLanePosX[10] = 720.f;

	for (int i = 0; i < SLIDELANENUM; i++)
	{
		laneList.push_back(new Lane(i, slideLanePosX[i]));
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

// 設置するレーンを決めてX座標を返す
float NotesEditor::LaneManager::Collision(float x)
{
	/*
		SHORT,LONGの場合はLANENUM
		SLIDEの場合はSLIDELANENUM
		を使う
	*/

	if (NotesManager::Instance().GetPutNotesType() == NOTESTYPE::SLIDE_NOTES)
	{
		return DecidePosX(x, slideLanePosX, SLIDELANENUM);
	}

	return DecidePosX(x, lanePosX, LANENUM);
}

int NotesEditor::LaneManager::GetLane(float x)
{
	if (NotesManager::Instance().GetPutNotesType() == NOTESTYPE::SLIDE_NOTES)
	{
		return DecideLane(x, slideLanePosX, SLIDELANENUM);
	}

	return DecideLane(x, lanePosX, LANENUM);
}

float NotesEditor::LaneManager::GetLanePosX(int lane)
{
	return lanePosX[lane];
}

float NotesEditor::LaneManager::GetSlideLanePosX(int lane)
{
	return slideLanePosX[lane];
}

float NotesEditor::LaneManager::DecideLane(float x, float laneList[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == laneList[i])
			return i;
	}
	return -1;
}

float NotesEditor::LaneManager::DecidePosX(float x, float laneList[], int size)
{
	int laneIndex = 0;

	// 初期の最小値設定
	float min = abs(laneList[0] - x);

	for (int i = 0; i < size; i++)
	{
		if (min > abs(laneList[i] - x))
		{
			min = abs(laneList[i] - x);
			laneIndex = i;
		}
	}

	return laneList[laneIndex];
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
