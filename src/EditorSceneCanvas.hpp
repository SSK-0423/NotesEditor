#pragma once
#include "Canvas.hpp"
#include "GUI.hpp"
#include <vector>

namespace NotesEditor
{
	enum BUTTON {
		BUTTON_SHORT,		// �V���[�g�m�[�c��z�u����{�^��
		BUTTON_LONG,		// �����O�m�[�c��z�u����{�^��
		BUTTON_SLIDE,		// �X���C�h�m�[�c��z�u����{�^��
		BUTTON_PLAY,		// �Ȃ̍Đ���~�{�^��
		BUTTON_RESTART,		// �Ȃ��͂��߂���Đ�����{�^��
		BUTTON_CHANGEBAR,	// ���ߐ���1/1�ɕύX����{�^��
		BUTTON_CHANGEBAR4,	// ���ߐ���1/4�ɕύX����{�^��
		BUTTON_CHANGEBAR8,	// ���ߐ���1/8�ɕύX����{�^��
		BUTTON_CHANGEBAR16,	// ���ߐ���1/16�ɕύX����{�^��
		BUTTON_CHANGEBAR32,	// ���ߐ���1/32�ɕύX����{�^��
		BUTTON_LOADMUSIC,	// �Ȃ�ǂݍ��ރ{�^��
		BUTTON_LOAD,		// �쐬�������ʂ̓ǂݍ���
		BUTTON_SAVE,		// �쐬�������ʂ̕ۑ�
		BUTTON_NUM			// �{�^���̐�
	};

	class EditorSceneCanvas : public Engine::UI::Canvas
	{
	private:
		void InitButton();
		void InitTextBox();

	public:
		EditorSceneCanvas();
		~EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
	};
}
