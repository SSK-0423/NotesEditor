#include "EditorSceneCanvas.hpp"
#include "Transform.hpp"
#include "TestObject.h"

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
}

void NotesEditor::EditorSceneCanvas::Init()
{

}

void NotesEditor::EditorSceneCanvas::Update()
{
}

void NotesEditor::EditorSceneCanvas::Draw()
{
	TestObject obj;
	Game::Component::Transform& transform = obj.GetTransform();
	Game::Component::Position position = transform.GetPosition();
	Game::Component::Position position2(10,10);
	position = position2;
	DrawFormatString(100, 0, GetColor(0, 255, 0), "%f", position.GetPosX());
}

void NotesEditor::EditorSceneCanvas::Input(const Game::Input::InputDeviceContainer& inputDeviceContainer)
{

}
