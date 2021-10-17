#include "FumenJsonLoader.hpp"
#include "OpenFileExplorer.hpp"
#include "NotesEditorMusic.hpp"
#include "Notes.hpp"
#include "NotesColor.hpp"
#include "ShortNotes.hpp"
#include "LongNotes.hpp"
#include "SlideNotes.hpp"
#include "BarManager.hpp"
#include "LaneManager.hpp"
#include "WindowSize.hpp"
#include "DxLib.h"

NotesEditor::FumenJsonLoader::FumenJsonLoader() : objList(nullptr), notesList(nullptr), notesEditorMusic(nullptr)
{
}

NotesEditor::FumenJsonLoader::~FumenJsonLoader()
{
}

void NotesEditor::FumenJsonLoader::SetObjList(std::vector<Engine::GameObject*>& objList)
{
	this->objList = &objList;
}

void NotesEditor::FumenJsonLoader::SetNotesList(std::vector<Notes*>& notesList)
{
	this->notesList = &notesList;
}

void NotesEditor::FumenJsonLoader::SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic)
{
	this->notesEditorMusic = &notesEditorMusic;
}

void NotesEditor::FumenJsonLoader::LoadFumen()
{
	// JSONファイル
	picojson::value fumen;
	// JSONファイル読み込み
	OpenFileExplorer openFileExplorer;
	if (openFileExplorer.OpenJsonFile(fumen) == -1) return;
	// 既存ノーツ削除
	DeleteExitNotes();
	// 曲読み込み
	notesEditorMusic->LoadMusicFromFumen(fumen);
	// 譜面を生成して追加する
	CreateNotesFromFumen(fumen);

	DrawFormatString(700, 800, GetColor(0, 255, 0), "読み込み完了");
}

void NotesEditor::FumenJsonLoader::DeleteExitNotes()
{
	objList->clear();
	objList->shrink_to_fit();
	for (auto notes : *notesList)
		delete notes;
	notesList->clear();
	notesList->shrink_to_fit();
}

float NotesEditor::FumenJsonLoader::GetPosX(NOTESTYPE parentType, int lane)
{
	if (parentType == NOTESTYPE::SLIDE_NOTES)
		return LaneManager::Instance().GetSlideLanePosX(lane);

	return LaneManager::Instance().GetLanePosX(lane);
}

float NotesEditor::FumenJsonLoader::CalcPosY(float timing)
{
	// 曲の総再生時間
	float totalTime = static_cast<float>(notesEditorMusic->GetTotalTime());
	// 曲の拍子
	float beat = static_cast<float>(notesEditorMusic->GetBeat());
	// 1小節の長さ(ms)
	float barTimeLength = SecToMsec(60.f) / static_cast<float>(notesEditorMusic->GetBPM()) * beat;
	// 最小音符の長さ(ms)
	float minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// 最小単位音符当たりの座標
	float minimunNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
	// 何番目の最小単位音符ラインか * 最小単位音符ライン1つ当たりのY座標
	int myLineNum = std::roundf(SecToMsec(timing) / minimumNoteTimeLength);

	return static_cast<float>(WINDOW_SIZE_HEIGHT) - myLineNum * minimunNotePosY;
}

NotesEditor::NotesData NotesEditor::FumenJsonLoader::MakeNotesData(picojson::value notesVal, NOTESTYPE parentType)
{
	int lane = notesVal.get<picojson::object>()["lane"].get<double>();
	float timing = notesVal.get<picojson::object>()["timing"].get<double>();
	int barNum = notesVal.get<picojson::object>()["barNum"].get<double>();
	int lineNum = notesVal.get<picojson::object>()["lineNum"].get<double>();

	float x = GetPosX(parentType, lane);
	float y = CalcPosY(timing);

	return NotesData(x, y, lane, timing, barNum, lineNum);
}

void NotesEditor::FumenJsonLoader::CreateNotesFromFumen(picojson::value fumen)
{
	picojson::array notesArray = fumen.get<picojson::object>()["notes"].get<picojson::array>();

	for (auto& notesVal : notesArray)
	{
		NOTESTYPE parentType = static_cast<NOTESTYPE>(notesVal.get<picojson::object>()["type"].get<double>());
		Notes* notes = CreateNotes(notesVal, parentType);
		notesList->push_back(notes);
		objList->push_back(notes);
	}
}

NotesEditor::Notes* NotesEditor::FumenJsonLoader::CreateNotes(picojson::value notesVal, NOTESTYPE type)
{
	switch (type)
	{
	case NotesEditor::NOTESTYPE::SHORT_NOTES:
		return CreateShortNotes(notesVal, type);
	case NotesEditor::NOTESTYPE::LONG_NOTES:
		return CreateLongNotes(notesVal, type);
	case NotesEditor::NOTESTYPE::SLIDE_NOTES:
		return CreateSlideNotes(notesVal, type);
	}
}

NotesEditor::ShortNotes* NotesEditor::FumenJsonLoader::CreateShortNotes(picojson::value notesVal, NOTESTYPE type)
{
	NotesData notesData = MakeNotesData(notesVal, type);
	return new ShortNotes(notesData);
}

NotesEditor::LongNotes* NotesEditor::FumenJsonLoader::CreateLongNotes(picojson::value notesVal, NOTESTYPE type)
{
	picojson::array childArray = notesVal.get<picojson::object>()["notes"].get<picojson::array>();
	NotesData startNotesData = MakeNotesData(childArray[0], type);
	NotesData endNotesData = MakeNotesData(childArray[1], type);
	ShortNotes* startNotes = new ShortNotes(startNotesData);
	ShortNotes* endNotes = new ShortNotes(endNotesData);
	LongNotes* longNotes = new LongNotes(*startNotes);
	longNotes->AddEndNotes(*endNotes);
	return longNotes;
}

NotesEditor::SlideNotes* NotesEditor::FumenJsonLoader::CreateSlideNotes(picojson::value notesVal, NOTESTYPE type)
{
	picojson::array childArray = notesVal.get<picojson::object>()["notes"].get<picojson::array>();
	std::vector<ShortNotes*> childList;
	for (auto& childVal : childArray)
	{
		childList.push_back(new ShortNotes(MakeNotesData(childVal, type)));
	}
	SlideNotes* slideNotes = new SlideNotes(childList);
	slideNotes->PutComplete();
	return slideNotes;
}