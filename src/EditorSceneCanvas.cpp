#include "EditorSceneCanvas.hpp"
#include "Transform.hpp"
#include "TestObject.h"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
	obj.GetTransform().SetPosition(500, 500);
	obj.GetTransform().Scalling(10, 10);
}

void NotesEditor::EditorSceneCanvas::Init()
{
	int image = LoadGraph("ShortNotes03.png");
}

void NotesEditor::EditorSceneCanvas::Update()
{
	if(Game::Input::InputDeviceContainer::Instance().GetKeyboard().IsPressKey(KEY_INPUT_W))
		DrawFormatString(0, 200, GetColor(0, 255, 0), "PressW");
}

void NotesEditor::EditorSceneCanvas::Draw()
{
	Game::Component::Transform& transform = obj.GetTransform();
	obj.Draw();
	
	DrawFormatString(0,100,GetColor(0,255,0),"X:%d",transform.GetPosition().GetPosX());
}