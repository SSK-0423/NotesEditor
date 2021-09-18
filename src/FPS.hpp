#pragma once
#include <math.h>
#include "DxLib.h"

namespace Game {

	class Fps {
		//����J�n����
		int startTime;         
		//�J�E���^
		int count;             
		//fps
		float fps;             
		//���ς����T���v����
		static const int N = 60;
		//�ݒ肵��FPS
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
			//1�t���[���ڂȂ玞�����L��
			if (count == 0) 
			{
				startTime = GetNowCount();
			}
			//60�t���[���ڂȂ畽�ς��v�Z����
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
			//������������
			int tookTime = GetNowCount() - startTime;	
			//�҂ׂ�����
			int waitTime = count * 1000 / FPS - tookTime;	
		
			if (waitTime > 0) 
			{
				//�ҋ@
				Sleep(waitTime);	
			}
		}
	};
}