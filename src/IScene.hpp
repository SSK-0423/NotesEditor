#pragma once

/*
* �V�[���̃C���^�[�t�F�[�X
*/

namespace Engine
{
	namespace Scene
	{
		class IScene {
		public:
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual void Finalize() = 0;
		};
	}

}