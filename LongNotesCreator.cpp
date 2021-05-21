#include "LongNotesCreator.hpp"

//�N���X�ϐ����̉�
bool LongNotesCreator::isStart = true;

LongNotesCreator::LongNotesCreator() noexcept {
	startNotes = nullptr;
	endNotes = nullptr;
}

Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {

	//�n�_�m�[�c
	if (isStart) {
		//�n�_�m�[�c����
		startNotes = new ShortNotes(x, y);

		//�I�_�m�[�c�t���O
		isStart = false;
		
		return nullptr;
	}
	//�I�_�m�[�c
	else {
		//�I�_�m�[�c�̈ʒu���n�_�m�[�c���O��������null��Ԃ�
		if (y > startNotes->position.y) {
			return nullptr;
		}
		//�I�_�m�[�c����
		endNotes = new ShortNotes(startNotes->position.x, y);
		
		//�����O�m�[�c����
		LongNotes* longNotes = new LongNotes(*startNotes);
		//�I�_�m�[�c�Z�b�g
		longNotes->SetEndNotes(*endNotes);
		
		//�n�_�m�[�c�t���O
		isStart = true;
		
		return longNotes;
	}
	//Notes* notes = new ShortNotes(x, y);
	//return notes;
}