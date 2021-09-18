#include "DxLib.h"
#include "SceneManager.hpp"
#include "EditScene.hpp"

namespace Game {

	namespace System {

		SceneManager::SceneManager() : nextScene(SCENE_NONE) //次のシーン管理変数
		{
			nowScene = (BaseScene*) new NotesEditor::EditScene(this);
		}

		//更新
		void SceneManager::Update() {
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
				//nowScene->Initialize();    //シーンを初期化
			}

			nowScene->Update(); //シーンの更新
		}

		//描画
		void SceneManager::Draw() 
		{
			nowScene->Draw(); //シーンの描画
		}

		void SceneManager::Input(const Input::InputDeviceContainer& inputDeviceContainer)
		{
			nowScene->Input(inputDeviceContainer);
		}

		// 引数 nextScene にシーンを変更する
		void SceneManager::ChangeScene(SCENE nextScene)
		{
			//次のシーンをセットする
			this->nextScene = nextScene;    
		}
	}
}