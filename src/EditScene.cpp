#include "EditScene.hpp"
#include "WindowSize.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"

NotesEditor::EditScene::EditScene(Engine::Scene::ISceneChanger* changer) : BaseScene(changer), camera(allObjList),laneManager(LaneManager::Instance())
{
	editorSceneCanvas.Init();
	laneHandle = LoadGraph("image/���[��02.png");
	int barHandle = LoadGraph("image/Bar8.png");
}

void NotesEditor::EditScene::Init()
{
}

void NotesEditor::EditScene::Update()
{
	editorSceneCanvas.Update();
	laneManager.Update();
	camera.Update();

	// �Ȃ̓ǂݍ��݂�����������
	if (NotesEditorMusic::Instance().IsMusicLoaded())
	{
		OnMusicLoaded();
		// isMusicLoaded�t���O��false�ɂ���
		NotesEditorMusic::Instance().CompleteMusicLoad();
	}
}

void NotesEditor::EditScene::Draw()
{
	DrawRotaGraph(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2, 1.0, 0, laneHandle, true, false);

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	editorSceneCanvas.Draw();
	SetDrawMode(DX_DRAWMODE_NEAREST);
	laneManager.Draw();
	camera.Draw();
	Input();
}

void NotesEditor::EditScene::Input()
{
	const Engine::Input::Mouse mouse = Engine::Input::InputDeviceContainer::Instance().GetMouse();
	if (mouse.IsPressKey(Engine::Input::Mouse::LEFT_CLICK))
	{
		BarManager::Instance().Collision(mouse.GetPosX() + camera.GetOriginPos().x, mouse.GetPosY() + camera.GetOriginPos().y);
		laneManager.Collision(mouse.GetPosX(), mouse.GetPosY());
	}
}

void NotesEditor::EditScene::OnMusicLoaded()
{
	editorSceneCanvas.OnMusicLoaded();

	//���ߐ��̌v�Z
	//���[�v�܂ł̊Ԃɂ����ߐ���`�悷�邽�߂�+2������
	int bar_num = NotesEditorMusic::Instance().GetTotalTime() / 1000 * NotesEditorMusic::Instance().GetBPM() / (60 * NotesEditorMusic::Instance().GetBeat()) + 2;
	camera.SetMinposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f,
		static_cast<float>(-WINDOW_SIZE_HEIGHT) * static_cast<float>(bar_num - 1) + static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	camera.SetMaxposition(static_cast<float>(WINDOW_SIZE_WIDTH) / 2.f, static_cast<float>(WINDOW_SIZE_HEIGHT) / 2.f);
	
	BarManager::Instance().CreateBar(allObjList,bar_num);
}
