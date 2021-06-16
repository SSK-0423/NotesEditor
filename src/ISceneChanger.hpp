#pragma once

typedef enum {
	eScene_Menu,
	eScene_Game,
	eScene_Config,

	eScene_None,
} eScene;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};