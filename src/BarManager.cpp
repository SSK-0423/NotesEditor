#include "BarManager.hpp"
#include "Bar.hpp"
#include "Transform.hpp"
#include "DxLib.h"

NotesEditor::BarManager::BarManager()
{
	Bar::fontHandle = CreateFontToHandle("Bar", 30, 1);
}

void NotesEditor::BarManager::ChangeSize()
{
	Engine::Components::Size size;
	for (auto bar : barList)
	{
		bar->GetTransform().Scaling(1.f,1.f);
		Engine::Components::Position pos = bar->GetTransform().GetPosition();
		bar->GetTransform().SetPosition(pos.x,pos.y * 1.f);
	}
}

void NotesEditor::BarManager::Collision(float x, float y)
{
	for (auto bar : barList)
	{

	}
}

void NotesEditor::BarManager::CreateBar(std::vector<Engine::GameObject*>& objList, int barNum)
{
	for (int i = 0; i < barNum; i++)
	{
		Bar* bar = new Bar(i);
		barList.push_back(bar);
		objList.push_back(static_cast<Engine::GameObject*>(bar));
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
