#pragma once
#include "OpenFileExplorer.hpp"
#include "AudioSource.hpp"
#include "Singleton.hpp"
#include "picojson.h"

/*
* ノーツエディターで使用する楽曲のクラス
*/

namespace NotesEditor
{
	class NotesEditorMusic : public Singleton<NotesEditorMusic> {
		friend Singleton<NotesEditorMusic>;
	private:
		NotesEditorMusic();
		OpenFileExplorer openFileExplorer;
		Engine::Components::AudioSource audioSource;
		picojson::value json;
		std::string musicName;
		float bpm;
		int beat;
		bool isMusicLoaded;
		bool isLoadFromFumenJson;
		int JsonParse(picojson::value json);
	public:
		~NotesEditorMusic();
		void LoadMusic();
		int LoadMusicFromFumen(picojson::value fumen);
		void PlayStopMusic();
		void ReplayMusic();
		long long GetTotalTime() const;
		long long GetElapsedTime() const;
		std::string GetMusicName() const;
		float GetBPM() const;
		int GetBeat() const;
		bool IsMusicLoaded();
		bool IsLoadFromFumenJson();
		bool IsPlaying();
		void CompleteMusicLoad();
		void SetPlayStartTime(long long time);
	};
}