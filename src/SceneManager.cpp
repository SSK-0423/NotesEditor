#include "SceneManager.hpp"
#include "EditScene.hpp"

Engine::Scene::SceneManager::SceneManager()
{
	nowScene = (BaseScene*) new NotesEditor::EditScene(this);
}

Engine::Scene::SceneManager::~SceneManager()
{
	delete nowScene;
}

void Engine::Scene::SceneManager::Update()
{
	nowScene->Update();
}

void Engine::Scene::SceneManager::Draw()
{
	nowScene->Draw();
}

void Engine::Scene::SceneManager::ChangeScene(SCENE nextScene)
{
	nowScene->Finalize();
	delete nowScene;

	switch (nextScene)
	{
	case SCENE::SCENE_EDIT:
		nowScene = (BaseScene*) new NotesEditor::EditScene(this);
		break;
	}
	nowScene->Initialize();
}