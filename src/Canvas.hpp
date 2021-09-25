#pragma once
#include "DxLib.h"
#include "ICanvas.hpp"
#include <vector>

/*
	�V�[���̑SGUI�̍X�V�E�`��E���͊֘A���������s����N���X
*/

namespace Game
{

	namespace Object
	{

		namespace UI
		{
			class GUI;

			class Canvas : public ICanvas{
			protected:
				std::vector<GUI*> guiList;

			public:
				Canvas() noexcept;
				virtual ~Canvas() noexcept;
				virtual void Init() override;
				virtual void Update() override;
				virtual void Draw() override;
				void AddGUIObj(GUI& obj);
			};
		}
	}
}