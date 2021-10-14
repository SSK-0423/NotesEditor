#pragma once
#include "OpenFileExplorer.hpp"
#include "AudioSource.hpp"
#include "Singleton.hpp"
#include "picojson.h"

namespace NotesEditor
{
	class NotesEditorMusic : public Singleton<NotesEditorMusic>{
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
		bool isPlaying;

		void JsonParse(picojson::value json);
	public:
		//�ȓǂݍ���
		void LoadMusic();
		//���ʃt�@�C������̋ȓǂݍ���
		void LoadMusicFromFumen(picojson::value fumen);
		//�Ȃ̍Đ��E��~
		void PlayStopMusic();
		//�Ȃ̍Đ�
		void PlayMusic();
		//�Ȃ̒�~
		void StopMusic();
		//�Ȃ��ŏ�����Đ�
		void ReplayMusic();
		//�Ȃ̒������擾
		int GetTotalTime() const;
		//���݂̍Đ��ʒu���擾
		int GetElapsedTime() const;
		//�Ȗ��擾
		std::string GetName() const;
		//BPM�擾
		float GetBPM() const;
		//���q�擾
		int GetBeat() const;
		//�Ȃ��ǂݍ��܂ꂽ���ǂ������擾
		bool IsMusicLoaded();
		//�Ȃ��Đ������ǂ���
		bool IsPlaying();
		//�Ȃ̓ǂݍ��݂������������Ƃ�ʒm
		void CompleteMusicLoad();
		//���Đ����Ԃƌo�ߎ��ԕ\��
		void MusicTimeDraw();
		//�Đ��J�n�ʒu�Z�b�g
		void SetCurrentTime(long long time);
	};
}