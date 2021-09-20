#pragma once

/*
	�e�N�X�`�������{�^���N���X
*/

namespace Game 
{
	namespace Component 
	{
		class Transform;
		class Texture;
	}

	namespace Object 
	{
		namespace UI 
		{
			class TextureButton {
			private:
				Component::Transform* transform;
				Component::Texture* texture;
			public:
				TextureButton(const char* filePath);
				~TextureButton();
				void Draw();
			};
		}
	}
}