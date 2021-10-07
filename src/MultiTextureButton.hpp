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
			Components::ICollider* collider;
			
			// �}�E�X�|�C���^�ƃ|���S���Ƃ̔���
			Collision::PointWithPolygon* collision;
			int clickCount;

			void RunEventFunc();
		public:
			MultiTextureButton(std::vector<const char*> filePath,Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update();
			void Draw();
		};
	}
}