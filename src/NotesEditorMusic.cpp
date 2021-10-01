#include "NotesEditorMusic.hpp"

NotesEditor::NotesEditorMusic::NotesEditorMusic() : audioSource(), bpm(0.f),beat(0),isMusicLoaded(false),isPlaying(false)
{

}
void NotesEditor::NotesEditorMusic::LoadMusic()
{
	DrawFormatString(0, 300, GetColor(0, 255, 0), "NotesEditorMusic::Music");
	//jsonファイルを読み込む
	if (openFileExplorer.OpenJsonFile(json) != -1) {
		//既に読み込んだ曲を削除
		InitSoundMem();
		//曲名読込
		musicName = json.get<picojson::object>()["NAME"].get<std::string>();
		//BPM読み込み
		bpm = json.get<picojson::object>()["BPM"].get<double>();
		//拍子読み込み
		beat = json.get<picojson::object>()["BEAT"].get<double>();
		//ファイルパス読込
		std::string path = json.get<picojson::object>()["PATH"].get<std::string>();
		//曲読み込み
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
