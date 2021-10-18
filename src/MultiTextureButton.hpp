#pragma once
#include "Button.hpp"
#include <vector>

/*
* �N���b�N�񐔂ɂ���ăe�N�X�`����؂�ւ���{�^���N���X
*/

namespace Engine
{
	namespace Components
	{
		class Texture;
	}

	namespace UI
	{
		class MultiTextureButton : public Button {
		private:
			// �{�^���N���b�N���ɌĂяo�����֐�
			DelegateBase<void(void)>* eventFunc;
			std::vector<Components::Texture*> textures;
			int nowTexIndex;
			int clickCount;
			void UpdateNowTexIndex();
			void RunEventFunc();
			void OnClick() override;
			void Release() override;
			void Clicking() override;
			void NotOnButton() override;
		public:
			MultiTextureButton(std::vector<const char*> filePath, Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update() override;
			void Draw() override;
		};
	}
}