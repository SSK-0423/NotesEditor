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
		
		std::string str;
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
		void LoadMusic();
		//曲の再生・停止
		void PlayStopMusic();
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
		bool IsMusicLoad();
		//曲が再生中がどうか
		bool IsPlaying();
		//フラグ変更
		void ChangeIsMusicLoaded();
		void MusicTimeDraw();
	};
}