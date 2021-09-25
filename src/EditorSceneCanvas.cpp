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