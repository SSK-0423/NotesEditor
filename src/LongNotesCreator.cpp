#include "LongNotesCreator.hpp"
#include "NotesData.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"

bool NotesEditor::LongNotesCreator::isStart = true;
NotesEditor::LongNotes* NotesEditor::LongNotesCreator::longNotes = nullptr;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::startNotes = nullptr;

NotesEditor::LongNotesCreator::LongNotesCreator()
{
}

NotesEditor::LongNotesCreator::~LongNotesCreator()
{
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData)
{
	// �I�_�m�[�c
	if (isStart)
	{
		startNotes = new ShortNotes(notesData);

		longNotes = new LongNotes(*startNotes);

		isStart = false;
		return longNotes;
	}
	//�I�_�m�[�c
	//�I�_�m�[�c�̈ʒu���n�_�m�[�c�����(��)�������烍���O�m�[�c�ݒu
	if (notesData.y < startNotes->GetTransform().GetPosition().y) {
		//�I�_�m�[�c����
		ShortNotes* endNotes = new ShortNotes(notesData);
		//�I�_�m�[�c�ǉ�
		longNotes->AddEndNotes(*endNotes);
		//�n�_�m�[�c�t���O
		isStart = true;
		//�n�_�m�[�c�𖳌��ɂ���
		startNotes = nullptr;
		//�����O�m�[�c������
		longNotes = nullptr;
	}

	return nullptr;
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::Cancel()
{
	Notes* cancelNotes = longNotes;
	Init();
	return cancelNotes;
}

void NotesEditor::LongNotesCreator::Init()
{
	isStart = true;
	longNotes = nullptr;
	startNotes = nullptr;
}
