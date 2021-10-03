#include "EditorSceneCanvas.hpp"
#include "InputDeviceContainer.hpp"
#include "Transform.hpp"
#include "ICollider.hpp"
#include "TextureButton.hpp"
#include "MultiTextureButton.hpp"
#include "MusicInfoTextBox.hpp"
#include "TextureTextBox.hpp"
#include "Music.hpp"
#include "NotesEditorMusic.hpp"
#include "DxLib.h"

const int BUTTON_SIZE_WIDTH = 126;
const int BUTTON_SIZE_HEIGHT = 66;
const int BUTTON_SIZE_HEIGHT2 = 66;
const int BOX_SIZE_WIDTH = 252;
const int BOX_SIZE_HEIGHT = 122;
const int ADD = 10;
const int BUTTON_POS_Y = BUTTON_SIZE_HEIGHT * 2 + ADD * 5;

using namespace Engine::UI;
using namespace Engine::Components;

void NotesEditor::EditorSceneCanvas::InitButton()
{
	std::vector<Button*> buttonList(BUTTON::BUTTON_NUM);

	// ボタン生成
	// 設置ノーツ選択ボタン
	TextureButton* shortButton = new TextureButton("image/SHORT.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* longButton = new TextureButton("image/LONG.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* slideButton = new TextureButton("image/SLIDE.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	// 曲の再生・停止ボタン
	TextureButton* playButton = new TextureButton("image/PLAY.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* stopButton = new TextureButton("image/STOP.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* replayButton = new TextureButton("image/REPLAY.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	// 小節線変更ボタン
	TextureButton* changeBarButton = new TextureButton("image/CHANGE_BAR.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* changeBarButton4 = new TextureButton("image/CHANGE_BAR4.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* changeBarButton8 = new TextureButton("image/CHANGE_BAR8.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* changeBarButton16 = new TextureButton("image/CHANGE_BAR16.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* changeBarButton32 = new TextureButton("image/CHANGE_BAR32.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	// ロード・セーブボタン
	TextureButton* loadMusicButton = new TextureButton("image/LOADMUSIC.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* loadButton = new TextureButton("image/LOAD.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	TextureButton* saveButton = new TextureButton("image/SAVE.png", COLLIDERTYPE::COLLIDERTYPE_BOX);

	std::vector<const char*> paths;
	paths.push_back("image/PLAY.png"); paths.push_back("image/STOP.png");
	MultiTextureButton* playStopButton = new MultiTextureButton(paths, COLLIDERTYPE::COLLIDERTYPE_BOX);


	// クリック時に呼ばれる関数セット
	playButton->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::PlayMusic));
	stopButton->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::StopMusic));

	playStopButton->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::PlayStopMusic));
	
	replayButton->SetEventFunc(Delegate<NotesEditor::NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::ReplayMusic));
	loadMusicButton->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::LoadMusic));

	// ボタンのサイズ設定
	shortButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH - ADD / 2, BUTTON_SIZE_HEIGHT - ADD * 1);
	longButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH - ADD / 2, BUTTON_SIZE_HEIGHT - ADD * 1);
	slideButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);

	playButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	stopButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	/// <summary>
	/// 
	/// </summary>
	playStopButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	replayButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	
	changeBarButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	changeBarButton4->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	changeBarButton8->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	changeBarButton16->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	changeBarButton32->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	
	loadMusicButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);
	loadButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);
	saveButton->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);

	// ボタンの位置指定
	shortButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y);
	longButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y);
	slideButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT);
	
	playButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	stopButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	/// <summary>
	/// 
	/// </summary>
	playStopButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	replayButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	
	changeBarButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4);
	changeBarButton4->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4);
	changeBarButton8->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5);
	changeBarButton16->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5);
	changeBarButton32->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 6);
	
	loadMusicButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 3);
	loadButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 7);
	saveButton->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 8);

	// 曲の再生・停止ボタン生成
	//MultiTextureButton* playStopButton = new MultiTextureButton();
	//playStopButton->AddTextureButton(playButton);
	//playStopButton->AddTextureButton(stopButton);

	//
	buttonList[BUTTON::BUTTON_SHORT]		= shortButton;
	buttonList[BUTTON::BUTTON_LONG]			= longButton;
	buttonList[BUTTON::BUTTON_SLIDE]		= slideButton;
	buttonList[BUTTON::BUTTON_REPLAY]		= replayButton;
	buttonList[BUTTON::BUTTON_PLAYSTOP]		= playStopButton;
	buttonList[BUTTON::BUTTON_CHANGEBAR]	= changeBarButton;
	buttonList[BUTTON::BUTTON_CHANGEBAR4]	= changeBarButton4;
	buttonList[BUTTON::BUTTON_CHANGEBAR8]	= changeBarButton8;
	buttonList[BUTTON::BUTTON_CHANGEBAR16]	= changeBarButton16;
	buttonList[BUTTON::BUTTON_CHANGEBAR32]	= changeBarButton32;
	buttonList[BUTTON::BUTTON_LOADMUSIC]	= loadMusicButton;
	buttonList[BUTTON::BUTTON_LOAD]			= loadButton;
	buttonList[BUTTON::BUTTON_SAVE]			= saveButton;

	for (int i = 0; i < BUTTON::BUTTON_NUM; i++)
	{
		guiList.push_back(buttonList[i]);
	}
}

void NotesEditor::EditorSceneCanvas::InitTextBox()
{
	MusicInfoTextBox* musicDataText = new MusicInfoTextBox("image/MUSIC_NAME_BPM.png");
	guiList.push_back(musicDataText);
}

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
}

NotesEditor::EditorSceneCanvas::~EditorSceneCanvas()
{
	for (auto& gui : guiList)
		delete gui;

	guiList.clear();
	guiList.shrink_to_fit();
}

void NotesEditor::EditorSceneCanvas::Init()
{
	InitButton();
	InitTextBox();
}

void NotesEditor::EditorSceneCanvas::Update()
{
	for (auto& gui : guiList)
	{
		gui->Update();
	}
}

void NotesEditor::EditorSceneCanvas::Draw()
{
	for (auto& gui : guiList)
	{
		gui->Draw();
	}
}

/*
GUI表示
Button配列作る→guiListに追加
ボタンの初期化
テキストボックスの初期化
guiListに追加
*/