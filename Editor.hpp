#pragma once
#include "BaseScene.hpp"
#include "Button.hpp"
#include "Camera2D.hpp"
#include "TextBox.hpp"
#include "BarManager.hpp"

#define BUTTON_SIZE_WIDTH 126
#define BUTTON_SIZE_HEIGHT 66
#define BUTTON_SIZE2_HEIGHT 66
#define ADD 10
#define BUTTON_POS_Y BUTTON_SIZE_HEIGHT*2 + ADD*4

typedef enum BUTTON {
	BUTTON_SHORT,		// ショートノーツを配置するボタン
	BUTTON_LONG,		// ロングノーツを配置するボタン
	BUTTON_SLIDE,		// スライドノーツを配置するボタン
	BUTTON_PLAY,		// 曲の再生停止ボタン
	BUTTON_RESTART,		// 曲をはじめから再生するボタン
	BUTTON_CHANGEBAR,	// 小節線を1/1に変更するボタン
	BUTTON_CHANGEBAR4,	// 小節線を1/4に変更するボタン
	BUTTON_CHANGEBAR8,	// 小節線を1/8に変更するボタン
	BUTTON_CHANGEBAR16,	// 小節線を1/16に変更するボタン
	BUTTON_CHANGEBAR32,	// 小節線を1/32に変更するボタン
	BUTTON_LOADMUSIC,	// 曲を読み込むボタン
	BUTTON_LOAD,		// 作成した譜面の読み込み
	BUTTON_SAVE,		// 作成した譜面の保存
	BUTTON_NUM			// ボタンの数
};

//エディター画面クラス
class Editor :public BaseScene {
private:
	int fontHandle;			//楽曲情報表示のフォント
	int speed;				//スクロールスピード
	int backgroungHandle;	//背景
	int laneHandle;			//レーン	
	//int lineHandle;			//ノーツライン

	//小節線のハンドル
	int barHandle;		// 1/1
	int bar4Handle;		// 1/4
	int bar8Handle;		// 1/8
	int bar16Handle;	// 1/16
	int bar32Handle;	// 1/32

	int musicInfoHandle;	//楽曲情報表示枠

	int count; // 曲を再生してから経過したフレーム数

	Button* button;
	TextBox text;
	Music music;
	Camera2D camera;
	BarManager barManager;

	// 小節線の描画
	// 楽曲のBPMと再生時間から小節数を算出して描画
	void MakeBar();
	void DrawButton();
	void InitButton();
	void DebugDraw();

public:
	Editor(ISceneChanger* changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};