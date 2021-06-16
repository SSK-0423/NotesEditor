#include "SlideNotesCreator.hpp"
#include "SlideNotes.hpp"
#include <algorithm>
//void SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
//	Notes* notes = new SlideNotes(x, y);
//}

SlideNotesCreator::SlideNotesCreator() noexcept {
	isEnd = false;
}

Notes* SlideNotesCreator::CreateNotes(float& x, float& y) noexcept {
	//Notes* notes = new SlideNotes(x, y);
	return nullptr;
}

void SlideNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept
{
	//�n�_�A���ԓ_�m�[�c
	if (!isEnd) {
		//�n�_
		if (slideNotesList.size() == 0) {
			//�m�[�c����
			ShortNotes* notes = new ShortNotes(x, y);
			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
			slideNotesList.push_back(notes);
			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
			objList.push_back(notes);
		}
		//���ԓ_
		else if (slideNotesList.size() > 0 && y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) 
		{
			//�m�[�c����
			ShortNotes* notes = new ShortNotes(x, y);
			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
			slideNotesList.push_back(notes);
			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�
			objList.push_back(notes);
		}
	}
	//�I�_�m�[�c
	else {
		//�I�_�m�[�c�̈ʒu���n�_�m�[�c�����(��)��������m�[�c�ݒu
		if (y < slideNotesList[slideNotesList.size() - 1]->collisionPos.y) {
			//�I�_�m�[�c����
			ShortNotes* endNotes = new ShortNotes(x, y);
			//�X���C�h�m�[�c�̃��X�g�ɒǉ�
			slideNotesList.push_back(endNotes);

			//�X���C�h�m�[�c����
			SlideNotes* slideNotes = new SlideNotes(x,y,slideNotesList);

			//�ݒu�r���ɒǉ������m�[�c���폜
			for (int i = slideNotesList.size() - 2; i >= 0; i--) {
				objList.pop_back();
				//auto deleteNotes = std::find(slideNotesList.begin(), slideNotesList.end(), slideNotesList[i]);
				//objList.erase(deleteNotes);
			}

			//�m�[�c���X�g�ɃX���C�h�m�[�c��ǉ�����
			//slideNotesList.push_back((GameObject*)slideNotes);
			//�J�����`��ΏۃI�u�W�F�N�g���X�g�ɒǉ�����
			objList.push_back(slideNotes);
			slideNotesList.clear();
			isEnd = false;
		}
	}
}

// �X���C�h�m�[�c�̏I�[��ݒu���Ă���������
void SlideNotesCreator::IsEnd() noexcept {
	if (slideNotesList.size() >= 4) {
		isEnd = true;
	}
}
