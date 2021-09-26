#include "EditorSceneCanvas.hpp"
#include "Transform.hpp"
#include "TestObject.h"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
}

void NotesEditor::EditorSceneCanvas::Init()
{
}

void NotesEditor::EditorSceneCanvas::Update()
{
	obj.Update();
}

void NotesEditor::EditorSceneCanvas::Draw()
{
	obj.Draw();
}