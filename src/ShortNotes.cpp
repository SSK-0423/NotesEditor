//#include "ShortNotes.hpp"
//#include "DxLib.h"
//#include "WindowSize.hpp"
//#include <math.h>
//
////�N���X�ϐ����̉�
////int ShortNotes::clapHandle = LoadSoundMem("sounds/clap.ogg");
//const int ShortNotes::SHORTNOTESWIDTH = 80;
//const int ShortNotes::SHORTNOTESHEIGHT = 20;
//
//ShortNotes::ShortNotes(float& x, float& y) noexcept 
//{
//	clapHandle = LoadSoundMem("sounds/clap.ogg");
//	color = GetColor(0, 255, 0);
//	width = SHORTNOTESWIDTH;
//	height = SHORTNOTESHEIGHT;
//	position.x = x;
//	position.y = y;
//	collisionPos.x = x;
//	collisionPos.y = y;
//}
//
//ShortNotes::~ShortNotes() noexcept 
//{
//
//}
//
//void ShortNotes::Update() noexcept 
//{
//	if (fabs(position.y - WINDOW_SIZE_HEIGHT) <= 5) 
//	{
//		PlayClap();
//	}
//}
//
//void ShortNotes::Draw() noexcept 
//{
//	DrawNotes();
//	DebugDraw();
//}
//
//void ShortNotes::SetColor(Color c)
//{
//	color = c;
//}
//
//Color ShortNotes::GetNotesColor() 
//{
//	return color;
//}
//
////�n���h�N���b�v�Đ�
//void ShortNotes::PlayClap() noexcept 
//{
//	PlaySoundMem(clapHandle, DX_PLAYTYPE_BACK);
//}
//
//// �m�[�c�`��
//void ShortNotes::DrawNotes()
//{
//	DrawBox(position.x - width / 2, position.y - height / 2,
//			position.x + width / 2, position.y + height / 2,
//			color, true);
//}
//
//// �f�o�b�O�p�`��
//void ShortNotes::DebugDraw()
//{
//	// �����蔻��\��
//	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
//	
//	// ���S���W�\��
//	// DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);
//	// DrawFormatString(800, 650, GetColor(0, 255, 0), "X:%f Y:%f", position.x, position.y);
//}