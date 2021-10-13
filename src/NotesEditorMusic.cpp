#include "NotesEditorMusic.hpp"
#include "GameSymbol.hpp"

NotesEditor::NotesEditorMusic::NotesEditorMusic() : musicName("No Data"), audioSource(), bpm(0.f), beat(0), isMusicLoaded(false), isPlaying(false)
{
}

void NotesEditor::NotesEditorMusic::LoadMusic()
{
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
		if (audioSource.LoadAudio(path.c_str()) == RESULT::RESULT_SUCCEED) 
		{
			isMusicLoaded = true;
			audioSource.ChangeVolume(128);
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
	if(audioSource.PlayAudioLoop() == RESULT::RESULT_SUCCEED)
		isPlaying = true;
}

void NotesEditor::NotesEditorMusic::PlayMusic()
{
	audioSource.PlayAudioLoop();
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

int NotesEditor::NotesEditorMusic::GetTotalTime() const
{
	return audioSource.GetTotalTime();
}

int NotesEditor::NotesEditorMusic::GetElapsedTime() const
{
	return audioSource.GetElapsedTime();
}

std::string NotesEditor::NotesEditorMusic::GetName() const
{
	return musicName;
}

float NotesEditor::NotesEditorMusic::GetBPM() const
{
	return bpm;
}

int NotesEditor::NotesEditorMusic::GetBeat() const
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

void NotesEditor::NotesEditorMusic::SetCurrentTime(long long time)
{
	audioSource.SetCurrentTime(time);
}
