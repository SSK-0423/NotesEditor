#pragma once
#include "BaseScene.hpp"
#include "Button.hpp"
#include "Camera2D.hpp"
#include "TextBox.hpp"
#include "BarManager.hpp"
#include "NotesManager.hpp"
#include <vector>

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

	int musicInfoHandle;	//楽曲情報表示枠

	int count; // 曲を再生してから経過したフレーム数

	float frame_move; //自動スクロール時の1フレーム当たりのカメラの移動量

	Button* button;
	TextBox text;
	Music music;
	Camera2D camera;
	BarManager barManager;
	NotesManager notesManager;

	//エディター内の全てのオブジェクト
	std::vector<GameObject*> objList;

	// 小節線の描画
	// 楽曲のBPMと再生時間から小節数を算出して描画
	void MakeBar() noexcept;
	//ボタンの更新
	void UpdateButton() noexcept;
	// ボタン描画
	void DrawButton() noexcept;
	// テキストボックス描画
	//void DrawTextBox() noexcept;
	//ボタンの初期化
	void InitButton() noexcept;
	//テキストボックスの初期化
	void InitTextBox() noexcept;
	//ボタンの画像セット
	void SetButtonImage() noexcept;
	//ボタンの位置セット
	void SetButtonPos() noexcept;
	//ボタンのイベント関数セット
	void SetClickEventFunc() noexcept;
	//小節線管理クラスの初期化
	void InitBarManager() noexcept;
	//カメラスクロール
	void ScrollCamera() noexcept;
	//キー入力管理
	void KeyInput() noexcept;
	//デバッグ用テキストなどの描画
	void DebugDraw() noexcept;
	//自動スクロール時の移動幅計算
	void CalcFrameMove() noexcept;
	//ノーツの設置
	void PutNotes() noexcept;
	//オブジェクトの破棄
	void DeleteObj() noexcept;

public:
	Editor(ISceneChanger* changer);
	void Initialize()  noexcept override;
	void Finalize()  noexcept override;
	void Update()  noexcept override;
	void Draw()  noexcept override;
	void AddObject(GameObject& obj) noexcept;
};