#include "NotesManager.hpp"
#include "ShortNotesCreator.hpp"
#include "LongNotesCreator.hpp"
#include "SlideNotesCreator.hpp"
#include "NotesData.hpp"
#include "ShortNotes.hpp"
#include "Transform.hpp"
#include "InputDeviceContainer.hpp"
#include "NotesColor.hpp"
#include "FumenJsonGenerator.hpp"
#include "DxLib.h"
#include <algorithm>

//static�ϐ����̉�
NotesEditor::NOTESTYPE NotesEditor::NotesManager::type = NotesEditor::NOTESTYPE::SHORT_NOTES;

NotesEditor::NotesManager::NotesManager() : mousePointerColor(GetColor(0, 255, 0))
{
}

NotesEditor::NotesManager::~NotesManager()
{
	for (auto notes : notesList)
		delete notes;
	notesList.clear();
	notesList.shrink_to_fit();
}

void NotesEditor::NotesManager::ChangeNotesTypeShort()
{
	type = NOTESTYPE::SHORT_NOTES;
	mousePointerColor = NotesColor::shortNotesColor;
}

void NotesEditor::NotesManager::ChangeNotesTypeLong()
{
	type = NOTESTYPE::LONG_NOTES;
	mousePointerColor = NotesColor::longNotesColor;
}

void NotesEditor::NotesManager::ChangeNotesTypeSlide()
{
	type = NOTESTYPE::SLIDE_NOTES;
	mousePointerColor = NotesColor::slideNotesColor;
}

void NotesEditor::NotesManager::Update()
{
	// ���̃X���C�h�m�[�c�ݒu��
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_RETURN))
		SlideNotesCreator::Instance().IsEnd();
}

void NotesEditor::NotesManager::Draw()
{
	int x, y;
	GetMousePoint(&x, &y);
	DrawBox(x - 10, y - 10, x + 10, y + 10, mousePointerColor, true);
}

void NotesEditor::NotesManager::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	/* �m�[�c���� */
	// �����ꏊ�Ƀm�[�c�����݂���
	if (IsExist(notesData.x, notesData.y))
		return;

	//�m�[�c����
	INotesCreator* creator = nullptr;

	//��������m�[�c
	switch (type)
	{
	case NOTESTYPE::SHORT_NOTES:
		creator = &ShortNotesCreator::Instance();
		break;
	case NOTESTYPE::LONG_NOTES:
		creator = &LongNotesCreator::Instance();
		break;
	case NOTESTYPE::SLIDE_NOTES:
		creator = &SlideNotesCreator::Instance();
		break;
	default:
		break;
	}
	Cancel(type, objList);

	//�m�[�c����
	Notes* notes = creator->CreateNotes(notesData);

	//�m�[�c�ǉ�
	if (notes != nullptr)
	{
		objList.push_back(notes);
		notesList.push_back(notes);
	}
}

void NotesEditor::NotesManager::DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList)
{
	for (auto notes : notesList)
	{
		bool isCol = notes->Collision(x, y);
		if (isCol)
		{
			/*
				�ݒu�r���Ńm�[�c���폜���A�m�[�c��ނ�؂�ւ��Đݒu�����ۂɁA
				�L�����Z���ł��m�[�c�̏����������s���A
				���łɂȂ��m�[�c���������悤�Ƃ���̂ŃG���[����������
			*/
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);
			auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
			objList.erase(notesDel);

			// �폜�����m�[�c���X���C�h�m�[�c�Ȃ�A�m�[�c�ݒu�m�菈�����s��
			// ��slideNotesCreator�̏������������s��
			NOTESTYPE notesType = notes->GetNotesType();
			if (notesType == NOTESTYPE::LONG_NOTES)
				LongNotesCreator::Instance().Init();
			else if (notesType == NOTESTYPE::SLIDE_NOTES)
				SlideNotesCreator::Instance().Init();
		}
	}
}

void NotesEditor::NotesManager::Delete()
{
	for (auto notes : notesList)
		delete notes;
	notesList.clear();
	notesList.shrink_to_fit();
}

void NotesEditor::NotesManager::ChangedScale(float scale)
{
	static float beforeScale = 1.f;
	if (beforeScale == scale) return;

	for (auto notes : notesList)
		notes->ChangedScale(scale, beforeScale < scale ? true : false);

	beforeScale = scale;
}

NotesEditor::NOTESTYPE NotesEditor::NotesManager::GetPutNotesType()
{
	return type;
}

std::vector<NotesEditor::Notes*>& NotesEditor::NotesManager::GetNotesListRef()
{
	return notesList;
}

bool NotesEditor::NotesManager::IsExist(float x, float y)
{
	for (auto notes : notesList)
	{
		if (notes->Collision(x, y))
			return true;
	}
	return false;
}

void NotesEditor::NotesManager::Cancel(NOTESTYPE type, std::vector<Engine::GameObject*>& objList)
{
	Notes* notes = nullptr;
	//��������m�[�c
	switch (type)
	{
	case NOTESTYPE::SHORT_NOTES:
		notes = LongNotesCreator::Instance().Cancel();
		if (notes == nullptr)
			notes = SlideNotesCreator::Instance().Cancel();
		break;
	case NOTESTYPE::LONG_NOTES:
		notes = SlideNotesCreator::Instance().Cancel();
		break;
	case NOTESTYPE::SLIDE_NOTES:
		notes = LongNotesCreator::Instance().Cancel();
		break;
	default:
		break;
	}

	if (notes != nullptr)
	{
		auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
		notesList.erase(deleteNotes);
		auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
		objList.erase(notesDel);
	}
}