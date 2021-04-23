#include "DxLib.h"
#include "SceneManager.hpp"
#include "Editor.hpp"

SceneManager::SceneManager() :
	mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Editor(this);
}

//初期化
void SceneManager::Initialize() {
	mScene->Initialize();
}

//終了処理
void SceneManager::Finalize() {
	mScene->Finalize();
}

//更新
void SceneManager::Update() {
	if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;
		switch (mNextScene) {       //シーンによって処理を分岐
		case eScene_Menu:        //次の画面がメニューなら
			mScene = (BaseScene*) new Editor(this);   //メニュー画面のインスタンスを生成する
			break;//以下略
		}
		mNextScene = eScene_None;    //次のシーン情報をクリア
		mScene->Initialize();    //シーンを初期化
	}

	mScene->Update(); //シーンの更新
}

//描画
void SceneManager::Draw() {
	mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneManager::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //次のシーンをセットする
}