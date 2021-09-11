#include "EditScene.hpp"

EditScene::EditScene(ISceneChanger* changer) : BaseScene(changer),camera(objList)
{
}

void EditScene::Initialize() noexcept
{
	editorCanvas.Initialize();
}

void EditScene::Finalize() noexcept
{
}

void EditScene::Update() noexcept
{
	camera.Update();
	editorCanvas.Update();
	barManager.Update();
	notesManager.Update();
}

void EditScene::Draw() noexcept
{

}
