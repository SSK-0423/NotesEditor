#include "TextureButtonRect.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "Collider.hpp"
#include "Polygon.hpp"

Game::Object::UI::TextureButtonRect::TextureButtonRect(const char* filePath) : TextureButton(filePath)
{
}

Game::Object::UI::TextureButtonRect::~TextureButtonRect()
{
}

void Game::Object::UI::TextureButtonRect::Draw()
{
}

void Game::Object::UI::TextureButtonRect::Input(const Game::Input::InputDeviceContainer& inputDeviceContainer)
{
	// マウス座標取得
	Component::Position mousePos = inputDeviceContainer.GetMouse().GetPosition();
	// マウス座標を示すPointオブジェクト作成
	Polygon::Point mousePoint(mousePos.GetPosX(), mousePos.GetPosY());
	// 点とポリゴンの当たり判定を担当するクラスのインスタンス
	Component::Collision::PointWithPolygon collision;
	// マウスポインタがボタン上にあるか
	bool isCollision = collision.Collision(mousePoint, *collider);
	// クリックし終わったか判定
	bool isReleaseLeft = inputDeviceContainer.GetMouse().IsPressKey(Input::Mouse::LEFT_CLICK);
	// 
	if (isCollision & isReleaseLeft) 
	{
		/* コールバック関数実行 */
	}
}
