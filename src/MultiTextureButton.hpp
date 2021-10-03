#pragma once
#include "Button.hpp"
#include <vector>

namespace Engine
{
	namespace Input
	{
		class InputDeviceContainer;
	}

	namespace Components
	{
		class Texture;
		enum class COLLIDERTYPE;
		class ICollider;
	}

	namespace Collision
	{
		class PointWithPolygon;
	}

	namespace UI
	{
		class TextureButton;
		class MultiTextureButton : public Button {
		private:
			// �{�^���N���b�N���ɌĂяo�����֐�
			DelegateBase<void(void)>* eventFunc;
			std::vector<Components::Texture*> texture;

			std::vector<TextureButton*> textureButtonList;
			Components::ICollider* collider;
			// �}�E�X�|�C���^�ƃ|���S���Ƃ̔���
			Collision::PointWithPolygon* collision;
			// ���ݕ\�����̃{�^��
			TextureButton* nowButton;
			int clickCount;

			void RunEventFunc();
		public:
			MultiTextureButton();
			MultiTextureButton(std::vector<const char*> filePath,Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void AddTextureButton(TextureButton* button);
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update();
			void Draw();
		};
	}
}