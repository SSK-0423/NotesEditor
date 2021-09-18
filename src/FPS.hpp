#pragma once
#include <math.h>
#include "DxLib.h"

namespace Game {

	class Fps {
		//測定開始時刻
		int startTime;         
		//カウンタ
		int count;             
		//fps
		float fps;             
		//平均を取るサンプル数
		static const int N = 60;
		//設定したFPS
		static const int FPS = 60;	

	public:
		Fps() 
		{
			startTime = 0;
			count = 0;
			fps = 0;
		}

		void Update() 
		{
			//1フレーム目なら時刻を記憶
			if (count == 0) 
			{
				startTime = GetNowCount();
			}
			//60フレーム目なら平均を計算する
			if (count == N) 
			{ 
				int t = GetNowCount();
				fps = 1000.f / ((t - startTime) / (float)N);
				count = 0;
				startTime = t;
			}
			count++;
		}

		void Draw() 
		{
			DrawFormatString(0, 0, GetColor(0, 255, 0), "%.1f", fps);
		}

		void Wait() 
		{
			//かかった時間
			int tookTime = GetNowCount() - startTime;	
			//待つべき時間
			int waitTime = count * 1000 / FPS - tookTime;	
		
			if (waitTime > 0) 
			{
				//待機
				Sleep(waitTime);	
			}
		}
	};
}