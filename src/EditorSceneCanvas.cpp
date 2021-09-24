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

}

void NotesEditor::EditorSceneCanvas::Update()
{

}

void NotesEditor::EditorSceneCanvas::Draw()
{
	Game::Component::Transform& transform = obj.GetTransform();
	//transform.Rotate(1);
	obj.Draw();
	
	DrawFormatString(0,100,GetColor(0,255,0),"X:%d",transform.GetPosition().GetPosX());
}

void NotesEditor::EditorSceneCanvas::Input(const Game::Input::InputDeviceContainer& inputDeviceContainer)
{
	Game::Component::Transform& transform = obj.GetTransform();
	inputDeviceContainer.GetKeyboard().ReadInput();
	if (inputDeviceContainer.GetKeyboard().GetPressingCount(KEY_INPUT_W) > 0)
		transform.Translate(0.f, -1.f);
	if (inputDeviceContainer.GetKeyboard().GetPressingCount(KEY_INPUT_S))
		transform.Translate(0.f, 1.f);
	if (inputDeviceContainer.GetKeyboard().GetPressingCount(KEY_INPUT_D))
		transform.Translate(1.f, 0.f);
	if (inputDeviceContainer.GetKeyboard().GetPressingCount(KEY_INPUT_A))
		transform.Translate(-1.f, 0.f);
	if (inputDeviceContainer.GetKeyboard().IsPressKey(KEY_INPUT_E))
		transform.Rotate(1);
	if (inputDeviceContainer.GetKeyboard().GetPressingCount(KEY_INPUT_Q))
		transform.Rotate(-1);
}
