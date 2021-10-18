#include "NotesEditorMusic.hpp"
#include "GameUtility.hpp"

NotesEditor::NotesEditorMusic::NotesEditorMusic() 
	: musicName("No Data"), audioSource(), bpm(0.f), beat(0), isMusicLoaded(false), isLoadFromFumenJson(false)
{
}

int NotesEditor::NotesEditorMusic::JsonParse(picojson::value json)
{
	Audio audio = audioSource.GetAudioHandle();
	std::string path = json.get<picojson::object>()["path"].get<std::string>();
	
	// ã»Ç™ì«Ç›çûÇﬂÇΩÇ»ÇÁ
	if (audioSource.LoadAudio(path.c_str()) == RESULT::RESULT_SUCCEED)
	{
		isMusicLoaded = true;
		audioSource.ChangeVolume(128);
		musicName = json.get<picojson::object>()["name"].get<std::string>();
		bpm = static_cast<float>(json.get<picojson::object>()["bpm"].get<double>());
		beat = static_cast<float>(json.get<picojson::object>()["beat"].get<double>());
		return RESULT::RESULT_SUCCEED;
	}

	isMusicLoaded = false;
	audioSource.SetAudioHandle(audio);
	return RESULT::RESULT_ERROR;
}

NotesEditor::NotesEditorMusic::~NotesEditorMusic()
{
}

void NotesEditor::NotesEditorMusic::LoadMusic()
{
	try
	{
		if (openFileExplorer.OpenJsonFile(json) != -1 && JsonParse(json) == RESULT::RESULT_SUCCEED)
		{
			isLoadFromFumenJson = false;
		}
	}
	catch (const std::exception&)
	{}
}

int NotesEditor::NotesEditorMusic::LoadMusicFromFumen(picojson::value fumen)
{
	try
	{
		if (JsonParse(fumen) == RESULT::RESULT_SUCCEED)
		{
			isLoadFromFumenJson = true;
			return RESULT::RESULT_SUCCEED;
		}
		return RESULT::RESULT_ERROR;
	}
	catch (const std::exception&)
	{
		return RESULT::RESULT_ERROR;
	}
}

void NotesEditor::NotesEditorMusic::PlayStopMusic()
{
	if (audioSource.IsPlaying())
	{
		audioSource.Stop();
		return;
	}
	audioSource.PlayLoop();
}

void NotesEditor::NotesEditorMusic::ReplayMusic()
{
	audioSource.Replay();
}

long long NotesEditor::NotesEditorMusic::GetTotalTime() const
{
	return audioSource.GetTotalTime();
}

long long NotesEditor::NotesEditorMusic::GetElapsedTime() const
{
	return audioSource.GetElapsedTime();
}

std::string NotesEditor::NotesEditorMusic::GetMusicName() const
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

bool NotesEditor::NotesEditorMusic::IsLoadFromFumenJson()
{
	return isLoadFromFumenJson;
}

bool NotesEditor::NotesEditorMusic::IsPlaying()
{
	return audioSource.IsPlaying();
}

void NotesEditor::NotesEditorMusic::CompleteMusicLoad()
{
	isMusicLoaded = false;
}

void NotesEditor::NotesEditorMusic::SetPlayStartTime(long long time)
{
	audioSource.SetPlayStartTime(time);
}