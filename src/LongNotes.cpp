//#include "LongNotes.hpp"
//#include "DxLib.h"
//#include <math.h>
//
////クラス変数実体化
//unsigned int LongNotes::color = GetColor(0, 0, 255);
//
//LongNotes::LongNotes(ShortNotes& start) noexcept {
//	startNotes = &start;
//	endNotes = nullptr;
//	width = 0;
//	height = 0;
//}
//
//LongNotes::LongNotes(ShortNotes& start, ShortNotes& end) noexcept {
//	startNotes = &start;
//	endNotes = &end;
//	//positionの設定
//	position.x = startNotes->position.x;
//	collisionPos.x = startNotes->collisionPos.x;
//	position.y = (startNotes->position.y + endNotes->position.y) / 2;
//	collisionPos.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
//	//サイズの設定
//	width = 80;
//	height = fabs(endNotes->collisionPos.y - startNotes->collisionPos.y);
//}
//
//LongNotes::~LongNotes() noexcept {
//	delete[] startNotes;
//	delete[] endNotes;
//}
//
//void LongNotes::SetStartNotes(ShortNotes& start) noexcept {
//	startNotes = &start;
//}
//
//void LongNotes::SetEndNotes(ShortNotes& end) noexcept {
//	endNotes = &end;
//	//positionの設定
//	position.x = startNotes->collisionPos.x;
//	collisionPos.x = startNotes->collisionPos.x;
//	position.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
//	collisionPos.y = (startNotes->collisionPos.y + endNotes->collisionPos.y) / 2;
//	//サイズの設定
//	width = 80;
//	height = fabs(fabs(endNotes->position.y) - fabs(startNotes->position.y));
//}
//
//void LongNotes::SetObjSize(int w, int h) noexcept {
//	width = w;
//	height = h;
//}
//
//void LongNotes::Update() noexcept {
//	startNotes->SetPosition(position.x, position.y + height / 2);
//	endNotes->SetPosition(position.x, position.y - height / 2);
//}
//
//void LongNotes::Draw() noexcept {
//
//	//始点描画
//	startNotes->Draw();
//	//終点描画
//	endNotes->Draw();
//	//始点と終点を線で繋ぐ
//	DrawLine(startNotes->position.x, startNotes->position.y, endNotes->position.x, endNotes->position.y, color, 80);
//
//	//DrawFormatString(800, 675, GetColor(0, 255, 0), "LY:%f", position.y);// + dx_[0] + 5);
//	
//	DrawBox(position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2, GetColor(255, 0, 0), false);
//	DrawCircle(position.x, position.y, 10, GetColor(255, 255, 255), true);
//
//
//	/*DrawBox(position.x - width / 2, position.y - height / 2,
//		position.x + width / 2, position.y + height / 2,
//		color, true);*/
//}
