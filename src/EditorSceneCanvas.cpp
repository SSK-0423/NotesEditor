#include "EditorSceneCanvas.hpp"
#include "InputDeviceContainer.hpp"
#include "Transform.hpp"
#include "ICollider.hpp"
#include "TextureButton.hpp"
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
	buttonList[BUTTON::BUTTON_SHORT] = new TextureButton("image/SHORT.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_LONG] = new TextureButton("image/LONG.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_SLIDE] = new TextureButton("image/SLIDE.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_PLAY] = new TextureButton("image/PLAY.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_RESTART] = new TextureButton("image/RESTART.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_CHANGEBAR] = new TextureButton("image/CHANGE_BAR.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_CHANGEBAR4] = new TextureButton("image/CHANGE_BAR4.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_CHANGEBAR8] = new TextureButton("image/CHANGE_BAR8.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_CHANGEBAR16] = new TextureButton("image/CHANGE_BAR16.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_CHANGEBAR32] = new TextureButton("image/CHANGE_BAR32.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_LOADMUSIC] = new TextureButton("image/LOADMUSIC.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_LOAD] = new TextureButton("image/LOAD.png", COLLIDERTYPE::COLLIDERTYPE_BOX);
	buttonList[BUTTON::BUTTON_SAVE] = new TextureButton("image/SAVE.png", COLLIDERTYPE::COLLIDERTYPE_BOX);

	// クリック時に呼ばれる関数セット
	//buttonList[BUTTON::BUTTON_SHORT]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_LONG]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_SLIDE]->SetEventFunc();
	buttonList[BUTTON::BUTTON_PLAY]->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::PlayStopMusic));
	buttonList[BUTTON::BUTTON_RESTART]->SetEventFunc(Delegate<NotesEditor::NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::ReplayMusic));
	//buttonList[BUTTON::BUTTON_CHANGEBAR]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR4]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR8]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR16]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR32]->SetEventFunc();
	buttonList[BUTTON::BUTTON_LOADMUSIC]->SetEventFunc(Delegate<NotesEditorMusic,
		void(void)>::createDelegator(&NotesEditorMusic::Instance(), &NotesEditorMusic::LoadMusic));
	//buttonList[BUTTON::BUTTON_LOAD]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_SAVE]->SetEventFunc();

	// ボタンのサイズ設定
	buttonList[BUTTON::BUTTON_SHORT]->GetTransform().SetSize(BUTTON_SIZE_WIDTH - ADD / 2, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_LONG]->GetTransform().SetSize(BUTTON_SIZE_WIDTH - ADD / 2, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_SLIDE]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_PLAY]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_RESTART]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_CHANGEBAR]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_CHANGEBAR4]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_CHANGEBAR8]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_CHANGEBAR16]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_CHANGEBAR32]->GetTransform().SetSize(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT - ADD * 1);
	buttonList[BUTTON::BUTTON_LOADMUSIC]->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);
	buttonList[BUTTON::BUTTON_LOAD]->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);
	buttonList[BUTTON::BUTTON_SAVE]->GetTransform().SetSize(BUTTON_SIZE_WIDTH * 2, BUTTON_SIZE_HEIGHT - ADD * 3);

	// ボタンの位置指定
	buttonList[BUTTON::BUTTON_SHORT]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y);
	buttonList[BUTTON::BUTTON_LONG]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y);
	buttonList[BUTTON::BUTTON_SLIDE]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT);
	buttonList[BUTTON::BUTTON_PLAY]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	buttonList[BUTTON::BUTTON_RESTART]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 2);
	buttonList[BUTTON::BUTTON_LOADMUSIC]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 3);
	buttonList[BUTTON::BUTTON_CHANGEBAR]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4);
	buttonList[BUTTON::BUTTON_CHANGEBAR4]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 4);
	buttonList[BUTTON::BUTTON_CHANGEBAR8]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5);
	buttonList[BUTTON::BUTTON_CHANGEBAR16]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + BUTTON_SIZE_WIDTH + ADD, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 5);
	buttonList[BUTTON::BUTTON_CHANGEBAR32]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH / 2 + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 6);
	buttonList[BUTTON::BUTTON_LOAD]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 7);
	buttonList[BUTTON::BUTTON_SAVE]->GetTransform().SetPosition(BUTTON_SIZE_WIDTH + ADD / 2, BUTTON_POS_Y + BUTTON_SIZE_HEIGHT * 8);

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