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
			//json�t�@�C��
			picojson::value json;
			//���y�t�@�C���̃n���h��
			Audio musicHandle;
			//�Ȗ�
			std::string name;
			//BPM
			float bpm;
			//���q
			int beat;

			//�Ȃ��ǂݍ��܂ꂽ���ǂ���
			bool isMusicLoad;
			//�Ȃ��Đ������ǂ���
			bool isPlay;

			Music();
		public:
			void SetMusic(const int& handle);
			void LoadMusic();
			virtual ~Music();
			//�Ȃ̍Đ��E��~
			void PlayMusic();
			//�Ȃ��ŏ�����Đ�
			void RestartMusic();
			//�Ȃ̒������擾
			int GetTotalTime();
			//���݂̍Đ��ʒu���擾
			float GetElapsedTime();
			//�Ȗ��擾
			std::string GetName();
			//BPM�擾
			float GetBPM();
			//���q�擾
			int GetBeat();
			//�Ȃ��ǂݍ��܂ꂽ���ǂ������擾
			bool IsMusicLoad();
			//�Ȃ��Đ������ǂ���
			bool IsPlay();
			//�t���O�ύX
			void ChangeIsMusicLoad();
			void MusicTimeDraw();
		};
	}
}