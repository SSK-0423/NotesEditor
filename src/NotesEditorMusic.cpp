#include "NotesEditorMusic.hpp"

NotesEditor::NotesEditorMusic::NotesEditorMusic() : audioSource(), bpm(0.f),beat(0),isMusicLoaded(false),isPlaying(false)
{

}
void NotesEditor::NotesEditorMusic::LoadMusic()
{
	DrawFormatString(0, 300, GetColor(0, 255, 0), "NotesEditorMusic::Music");
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
		//musicHandle = LoadSoundMem(path.c_str());
		if (audioSource.LoadAudio(path.c_str()) == 0) 
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

void NotesEditor::NotesEditorMusic::ReplayMusic()
{
	if(audioSource.ReplayAudio() == RESULT::RESULT_SUCCEED)
		isPlaying = true;
}

int NotesEditor::NotesEditorMusic::GetTotalTime()
{
	return 0;
}

float NotesEditor::NotesEditorMusic::GetElapsedTime()
{
	return 0.0f;
}

std::string NotesEditor::NotesEditorMusic::GetName()
{
	return std::string();
}

float NotesEditor::NotesEditorMusic::GetBPM()
{
	return 0.0f;
}

int NotesEditor::NotesEditorMusic::GetBeat()
{
	return 0;
}

bool NotesEditor::NotesEditorMusic::IsMusicLoad()
{
	return false;
}

bool NotesEditor::NotesEditorMusic::IsPlaying()
{
	return false;
}

void NotesEditor::NotesEditorMusic::ChangeIsMusicLoaded()
{
}

void NotesEditor::NotesEditorMusic::MusicTimeDraw()
{
}
