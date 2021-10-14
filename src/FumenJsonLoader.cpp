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
	// 1小節の長さ
	float barTimeLength = 60.f * 1000.f / static_cast<float>(notesEditorMusic->GetBPM()) * beat;
	// 最小音符の長さ
	float minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// 最小単位音符当たりの座標
	float minimunNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
	// 32分ライン何番目か * 32分ライン1つ当たりのY座標
	int myLineNum = std::roundf(timing * 1000.f / minimumNoteTimeLength);

	return static_cast<float>(WINDOW_SIZE_HEIGHT) - myLineNum * minimunNotePosY;
}

NotesEditor::NotesData NotesEditor::FumenJsonLoader::MakeNotesData(picojson::value notesVal, NOTESTYPE parentType)
{
	/*
		この関数のタスク
		・NotesDataの作成
		・レーン取得
		・タイミング取得
		・X座標の決定
		・Y座標の計算
	*/
	// レーン
	int lane = notesVal.get<picojson::object>()["lane"].get<double>();
	// タイミング
	float timing = notesVal.get<picojson::object>()["timing"].get<double>();

	float x = GetPosX(parentType, lane);
	float y = CalcPosY(timing);

	return NotesData(x, y, lane, timing);
}

void NotesEditor::FumenJsonLoader::CreateNotes(picojson::value fumen)
{
	picojson::array notesArray = fumen.get<picojson::object>()["notes"].get<picojson::array>();

	for (auto& notesVal : notesArray)
	{
		NOTESTYPE parentType = static_cast<NOTESTYPE>(notesVal.get<picojson::object>()["type"].get<double>());

		if (parentType == NOTESTYPE::SHORT_NOTES)
		{
			NotesData notesData = MakeNotesData(notesVal, parentType);
			ShortNotes* notes = new ShortNotes(notesData);
			notesList->push_back(notes);
			objList->push_back(notes);
		}
		else if (parentType == NOTESTYPE::LONG_NOTES)
		{
			picojson::array childArray = notesVal.get<picojson::object>()["notes"].get<picojson::array>();
			NotesData startNotesData = MakeNotesData(childArray[0], parentType);
			NotesData endNotesData = MakeNotesData(childArray[1], parentType);
			ShortNotes* startNotes = new ShortNotes(startNotesData);
			ShortNotes* endNotes = new ShortNotes(endNotesData);
			LongNotes* longNotes = new LongNotes(*startNotes);
			longNotes->AddEndNotes(*endNotes);
			notesList->push_back(longNotes);
			objList->push_back(longNotes);
		}
		else if (parentType == NOTESTYPE::SLIDE_NOTES)
		{
			picojson::array childArray = notesVal.get<picojson::object>()["notes"].get<picojson::array>();
			std::vector<ShortNotes*> childList;
			for (auto& childVal : childArray)
			{
				childList.push_back(new ShortNotes(MakeNotesData(childVal, parentType)));
			}
			SlideNotes* slideNotes = new SlideNotes(childList);
			slideNotes->PutComplete();
			notesList->push_back(slideNotes);
			objList->push_back(slideNotes);
		}
	}
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
	/*
		譜面のJSONファイルを読み込んでノーツを生成する
		・JSONファイル読み込み
		・曲読み込み
		・ノーツ生成
	*/
	// JSONファイル
	picojson::value fumen;
	// JSONファイル読み込み
	OpenFileExplorer openFileExplorer;
	openFileExplorer.OpenJsonFile(fumen);
	// 曲読み込み
	notesEditorMusic->LoadMusicFromFumen(fumen);
	// ノーツ生成
	CreateNotes(fumen);

	/*
		Json読み込み
		typeでどのノーツを生成するか判断
		type == longの時はnotesを取得して始点と終点に追加
		type == slideの時はnotesを取得して子ノーツを追加

		ノーツ作成
		NotesDataを作成→ノーツ生成
		レーンよりX座標算出→laneManagerのlanePosX,slideLanePosXを使う
		タイミングよりY座標算出→タイミング * 1000.f / 総再生時間 * 小節の末端座標までの変位
		タイミングが何番目のラインかを求めて、1ライン当たりの座標を掛ける
		タイミング * 1000.f / 32分当たりの時間 * 32分当たりの座標
		タイミング * 1000.f / 単位y座標当たりの経過時間 = 下端からの変位
		laneそのまま代入
		timingそのまま代入
	*/
}