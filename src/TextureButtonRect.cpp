#include "TextureButtonRect.hpp"
#include "InputDeviceContainer.hpp"
#include "PointInPolygon.hpp"
#include "Point.hpp"
#include "Collider.hpp"

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
	Component::Collision::PointInPolygon collision;
	// 当たり判定
	bool isCollision = collision.Collision(mousePoint, *collider);
	// クリック判定
	bool isLeftClick = inputDeviceContainer.GetMouse().IsPressKey(Input::Mouse::LEFT_CLICK);
	
	if (isCollision & isLeftClick) 
	{
		/* コールバック関数実行 */
	}
}
