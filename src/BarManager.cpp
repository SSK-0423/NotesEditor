#include "BarManager.hpp"
#include "Bar.hpp"
#include "Transform.hpp"
#include "DxLib.h"

NotesEditor::BarManager::BarManager()
{
	Bar::MAXNOTENUM = MAXNOTENUM;
	Bar::fontHandle = CreateFontToHandle("Bar", 30, 1);
}

void NotesEditor::BarManager::ChangeSize()
{
	Engine::Components::Size size;
	for (auto bar : barList)
	{
		bar->GetTransform().Scaling(1.f, 1.f);
		Engine::Components::Position pos = bar->GetTransform().GetPosition();
		bar->GetTransform().SetPosition(pos.x, pos.y * 1.f);
	}
}

float NotesEditor::BarManager::Collision(float x, float y)
{
	float putPosY;
	for (auto bar : barList)
	{
		putPosY = bar->Collision(x, y);
		if (putPosY != -1.f) return putPosY;
	}
	return -1.f;
}

float NotesEditor::BarManager::CalcTiming(float y)
{
	float timing = barList[0]->GetTransform().GetSize().height * static_cast<float>(barList.size());
	return 0.0f;
}

unsigned int NotesEditor::BarManager::GetBarNum()
{
	return barList.size();
}

void NotesEditor::BarManager::Delete()
{
	//for (auto bar : barList)
	//{
	//	delete bar;
	//}
	barList.clear();
	barList.shrink_to_fit();
}

void NotesEditor::BarManager::CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum)
{
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
		objList.push_back(static_cast<Engine::GameObject*>(bar));

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
