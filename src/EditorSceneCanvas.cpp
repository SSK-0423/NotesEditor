#include "EditorSceneCanvas.hpp"
#include "InputDeviceContainer.hpp"
#include "Transform.hpp"
#include "ICollider.hpp"
#include "TextureButton.hpp"
#include "TextureTextBox.hpp"
#include "Music.hpp"
#include "DxLib.h"

const int BUTTON_SIZE_WIDTH = 126;
const int BUTTON_SIZE_HEIGHT = 66;
const int BUTTON_SIZE_HEIGHT2 = 66;
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
	buttonList[BUTTON::BUTTON_PLAY]->SetEventFunc(Delegate<Engine::Components::Music, void(void)>::createDelegator(&Engine::Components::Music::Instance(), &Music::PlayMusic));
	buttonList[BUTTON::BUTTON_RESTART]->SetEventFunc(Delegate<Engine::Components::Music, void(void)>::createDelegator(&Engine::Components::Music::Instance(), &Music::RestartMusic));
	//buttonList[BUTTON::BUTTON_CHANGEBAR]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR4]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR8]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR16]->SetEventFunc();
	//buttonList[BUTTON::BUTTON_CHANGEBAR32]->SetEventFunc();
	buttonList[BUTTON::BUTTON_LOADMUSIC]->SetEventFunc(Delegate<Engine::Components::Music, void(void)>::createDelegator(&Engine::Components::Music::Instance() , &Music::LoadMusic));
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
	TextureTextBox* viewMusicInfo = new TextureTextBox("image/MUSIC_NAME_BPM.png");
	guiList.push_back(viewMusicInfo);
	//viewMusicInfo->GetTransform().Scaling(0.65f, 1.f);
	viewMusicInfo->GetTransform().SetPosition(132.f, 70.f);
}

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
	x = 1.f;
	y = 1.f;
}

NotesEditor::EditorSceneCanvas::~EditorSceneCanvas()
{
}

void NotesEditor::EditorSceneCanvas::Init()
{
	InitButton();
	InitTextBox();
}

void NotesEditor::EditorSceneCanvas::Update()
{
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_W))
		guiList[0]->GetTransform().Translate(0.f, -1.f);
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_S))
		guiList[0]->GetTransform().Translate(0.f, 1.f);
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_A))
		guiList[0]->GetTransform().Translate(-1.f, 0.f);
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_D))
		guiList[0]->GetTransform().Translate(1.f, 0.f);
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Q))
		x += 0.01f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_E))
		x -= 0.01f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Z))
		y += 0.01f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_X))
		y -= 0.01f;
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_R))
	{
		x += 0.01f; y += 0.01f;
	}
	if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_F))
	{
		x -= 0.01f; y -= 0.01f;
	}

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