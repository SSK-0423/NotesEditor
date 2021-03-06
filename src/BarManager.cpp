#include "BarManager.hpp"
#include "Bar.hpp"
#include "Transform.hpp"
#include "DxLib.h"

const int NotesEditor::BarManager::FONTSIZE = 50;
const int NotesEditor::BarManager::FONTTHICK = 1;

NotesEditor::BarManager::BarManager() : lineNum(0)
{
	Bar::MAXNOTENUM = MAXNOTENUM;
	Bar::fontHandle = CreateFontToHandle("Bar", FONTSIZE, FONTTHICK);
}

float NotesEditor::BarManager::DecidePutPosY(float x, float y)
{
	float putPosY;
	for (auto& bar : barList)
	{
		putPosY = bar->DecidePutPosY(x, y);
		if (putPosY != -1.f) return putPosY;
	}
	return -1.f;
}

float NotesEditor::BarManager::CalcTiming(float y)
{
	float timing = barList[0]->GetTransform().GetSize().height * static_cast<float>(barList.size());
	return timing;
}

unsigned int NotesEditor::BarManager::GetBarNum()
{
	return barList.size();
}

int NotesEditor::BarManager::GetLineNum()
{
	return lineNum;
}

int NotesEditor::BarManager::NotesBarNum(float y)
{
	const int NONE = -1;

	for (size_t i = 0; i < barList.size(); i++)
	{
		if (barList[i]->Collision(barList[i]->GetTransform().GetPosition().x, y))
			return i;
	}
	return NONE;
}

int NotesEditor::BarManager::NotesLineNum(float y)
{
	const int NONE = -1;
	for (auto bar : barList)
	{
		int lineNum = bar->LineNum(y);
		if (lineNum != NONE)
			return lineNum;
	}
	return NONE;
}

void NotesEditor::BarManager::Delete()
{
	for (auto bar : barList)
		delete bar;
	barList.clear();
	barList.shrink_to_fit();
}

NotesEditor::BarManager::~BarManager()
{
	for (auto bar : barList)
		delete bar;
	barList.clear();
	barList.shrink_to_fit();
}

void NotesEditor::BarManager::CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum)
{
	this->lineNum = lineNum;
	// ???߂̐???
	for (int i = 0; i < barNum; i++)
	{
		Bar* bar;
		if (lineNum >= BarManager::MAXNOTENUM)
			bar = new Bar(i, BarManager::MAXNOTENUM);
		else
			bar = new Bar(i, lineNum);
		
		barList.push_back(bar);
		objList.insert(objList.begin(), bar);
		lineNum -= BarManager::MAXNOTENUM;
	}
}

void NotesEditor::BarManager::ChangeBarType()
{
	Bar::ChangeBarType(BARTYPE::BAR1);
}

void NotesEditor::BarManager::ChangeBarType4()
{
	Bar::ChangeBarType(BARTYPE::BAR4);
}

void NotesEditor::BarManager::ChangeBarType8()
{
	Bar::ChangeBarType(BARTYPE::BAR8);
}

void NotesEditor::BarManager::ChangeBarType16()
{
	Bar::ChangeBarType(BARTYPE::BAR16);
}

void NotesEditor::BarManager::ChangeBarType32()
{
	Bar::ChangeBarType(BARTYPE::BAR32);
}

void NotesEditor::BarManager::ChangedBarsTransformByScale(float scaleHeight)
{
	for (auto bar : barList)
		bar->ChangedTransformByScale(scaleHeight);
}
