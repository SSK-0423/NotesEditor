#include "MultiTextureButton.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "ICollider.hpp"
#include "InputDeviceContainer.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "ColliderCreator.hpp"

void Engine::UI::MultiTextureButton::RunEventFunc()
{
}

Engine::UI::MultiTextureButton::MultiTextureButton(const char* filePath, Components::COLLIDERTYPE type) : Button()
{
	transform = new Components::Transform();
	texture.push_back(new Components::Texture(*transform, filePath));
	collision = new Collision::PointWithPolygon();

	// Collider����
	collider = Engine::ColliderCreator::Instance().CreateCollider(type, *transform);

	// Transform���e�N�X�`���̃T�C�Y�ɍ��킹��
	float texWidth, texHeight;
	texture[0]->GetTextureSize(texWidth, texHeight);
	transform->SetSize(texWidth, texHeight);
	transform->SetPosition(100.f, 100.f);
}

Engine::UI::MultiTextureButton::~MultiTextureButton()
{
}

void Engine::UI::MultiTextureButton::AddTexture(const char* filePath)
{
	texture.push_back(new Components::Texture(*transform, filePath));
}

void Engine::UI::MultiTextureButton::Update()
{
	// �}�E�X�|�C���^�̍��W�擾
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// �}�E�X�|�C���^���{�^���̏�ɂ��邩
	bool isOnButton =  collision->Collision(x, y, *collider);
	// �{�^���N���b�N���̏���
	if (isOnButton)
	{
		// ���N���b�N�������ꂽ��
		bool isRelease = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
		if (isRelease)
		{
			// �C�x���g���s
			RunEventFunc();
		}

		// ���N���b�N����Ă��邩
		bool isClicking = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
		if (isClicking)
		{
			// �{�^���T�C�Y�ύX
			transform->Scaling(CLICKEDSIZE, CLICKEDSIZE);
			return;
		}
	}

	// �{�^�������̑傫���ɖ߂�
	transform->Scaling(1.0f, 1.0f);
}

void Engine::UI::MultiTextureButton::Draw()
{
}
