#include "SceneManager.hpp"
#include "EditScene.hpp"

Engine::Scene::SceneManager::SceneManager() : nextScene(SCENE_NONE)
{
	nowScene = (BaseScene*) new NotesEditor::EditScene(this);
}

void Engine::Scene::SceneManager::Update()
{
	//次のシーンがセットされていたら
	if (nextScene != SCENE_NONE) 
	{    
		//現在のシーンの終了処理を実行
		//nowScene->Finalize();
		delete nowScene;

		//シーンによって処理を分岐
		switch (nextScene) 
		{       
			//次の画面がエディット
			case SCENE_EDIT:        
				//エディット画面のインスタンス生成
				nowScene = (BaseScene*) new NotesEditor::EditScene(this); 
				break;
		}
		nextScene = SCENE_NONE;    //次のシーン情報をクリア
		//nowScene->Initialize();  //シーンを初期化
	}

	nowScene->Update(); //シーンの更新
}

void Engine::Scene::SceneManager::Draw()
{
	nowScene->Draw();
}

void Engine::Scene::SceneManager::ChangeScene(SCENE NextScene)
{
	this->nextScene = nextScene;
}
