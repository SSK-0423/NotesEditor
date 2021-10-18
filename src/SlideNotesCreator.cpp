#include "SlideNotesCreator.hpp"
#include "NotesData.hpp"
#include "NotesColor.hpp"
#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"
#define CREATEMODE 1;
/*
	�X���C�h�m�[�c�ݒu�d�l
	�E�Œ�4�_�K�v
	�E�G���^�[�L�[�������Ƃ���Ŋm�聨isEnd
	�E1�_�ڂ�u����������A�X���C�h�m�[�c�������ĕԂ����X���C�h�m�[�c����4�_�ȏ゠�邩�ǂ����𔻒肷��
	�E1�_�ډғ����𔻒肷�遨isStart
	�E�ݒu���ɓ_���폜����ɂ͂ǂ����邩���X���C�h�m�[�c����deleteNotes���Ăяo���āA��Ԃ��Čv�Z����
	�E5�_�ڈȍ~�͒u�����тɕ�Ԃ��Čv�Z����A�`�悪�C�������
*/

NotesEditor::SlideNotesCreator::SlideNotesCreator() : isStart(true) ,slideNotes(nullptr)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	// Enter�L�[�Ō��肷��̂�Y�ꂪ���Ȃ̂ŁA�ݒu���̓m�[�c�̐F���s���N�E���ɂ�����
	
	// �ݒu�J�n
	if (isStart)
	{
		isStart = false;

		//�n�_�m�[�c����
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(NotesColor::puttingNotesColor);
		//�X���C�h�m�[�c�̃��X�g�ɒǉ�
		slideNotesList.push_back(notes);
		//�X���C�h�m�[�c����
		slideNotes = new SlideNotes(slideNotesList);

		return slideNotes;
	}
	// ���ԃm�[�c�ݒu
	else if (!isStart && notesData.y < slideNotesList[slideNotesList.size() - 1]->GetTransform().GetPosition().y)
	{
		// ���ԃm�[�c����
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(NotesColor::puttingNotesColor);
		// �X���C�h�m�[�c�̃��X�g�ɒǉ�
		slideNotesList.push_back(notes);
		// �X���C�h�m�[�c�̃��X�g�X�V
		slideNotes->AddNotes(*notes);

	}
	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
	// �ݒu����
	if (slideNotesList.size() >= 4)
	{
		slideNotes->PutComplete();
		Init();
	}
}

void NotesEditor::SlideNotesCreator::Init()
{
	isStart = true;
	slideNotes = nullptr;
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::Cancel()
{
	Notes* cancelNotes = slideNotes;
	Init();
	return cancelNotes;
}