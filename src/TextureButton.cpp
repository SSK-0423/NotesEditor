#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

Engine::UI::TextureButton::TextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button(), isPressed(false)
{
	transform = new Components::Transform();
	texture = new Components::Texture(*transform, filePath);
	collision = new Collision::PointWithPolygon();

	// Collider����
	collider = Engine::ColliderCreator::Instance().CreateCollider(type, *transform);

	eventFunc = nullptr;

	// Transform���e�N�X�`���̃T�C�Y�ɍ��킹��
	float texWidth, texHeight;
	texture->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
}

Engine::UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
	delete collider;
	delete collision;
}

void Engine::UI::TextureButton::SetEventFunc(DelegateBase<void(void)>* func)
{
	eventFunc = func;
}

void Engine::UI::TextureButton::Update()
{
	// Texture���I�u�W�F�N�g�̈ʒu�E��]�E�T�C�Y�ɍ��킹��
	texture->Update();
	// Collider���I�u�W�F�N�g�̈ʒu�E��]�E�T�C�Y�ɍ��킹��
	collider->Update();

	if (IsClick())
		RunEventFunc();
}

void Engine::UI::TextureButton::Draw()
{
	texture->Draw();
}

bool Engine::UI::TextureButton::IsClick()
{
	if (IsOnButton())
	{
		// �{�^�����N���b�N����Ă����Ԃō��N���b�N�������ꂽ��
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
		if (isRelease && isPressed == true)
		{
			isPressed = false;
			return true;
		}

		// ���N���b�N����Ă��邩
		bool isClicking = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
		if (isClicking)
		{
			isPressed = true;
			transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
			return false;
		}
	}
	transform->Scaling(1.f,1.f);
	return false;
}

// �C�x���g���s
void Engine::UI::TextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

bool Engine::UI::TextureButton::IsOnButton()
{
	// �}�E�X�|�C���^�̍��W�擾
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// �}�E�X�|�C���^���{�^���̏�ɂ��邩
	return collision->Collision(x, y, *collider);
}