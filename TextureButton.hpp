#pragma once
/*
	テクスチャを持つボタンクラス
*/

namespace Game 
{
	namespace Component {
		class Texture;
		class Tranform;
	}
	namespace Object 
	{
		namespace UI 
		{
			class TextureButton {
			private:
				Component::Tranform* transform;
				Component::Texture* texture;
			public:
				TextureButton(const char* filePath) 
				{

				}
				~TextureButton() {
					delete texture;
					delete transform;
				}
				void Draw(){}
			};
		}
	}
}