#include "SlideNotesCreator.hpp"
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
NotesEditor::SlideNotesCreator::SlideNotesCreator() : isStart(true), isEnd(false)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
#ifdef CREATEMODE
	// �ݒu�J�n
	if (isStart)
	{
		isStart = false;

		//�n�_�m�[�c����
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(GetColor(255, 128, 0));
		//�X���C�h�m�[�c�̃��X�g�ɒǉ�
		slideNotesList.push_back(notes);		
		//�X���C�h�m�[�c����
		slideNotes = new SlideNotes(slideNotesList);
		//�`�惊�X�g�ɒǉ�
		objList.push_back(slideNotes);
		
		return slideNotes;
	}
	// ���ԃm�[�c�ݒu
	else if (!isStart)
	{
		// ���ԃm�[�c����
		ShortNotes* notes = new ShortNotes(notesData);
		notes->SetColor(GetColor(255, 128, 0));
		// �X���C�h�m�[�c�̃��X�g�ɒǉ�
		slideNotesList.push_back(notes);
		// �X���C�h�m�[�c�̃��X�g�X�V
		slideNotes->AddNotes(*notes);
	}
#else
	//�n�_�A���ԓ_�m�[�c
	if (!isEnd)
	{
		//�n�_
		if (slideNotesList.size() == 0)
		{
			//�m�[�c����
			ShortNotes* notes = new ShortNotes(notesData);
			notes->SetColor(GetColor(255, 128, 0));
			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
			slideNotesList.push_back(notes);
			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
			objList.push_back(notes);
		}
		//���ԓ_
		else if (slideNotesList.size() > 0 && notesData.y < slideNotesList[slideNotesList.size() - 1]->GetTransform().GetPosition().y)
		{
			//�m�[�c����
			ShortNotes* notes = new ShortNotes(notesData);
			notes->SetColor(GetColor(255, 128, 0));
			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
			slideNotesList.push_back(notes);
			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
			objList.push_back(notes);
		}
	}

	//�I�_�m�[�c
	if (isEnd)
	{
		//�X���C�h�m�[�c����
		SlideNotes* slideNotes = new SlideNotes(slideNotesList);

		//�ݒu�r���ɒǉ������m�[�c���폜
		for (int i = slideNotesList.size() - 1; i >= 0; i--)
		{
			objList.pop_back();
		}

		//�m�[�c���X�g�ɃX���C�h�m�[�c��ǉ�����
		objList.push_back(slideNotes);

		//�X���C�h�m�[�c�ݒu�p���X�g������
		slideNotesList.clear();
		slideNotesList.shrink_to_fit();

		//4�_�u������I�_�ɂ��Ȃ�
		isEnd = false;

		return slideNotes;
	}

#endif // CREATEMODE
	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
	// �ݒu����
	if (slideNotesList.size() >= 4)
	{
		slideNotes = nullptr;
		slideNotesList.clear();
		slideNotesList.shrink_to_fit();
		isStart = true;
		isEnd = false;
	}
}

void NotesEditor::SlideNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	//for (int i = 0; i < slideNotesList.size(); i++)
	//{
	//	objList.pop_back();
	//}
	isStart = true;
	isEnd = false;
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

void NotesEditor::SlideNotesCreator::DeleteNotes(Engine::GameObject& notes)
{
}

void NotesEditor::SlideNotesCreator::Draw()
{
}
