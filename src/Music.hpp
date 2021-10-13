#pragma once
#include <string>
#include "GameSymbol.hpp"
#include "picojson.h"
#include "Singleton.hpp"

namespace Engine
{
	namespace Components
	{
		class Music : public Singleton<Music>{
			friend Singleton<Music>;
		private:
			std::string str;
			//jsonファイル
			picojson::value json;
			//音楽ファイルのハンドル
			Audio musicHandle;
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

			Music();
		public:
			void SetMusic(const int& handle);
			void LoadMusic();
			virtual ~Music();
			//曲の再生・停止
			void PlayMusic();
			//曲を最初から再生
			void RestartMusic();
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
			bool IsPlay();
			//フラグ変更
			void ChangeIsMusicLoad();
			void MusicTimeDraw();
		};
	}
}