#include "FumenJsonGenerator.hpp"
#include "Notes.hpp"
#include "LongNotes.hpp"
#include "SlideNotes.hpp"
#include "picojson.h"
#include <fstream>

NotesEditor::FumenJsonGenerator::FumenJsonGenerator()
{
}

void NotesEditor::FumenJsonGenerator::QuickSort(std::vector<Notes*>& notesList, int left, int right)
{

}

NotesEditor::FumenJsonGenerator::~FumenJsonGenerator()
{
}

void NotesEditor::FumenJsonGenerator::SaveFumen(std::vector<Notes*> notesList)
{
    float min = 0.0f;
    // ソート
    /*
    *   timingで昇順にソートする
    *   クイックソート
    *   timingだけの配列を作ってソート
    * 　→それを使ってnotesListを並べ替え
    */
    QuickSort(notesList, 0, notesList.size());
    // Jsonオブジェクトの作成
	// 譜面オブジェクト
	picojson::object fumen;
    picojson::array notesDataList;

	for (auto notes : notesList)
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
            for(auto child : childList)
            {
                NOTESTYPE childType= child->GetNotesType();
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
	std::string fileName = "test.json";
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