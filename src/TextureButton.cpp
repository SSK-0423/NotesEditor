#include "TextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

// �C�x���g���s
void Engine::UI::TextureButton::RunEventFunc()
{
	if (eventFunc == nullptr)
		return;
	(*eventFunc)();
}

Engine::UI::TextureButton::TextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button()
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
	transform->SetPosition(100.f, 100.f);
}

Engine::UI::TextureButton::~TextureButton()
{
	delete transform;
	delete texture;
	delete collider;
	delete collision;
}

void Engine::UI::TextureButton::Update()
{
	// Texture���I�u�W�F�N�g�̈ʒu�E��]�E�T�C�Y�ɍ��킹��
	texture->Update();
	// Collider���I�u�W�F�N�g�̈ʒu�E��]�E�T�C�Y�ɍ��킹��
	collider->Update();

	// �}�E�X�|�C���^�̍��W�擾
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();
	
	// �}�E�X�|�C���^���{�^���̏�ɂ��邩
	bool isOnButton = collision->Collision(x, y, *collider);
	// ���N���b�N���ꂽ��
	bool isClick = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);

	// �{�^���N���b�N���̏���
	if (isOnButton && isClick)
	{
		// �{�^���T�C�Y�ύX
		transform->Scaling(CLICKEDSIZE,CLICKEDSIZE);
		// �C�x���g���s
		RunEventFunc();

		return;
	}

	// �{�^�������̑傫���ɖ߂�
	transform->Scaling(1.0f, 1.0f);
}

void Engine::UI::TextureButton::Draw()
{
	texture->Draw();
}