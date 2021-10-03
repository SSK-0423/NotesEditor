#include "NotesEditorMusic.hpp"
#include "GameSymbol.hpp"

NotesEditor::NotesEditorMusic::NotesEditorMusic() : musicName("No Data"), audioSource(), bpm(0.f), beat(0), isMusicLoaded(false), isPlaying(false)
{
}

void NotesEditor::NotesEditorMusic::LoadMusic()
{
	//json�t�@�C����ǂݍ���
	if (openFileExplorer.OpenJsonFile(json) != -1) {
		//���ɓǂݍ��񂾋Ȃ��폜
		InitSoundMem();
		//�Ȗ��Ǎ�
		musicName = json.get<picojson::object>()["NAME"].get<std::string>();
		//BPM�ǂݍ���
		bpm = json.get<picojson::object>()["BPM"].get<double>();
		//���q�ǂݍ���
		beat = json.get<picojson::object>()["BEAT"].get<double>();
		//�t�@�C���p�X�Ǎ�
		std::string path = json.get<picojson::object>()["PATH"].get<std::string>();
		//�ȓǂݍ���
		if (audioSource.LoadAudio(path.c_str()) == RESULT::RESULT_SUCCEED) 
		{
			isMusicLoaded = true;
		}
	}
}

void NotesEditor::NotesEditorMusic::PlayStopMusic()
{
	if (isPlaying) 
	{
		if(audioSource.StopAudio() == RESULT::RESULT_SUCCEED);
			isPlaying = false;
		return;
	}
	if(audioSource.PlayAudio() == RESULT::RESULT_SUCCEED)
		isPlaying = true;
}

void NotesEditor::NotesEditorMusic::PlayMusic()
{
	audioSource.PlayAudio();
}

void NotesEditor::NotesEditorMusic::StopMusic()
{
	audioSource.StopAudio();
}

void NotesEditor::NotesEditorMusic::ReplayMusic()
{
	if(audioSource.ReplayAudio() == RESULT::RESULT_SUCCEED)
		isPlaying = true;
}

int NotesEditor::NotesEditorMusic::GetTotalTime()
{
	return audioSource.GetTotalTime();
}

float NotesEditor::NotesEditorMusic::GetElapsedTime()
{
	return audioSource.GetElapsedTime();
}

std::string NotesEditor::NotesEditorMusic::GetName()
{
	return musicName;
}

float NotesEditor::NotesEditorMusic::GetBPM()
{
	return bpm;
}

int NotesEditor::NotesEditorMusic::GetBeat()
{
	return beat;
}

bool NotesEditor::NotesEditorMusic::IsMusicLoaded()
{
	return isMusicLoaded;
}

bool NotesEditor::NotesEditorMusic::IsPlaying()
{
	return isPlaying;
}

void NotesEditor::NotesEditorMusic::CompleteMusicLoad()
{
	isMusicLoaded = false;
}

void NotesEditor::NotesEditorMusic::MusicTimeDraw()
{
}
