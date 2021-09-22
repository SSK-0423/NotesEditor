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
	// �}�E�X���W�擾
	Component::Position mousePos = inputDeviceContainer.GetMouse().GetPosition();
	// �}�E�X���W������Point�I�u�W�F�N�g�쐬
	Polygon::Point mousePoint(mousePos.GetPosX(), mousePos.GetPosY());
	// �_�ƃ|���S���̓����蔻���S������N���X�̃C���X�^���X
	Component::Collision::PointWithPolygon collision;
	// �}�E�X�|�C���^���{�^����ɂ��邩
	bool isCollision = collision.Collision(mousePoint, *collider);
	// �N���b�N���I�����������
	bool isReleaseLeft = inputDeviceContainer.GetMouse().IsPressKey(Input::Mouse::LEFT_CLICK);
	// 
	if (isCollision & isReleaseLeft) 
	{
		/* �R�[���o�b�N�֐����s */
	}
}
