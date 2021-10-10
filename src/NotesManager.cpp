#include "NotesManager.hpp"
#include "ShortNotes.hpp"
#include "INotesCreator.hpp"
#include "NotesData.hpp"
#include "Transform.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"
#include <algorithm>

#define CREATE 0

//static�ϐ����̉�
NotesEditor::NOTESTYPE NotesEditor::NotesManager::type = NotesEditor::NOTESTYPE::SHORT_NOTES;

bool NotesEditor::NotesManager::IsExist(float x, float y)
{
	for (auto notes : notesList)
	{
		if (notes->Collision(x, y))
			return true;
	}
	return false;
}

NotesEditor::NotesManager::NotesManager() : color(GetColor(0, 255, 0))
{
}

void NotesEditor::NotesManager::ChangeNotesTypeShort()
{
	type = NOTESTYPE::SHORT_NOTES;
	color = GetColor(0, 255, 0);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "ShortNotes");
}

void NotesEditor::NotesManager::ChangeNotesTypeLong()
{
	type = NOTESTYPE::LONG_NOTES;
	color = GetColor(0, 128, 255);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "LongNotes");
}

void NotesEditor::NotesManager::ChangeNotesTypeSlide()
{
	type = NOTESTYPE::SLIDE_NOTES;
	color = GetColor(255, 128, 0);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "SlideNotes");
}

void NotesEditor::NotesManager::Update()
{
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_Q))
		ShortNotes::playRange += 0.001f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_E))
		ShortNotes::playRange -= 0.001f;
}

void NotesEditor::NotesManager::Draw()
{
	DrawFormatString(800, 625, GetColor(0, 255, 0), "playRange:%f", ShortNotes::playRange);
	DrawFormatString(800, 600, GetColor(0, 255, 0), "notesList:%d", notesList.size());
	DrawFormatString(800, 575, GetColor(0, 255, 0), "isStart:%d", LongNotesCreator::isStart);
	DrawFormatString(800, 550, GetColor(0, 255, 0), "startNotes:%p", LongNotesCreator::startNotes);
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
		creator = &shortNotesCreator;
		longNotesCreator.Cancel(objList);		//�����O�m�[�c�̐ݒu���L�����Z��
		slideNotesCreator.Cancel(objList);	//�X���C�h�m�[�c�̐ݒu���L�����Z��
		break;
	case NOTESTYPE::LONG_NOTES:
		creator = &longNotesCreator;
		slideNotesCreator.Cancel(objList);	//�X���C�h�m�[�c�̐ݒu���L�����Z��
		break;
	case NOTESTYPE::SLIDE_NOTES:
		creator = &slideNotesCreator;
		longNotesCreator.Cancel(objList);		//�����O�m�[�c�̐ݒu���L�����Z��
		break;
	default:
		break;
	}

	//�m�[�c����
	Notes* notes = creator->CreateNotes(notesData, objList);

	//�������������Ă�����notesList�ɒǉ�
	if (notes != nullptr)
		notesList.push_back(notes);
}

void NotesEditor::NotesManager::DeleteNotes(float x, float y, std::vector<Engine::GameObject*>& objList)
{
	for (auto notes : notesList)
	{
		bool isCol = notes->Collision(x, y);
		if (isCol)
		{
			DrawFormatString(800, 500, GetColor(0, 255, 0), "��������");
			auto deleteNotes = std::find(notesList.begin(), notesList.end(), notes);
			notesList.erase(deleteNotes);
			auto notesDel = std::find(objList.begin(), objList.end(), static_cast<Engine::GameObject*>(notes));
			objList.erase(notesDel);
		}
	}
}

void NotesEditor::NotesManager::DeleteObj()
{
}

NotesEditor::NOTESTYPE NotesEditor::NotesManager::GetPutNotesType()
{
	return type;
}
