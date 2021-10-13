#pragma once
#include "DxLib.h"
#include "ICanvas.hpp"
#include <vector>

/*
	�V�[���̑SGUI�̍X�V�E�`��E���͊֘A���������s����N���X
*/

namespace Engine
{
	namespace UI
	{
		class GUI;

		class Canvas : public ICanvas {
		protected:
			std::vector<GUI*> guiList;

		public:
			Canvas();
			virtual ~Canvas();
			virtual void Update() override;
			virtual void Draw() override;
			void AddGUIObj(GUI& obj);
		};
	}
}