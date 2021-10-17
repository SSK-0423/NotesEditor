#include "BarManager.hpp"
#include "Bar.hpp"
#include "Transform.hpp"
#include "DxLib.h"

const int NotesEditor::BarManager::FONTSIZE = 30;
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

void NotesEditor::BarManager::DebugDraw()
{
	DrawFormatString(800, 25, GetColor(0, 255, 0), "barList:%d", barList.size());
}

void NotesEditor::BarManager::CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum)
{
	this->lineNum = lineNum;
	// è¨êﬂÇÃê∂ê¨
	for (int i = 0; i < barNum; i++)
	{
		Bar* bar;
		if (lineNum >= BarManager::MAXNOTENUM)
		{
			bar = new Bar(i, BarManager::MAXNOTENUM);
		}
		else
		{
			bar = new Bar(i, lineNum);
		}
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
