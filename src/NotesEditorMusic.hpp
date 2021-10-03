#pragma once
#include "OpenFileExplorer.hpp"
#include "AudioSource.hpp"
#include "Singleton.hpp"

namespace NotesEditor
{
	class NotesEditorMusic : public Singleton<NotesEditorMusic>{
		friend Singleton<NotesEditorMusic>;
	private:
		NotesEditorMusic();
		OpenFileExplorer openFileExplorer;
		Engine::Components::AudioSource audioSource;
		
		//jsonファイル
		picojson::value json;
		//曲名
		std::string musicName;
		//BPM
		float bpm;
		//拍子
		int beat;

		bool isMusicLoaded;
		bool isPlaying;
	public:
		//曲読み込み
		void LoadMusic();
		//曲の再生・停止
		void PlayStopMusic();
		//曲の再生
		void PlayMusic();
		//曲の停止
		void StopMusic();
		//曲を最初から再生
		void ReplayMusic();
		//曲の長さを取得
		int GetTotalTime();
		//現在の再生位置を取得
		float GetElapsedTime();
		//曲名取得
		std::string GetName();
		//BPM取得
		float GetBPM();
		//拍子取得
		int GetBeat();
		//曲が読み込まれたかどうかを取得
		bool IsMusicLoaded();
		//曲が再生中がどうか
		bool IsPlaying();
		//曲の読み込みが完了したことを通知
		void CompleteMusicLoad();
		//総再生時間と経過時間表示
		void MusicTimeDraw();
	};
}