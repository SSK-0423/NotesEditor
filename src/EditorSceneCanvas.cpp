#include "EditorSceneCanvas.hpp"
//#include "Transform.hpp"
//#include "TestObject.h"
//#include "InputDeviceContainer.hpp"
//#include "TextureButton.hpp"
#include "DxLib.h"

NotesEditor::EditorSceneCanvas::EditorSceneCanvas()
{
}

void NotesEditor::EditorSceneCanvas::Init()
{
	//guiList.push_back(new UI::TextureButton("image/PLAY.png",Component::Collider::COLLIDERTYPE::COLLIDERTYPE_BOX));
}

void NotesEditor::EditorSceneCanvas::Update()
{
	obj.Update();
	/*for (auto& gui : guiList)
		gui.Update();
	obj.Update();*/
}

void NotesEditor::EditorSceneCanvas::Draw()
{
	obj.Draw();
	//for (auto& gui : guiList)
	//	gui.Draw();
	//obj.Draw();
}