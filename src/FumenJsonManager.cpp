#include "FumenJsonManager.hpp"
#include "DxLib.h"

NotesEditor::FumenJsonManager::FumenJsonManager()
{
}

NotesEditor::FumenJsonManager::~FumenJsonManager()
{
}

void NotesEditor::FumenJsonManager::LoadFumen()
{
	DrawFormatString(800, 700, GetColor(0, 255, 0), "���ʓǍ�");
}

void NotesEditor::FumenJsonManager::SaveFumen()
{
	DrawFormatString(800, 700, GetColor(0, 255, 0), "���ʕۑ�");
}
