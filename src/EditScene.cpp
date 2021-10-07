#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer) : BaseScene(changer), camera(allObjList)
{
	editorSceneCanvas.Init();
	laneHandle = LoadGraph("image/Lane.png");
	int barHandle = LoadGraph("image/Bar8.png");
}

void NotesEditor::EditScene::Init()
{
}

void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	camera.Update();

	// 曲の読み込みが完了したら
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		OnMusicLoaded();
		// isMusicLoadedフラグをfalseにする
		NotesEditorMusic::Instance().CompleteMusicLoad();
	}

	Engine::Input::InputDeviceContainer& input = Engine::Input::InputDeviceContainer::Instance();
	if (input.GetKeyboard().IsPressKey(KEY_INPUT_Q))
		BarManager::Instance().ChangeSize();

	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();
	if (mouse.IsPressKey(Engine::Input::Mouse::LEFT_CLICK))
		BarManager::Instance().Collision(mouse.GetPosX(), mouse.GetPosY());
}

void NotesEditor::EditScene::Draw()
{
	//DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.01, 0, laneHandle, true, false);

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	editorSceneCanvas.Draw();
	SetDrawMode(DX_DRAWMODE_NEAREST);
	camera.Draw();
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	editorSceneCanvas.OnMusicLoaded();

	//小節数の計算
	//ループまでの間にも小節線を描画するために+2をする
	int bar_num = NotesEditorMusic::Instance().GetTotalTime() / 1000 * NotesEditorMusic::Instance().GetBPM() / (60 * NotesEditorMusic::Instance().GetBeat()) + 2;
	camera.SetMinposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(bar_num - 1) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	camera.SetMaxposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	
	BarManager::Instance().CreateBar(allObjList,bar_num);
}
