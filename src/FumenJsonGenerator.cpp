#include "FumenJsonGenerator.hpp"
#include "Notes.hpp"
#include "LongNotes.hpp"
#include "SlideNotes.hpp"
#include "NotesEditorMusic.hpp"
#include "picojson.h"
#include <filesystem>
#include <fstream>

NotesEditor::FumenJsonGenerator::FumenJsonGenerator() : notesList(nullptr), notesEditorMusic(nullptr)
{
}

void NotesEditor::FumenJsonGenerator::QuickSort(std::vector<Notes*>& notesList, int left, int right)
{
	if (right - left <= 1) return;
	int pivot_index = (right + left) / 2;   // 基準点　ここでは適当に配列の中央とする
	float pivot_timing = notesList[pivot_index]->GetTiming();
	
	// 分割
	// 基準値を右端のデータと交換
	std::swap(notesList[pivot_index], notesList[right - 1]);
	/*
		基準値を右端に→全て基準値より小さいとしている
		配列を左から基準値と比較を行い、基準値より大きい
	*/
	int i = left;
	// 左
	for (int j = left; j < right - 1; j++)
	{
		if (notesList[j]->GetTiming() < pivot_timing)
		{
			std::swap(notesList[i], notesList[j]);
			i++;
		}
	}
	std::swap(notesList[i], notesList[right - 1]);

	// 再帰的に解く
	QuickSort(notesList, left, i);			// 左半分(pivot_timing)未満
	QuickSort(notesList, i + 1, right);		// 右半分(pivot_timing)以上
}

NotesEditor::FumenJsonGenerator::~FumenJsonGenerator()
{
}

void NotesEditor::FumenJsonGenerator::SetNotesList(std::vector<Notes*>& notesList)
{
	this->notesList = &notesList;
}

void NotesEditor::FumenJsonGenerator::SetNotesEditorMusic(NotesEditorMusic& notesEditorMusic)
{
	this->notesEditorMusic = &notesEditorMusic;
}

// TODO:子ノーツ作成の関数化
void NotesEditor::FumenJsonGenerator::SaveFumen()
{
	QuickSort(*notesList, 0, notesList->size());
	// Jsonオブジェクトの作成
	// 譜面オブジェクト
	picojson::object fumen;
	// 楽曲情報追加
	std::string musicName = notesEditorMusic->GetName();
	float bpm = notesEditorMusic->GetBPM();
	int beat = notesEditorMusic->GetBeat();
	std::string audioFilePath = "sounds\\" + musicName + ".ogg";

	fumen.insert(std::make_pair("name", picojson::value(musicName)));
	fumen.insert(std::make_pair("bpm", picojson::value(static_cast<double>(bpm))));
	fumen.insert(std::make_pair("beat", picojson::value(static_cast<double>(beat))));
	fumen.insert(std::make_pair("path", picojson::value(audioFilePath)));

	picojson::array notesDataList;

	for (auto notes : *notesList)
	{
		NOTESTYPE type = notes->GetNotesType();
		int lane = notes->GetLane();
		float timing = notes->GetTiming();

		// ノーツ
		picojson::object parentNotes;
		parentNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(type))));
		parentNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(lane))));
		parentNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(timing))));

		// ロングノーツだったら
		if (type == NOTESTYPE::LONG_NOTES)
		{
			/*
				LongNotesにダウンキャスト
				始点・終点ノーツ取得
				子ノーツリストに追加
				親ノーツオブジェクトにinsert
			*/
			std::vector<ShortNotes*> childList = dynamic_cast<LongNotes*>(notes)->GetChildNotesList();

			// 子ノーツリスト
			picojson::array childNotesList;

			// 子ノーツリスト作成
			for (auto child : childList)
			{
				NOTESTYPE childType = child->GetNotesType();
				int childLane = child->GetLane();
				float childTiming = child->GetTiming();
				// 子ノーツ
				picojson::object childNotes;
				childNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(childType))));
				childNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(childLane))));
				childNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(childTiming))));

				childNotesList.push_back(picojson::value(childNotes));
			}

			parentNotes.insert(std::make_pair("notes", picojson::value(childNotesList)));
		}
		// スライドノーツだったら
		if (type == NOTESTYPE::SLIDE_NOTES)
		{
			/*
				SlideNotesにダウンキャスト
				子ノーツリスト取得
				jsonオブジェクトの子ノーツリスト
			*/
			std::vector<ShortNotes*> childList = dynamic_cast<SlideNotes*>(notes)->GetChildNotesList();

			// 子ノーツリスト
			picojson::array childNotesList;

			// 子ノーツリスト作成
			for (auto child : childList)
			{
				NOTESTYPE childType = child->GetNotesType();
				int childLane = child->GetLane();
				float childTiming = child->GetTiming();
				// 子ノーツ
				picojson::object childNotes;
				childNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(childType))));
				childNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(childLane))));
				childNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(childTiming))));

				childNotesList.push_back(picojson::value(childNotes));
			}

			parentNotes.insert(std::make_pair("notes", picojson::value(childNotesList)));
		}

		notesDataList.push_back(picojson::value(parentNotes));
	}

	// ノーツリストに追加
	fumen.insert(std::make_pair("notes", picojson::value(notesDataList)));

	// 譜面制作
	std::string fileName = "notes/" + musicName + ".json";
	std::ofstream fumenFile(fileName);
	std::string json = static_cast<picojson::value>(fumen).serialize(true);
	fumenFile << json;
	fumenFile.close();
}

/*
	"NOTES": [
		{
			"TYPE": "ノーツタイプ",
			"LANE": "レーン",
			"TIMING": "判定タイミング",
			"NOTES": []
		},
		{
			"TYPE": "ノーツタイプ",
			"LANE": "レーン",
			"TIMING": "判定タイミング",
			"NOTES": [
				{
					"TYPE": "ノーツタイプ",
					"LANE": "レーン",
					"TIMING": "判定タイミング",
					"NOTES": []
				},
				{
					"TYPE": "ノーツタイプ",
					"LANE": "レーン",
					"TIMING": "判定タイミング",
					"NOTES": []
				}
			]
		}
	]
*/