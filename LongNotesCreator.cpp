#include "LongNotesCreator.hpp"
#include "LongNotes.hpp"
#include "Mouse.hpp"
#include <math.h>
LongNotesCreator::LongNotesCreator(BarManager& barManager) noexcept {
	this->barManager = &barManager;
}

//�����O�m�[�c�̐���
Notes* LongNotesCreator::CreateNotes(float& x, float& y) noexcept {
	//�n�_�m�[�c����
	ShortNotes* start = new ShortNotes(x, y);
	//�n�_��ǉ����ă����O�m�[�c����
	LongNotes* longNotes = new LongNotes((ShortNotes&)*start);
	//�I�[�m�[�c��ݒu�������ǂ���
	bool isPut = false;
	//�I�[�m�[�c��ݒu����܂Ń��[�v
	while (!isPut) {
		Mouse::Instance()->Update();
		if (Mouse::Instance()->GetPressingCount(Mouse::LEFT_CLICK) == 1) {
			int x, y;
			GetMousePoint(&x, &y);
			if (x >= 1024 / 2 - 1024 / 4 && x <= 1024 / 2 + 1024 / 4) {
				float putPosX, putPosY;
				//�m�[�c�̐ݒu�ʒu������
				barManager->DecidePutPos(putPosX, putPosY);
				if (putPosX != start->position.x) {
					putPosX = start->position.x;
				}
				ShortNotes* end = new ShortNotes(putPosX,putPosY);
				longNotes->AddEndNotes(*end);
				longNotes->SetObjSize(30, (int)fabs(start->position.y - end->position.y));
				isPut = true;
			}
		}
	}
	return longNotes;
}