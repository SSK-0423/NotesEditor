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
		//json�t�@�C��
		picojson::value json;
		//�Ȗ�
		std::string musicName;
		//BPM
		float bpm;
		//���q
		int beat;

		bool isMusicLoaded;
		bool isPlaying;
	public:
		void LoadMusic();
		//�Ȃ̍Đ��E��~
		void PlayStopMusic();
		//�Ȃ��ŏ�����Đ�
		void ReplayMusic();
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
		bool IsPlaying();
		//�t���O�ύX
		void ChangeIsMusicLoaded();
		void MusicTimeDraw();
	};
}