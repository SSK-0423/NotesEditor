#pragma once
#include "Canvas.hpp"
#include "GUI.hpp"
#include <vector>

namespace Engine
{
	namespace UI
	{
		class Button;
	}
}

namespace NotesEditor
{
	enum BUTTON {
		BUTTON_SHORT,		// ショートノーツを配置するボタン
		BUTTON_LONG,		// ロングノーツを配置するボタン
		BUTTON_SLIDE,		// スライドノーツを配置するボタン
		BUTTON_PLAYSTOP,	// 曲の再生停止ボタン
		BUTTON_REPLAY,		// 曲をはじめから再生するボタン
		BUTTON_CHANGEBAR,	// 小節線を1/1に変更するボタン
		BUTTON_CHANGEBAR4,	// 小節線を1/4に変更するボタン
		BUTTON_CHANGEBAR8,	// 小節線を1/8に変更するボタン
		BUTTON_CHANGEBAR16,	// 小節線を1/16に変更するボタン
		BUTTON_CHANGEBAR32,	// 小節線を1/32に変更するボタン
		BUTTON_LOADMUSIC,	// 曲を読み込むボタン
		BUTTON_LOAD,		// 作成した譜面の読み込み
		BUTTON_SAVE,		// 作成した譜面の保存
		BUTTON_NUM			// ボタンの数
	};

	enum TEXTBOX {
		TEXTBOX_MUSICINFO,	// 楽曲情報を表示するテキストボックス
		TEXTBOX_NUM
	};

	class MusicInfoTextBox;

	class EditorSceneCanvas : public Engine::UI::Canvas
	{
	private:
		std::vector<Engine::UI::Button*> buttonList;
		MusicInfoTextBox* musicInfoText;
		void InitButton();
		void InitTextBox();

	public:
		EditorSceneCanvas();
		~EditorSceneCanvas();
		void Init();
		void Update();
		void Draw();
		void OnMusicLoaded();
	};
}
