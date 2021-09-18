//#include "LongNotesCreator.hpp"
//#include "DxLib.h"
//
////�N���X�ϐ����̉�
//bool LongNotesCreator::isStart = true;
//
//LongNotesCreator::LongNotesCreator() noexcept {
//	startNotes = nullptr;
//	endNotes = nullptr;
//}
//
//Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {
//
//	//�n�_�m�[�c
//	if (isStart) {
//		//�n�_�m�[�c����
//		startNotes = new ShortNotes(x, y);
//
//		//�I�_�m�[�c�t���O
//		isStart = false;
//
//		return nullptr;
//	}
//	//�I�_�m�[�c
//	else {
//		//�I�_�m�[�c�̈ʒu���n�_�m�[�c���O��������null��Ԃ�
//		if (y > startNotes->collisionPos.y) {
//			return nullptr;
//		}
//		//�I�_�m�[�c����
//		endNotes = new ShortNotes(startNotes->position.x, y);
//
//		//�����O�m�[�c����
//		LongNotes* longNotes = new LongNotes(*startNotes);
//		//�I�_�m�[�c�Z�b�g
//		longNotes->SetEndNotes(*endNotes);
//
//		//�n�_�m�[�c�t���O
//		isStart = true;
//
//		return longNotes;
//	}
//	//Notes* notes = new ShortNotes(x, y);
//	//return notes;
//}
//
//void LongNotesCreator::CreateNotes(float& x, float& y, std::vector<GameObject*>& objList) noexcept {
//	//�n�_�m�[�c
//	if (isStart) {
//		//�n�_�m�[�c����
//		startNotes = new ShortNotes(x, y);
//		startNotes->SetColor(GetColor(0, 128, 255));
//
//		//�I�_�m�[�c�t���O
//		isStart = false;
//
//		objList.push_back(startNotes);
//	}
//	//�I�_�m�[�c
//	else {
//		//�I�_�m�[�c�̈ʒu���n�_�m�[�c�����(��)�������烍���O�m�[�c�ݒu
//		if (y < startNotes->collisionPos.y) {
//			//�I�_�m�[�c����
//			endNotes = new ShortNotes(startNotes->collisionPos.x, y);
//			endNotes->SetColor(GetColor(0, 128, 255));
//			//�����O�m�[�c����
//			LongNotes* longNotes = new LongNotes(*startNotes, *endNotes);
//
//			//�n�_�m�[�c�t���O
//			isStart = true;
//			//�����ɒǉ�����Ă���n�_�m�[�c�����X�g����폜
//			objList.pop_back();
//			//�����O�m�[�c�ǉ�
//			objList.push_back(longNotes);
//		}
//	}
//}
//
//void LongNotesCreator::Cancel(std::vector<GameObject*>& objList) noexcept
//{
//	if (startNotes != nullptr && endNotes == nullptr) {
//		objList.pop_back();
//		isStart = true;
//		delete[] startNotes;
//	}
//}
//
//void LongNotesCreator::DeleteNotes(GameObject& notes) noexcept
//{
//	isStart = true;
//	delete[] startNotes;
//}
