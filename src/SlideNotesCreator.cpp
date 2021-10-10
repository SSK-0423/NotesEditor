#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include "Transform.hpp"
#include "DxLib.h"
//#include <algorithm>
//
//SlideNotesCreator::SlideNotesCreator()  {
//	isEnd = false;
//}
//
//Notes* SlideNotesCreator::CreateNotes(float& x, float& y)  {
//	return nullptr;
//}
//
//void SlideNotesCreator::CreateNotes(std::vector<GameObject*>& objList)  {
//	//�I�_�m�[�c
//	if(isEnd){
//		//�X���C�h�m�[�c����
//		SlideNotes* slideNotes = new SlideNotes(slideNotesList);
//		
//		//�ݒu�r���ɒǉ������m�[�c���폜
//		for (int i = slideNotesList.size() - 1; i >= 0; i--) {
//			objList.pop_back();
//		}
//
//		//�m�[�c���X�g�ɃX���C�h�m�[�c��ǉ�����
//		objList.push_back(slideNotes);
//		//�X���C�h�m�[�c�ݒu�p���X�g������
//		slideNotesList.clear();
//		isEnd = false;
//	}
//}
//
//void SlideNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) 
//{
//	//�n�_�A���ԓ_�m�[�c
//	if (!isEnd) {
//		//�n�_
//		if (slideNotesList.size() == 0) {
//			//�m�[�c����
//			ShortNotes* notes = new ShortNotes(x, y);
//			notes->SetColor(GetColor(255, 128, 0));
//			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
//			slideNotesList.push_back(notes);
//			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
//			objList.push_back(notes);
//		}
//		//���ԓ_
//		else if (slideNotesList.size() > 0 && y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) 
//		{
//			//�m�[�c����
//			ShortNotes* notes = new ShortNotes(x, y);
//			notes->SetColor(GetColor(255, 128, 0));
//			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
//			slideNotesList.push_back(notes);
//			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
//			objList.push_back(notes);
//		}
//	}
//}
//
//// �X���C�h�m�[�c�̏I�[��ݒu���Ă���������
//void SlideNotesCreator::IsEnd()  {
//	if (slideNotesList.size() >= 4) {
//		isEnd = true;
//	}
//}
//
//// �ݒu�L�����Z��
//void SlideNotesCreator::Cancel(std::vector<GameObject*>& objList)  {
//	for (int i = 0; i < slideNotesList.size(); i++) {
//		objList.pop_back();
//	}
//	slideNotesList.clear();
//}
//
////���ԃm�[�c�폜
//void SlideNotesCreator::DeleteNotes(GameObject& notes) 
//{
//	//�X���C�h�m�[�c�̒��ԃm�[�c�Ȃ�폜
//	auto deleteNotes = std::find(slideNotesList.begin(), slideNotesList.end(), (ShortNotes*)&notes);
//	slideNotesList.erase(deleteNotes);
//}
//
//void SlideNotesCreator::Draw()
//{
//	DrawFormatString(800, 600, GetColor(0, 255, 0), "�X���C�h�m�[�c���X�g:%d", slideNotesList.size());
//}

NotesEditor::SlideNotesCreator::SlideNotesCreator() : isEnd(false)
{
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

NotesEditor::Notes* NotesEditor::SlideNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
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
			
			if (slideNotesList.size() >= 4)
				isEnd = true;
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

	return nullptr;
}

void NotesEditor::SlideNotesCreator::IsEnd()
{
}

void NotesEditor::SlideNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	for (int i = 0; i < slideNotesList.size(); i++) 
	{
		objList.pop_back();
	}
	slideNotesList.clear();
	slideNotesList.shrink_to_fit();
}

void NotesEditor::SlideNotesCreator::DeleteNotes(Engine::GameObject& notes)
{
}

void NotesEditor::SlideNotesCreator::Draw()
{
}
