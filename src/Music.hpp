#pragma once
#include <string>
#include "picojson.h"
class Music {
private:
	std::string str;
	//jsonファイル
	picojson::value json;

	int musicHandle;
	//曲名
	std::string name;
	//BPM
	float bpm;
	//拍子
	int beat;

	//曲が読み込まれたかどうか
	bool isMusicLoad;
	//曲が再生中かどうか
	bool isPlay;

public:
	//コンストラクタ
	Music();
	//曲のセット
	void SetMusic(const int& handle) noexcept;
	//曲の読込
	void LoadMusic() noexcept;
	//デストラクタ
	virtual ~Music() noexcept;
	//曲の再生・停止
	void PlayMusic() noexcept;
	//曲を最初から再生
	void RestartMusic() noexcept;
	//曲の長さを取得
	int GetTotalTime() noexcept;
	//現在の再生位置を取得
	float GetElapsedTime() noexcept;
	//曲名取得
	std::string GetName() noexcept;
	//BPM取得
	float GetBPM() noexcept;
	//拍子取得
	int GetBeat() noexcept;
	//曲が読み込まれたかどうかを取得
	bool IsMusicLoad() noexcept;
	//曲が再生中がどうか
	bool IsPlay() noexcept;
	//フラグ変更
	void ChangeIsMusicLoad() noexcept;
	void MusicTimeDraw() noexcept;
};