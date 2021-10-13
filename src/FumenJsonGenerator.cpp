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
    // �\�[�g
    /*
    *   timing�ŏ����Ƀ\�[�g����
    *   �N�C�b�N�\�[�g
    *   timing�����̔z�������ă\�[�g
    * �@��������g����notesList����בւ�
    */
    QuickSort(notesList, 0, notesList.size());
    // Json�I�u�W�F�N�g�̍쐬
	// ���ʃI�u�W�F�N�g
	picojson::object fumen;
    picojson::array notesDataList;

	for (auto notes : notesList)
	{
        NOTESTYPE type = notes->GetNotesType();
        int lane = notes->GetLane();
        float timing = notes->GetTiming();

		// �m�[�c
		picojson::object parentNotes;
        parentNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(type))));
        parentNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(lane))));
        parentNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(timing))));

        // �����O�m�[�c��������
        if (type == NOTESTYPE::LONG_NOTES)
        {
            /* 
                LongNotes�Ƀ_�E���L���X�g
                �n�_�E�I�_�m�[�c�擾
                �q�m�[�c���X�g�ɒǉ�
                �e�m�[�c�I�u�W�F�N�g��insert
            */
            std::vector<ShortNotes*> childList = dynamic_cast<LongNotes*>(notes)->GetChildNotesList();
            
            // �q�m�[�c���X�g
            picojson::array childNotesList;

            // �q�m�[�c���X�g�쐬
            for(auto child : childList)
            {
                NOTESTYPE childType= child->GetNotesType();
                int childLane = child->GetLane();
                float childTiming = child->GetTiming();
                // �q�m�[�c
                picojson::object childNotes;
                childNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(childType))));
                childNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(childLane))));
                childNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(childTiming))));

                childNotesList.push_back(picojson::value(childNotes));
            }

            parentNotes.insert(std::make_pair("notes", picojson::value(childNotesList)));
        }
        // �X���C�h�m�[�c��������
        if (type == NOTESTYPE::SLIDE_NOTES)
        {
            /* 
                SlideNotes�Ƀ_�E���L���X�g
                �q�m�[�c���X�g�擾
                json�I�u�W�F�N�g�̎q�m�[�c���X�g
            */
            std::vector<ShortNotes*> childList = dynamic_cast<SlideNotes*>(notes)->GetChildNotesList();

            // �q�m�[�c���X�g
            picojson::array childNotesList;

            // �q�m�[�c���X�g�쐬
            for (auto child : childList)
            {
                NOTESTYPE childType = child->GetNotesType();
                int childLane = child->GetLane();
                float childTiming = child->GetTiming();
                // �q�m�[�c
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

    // �m�[�c���X�g�ɒǉ�
    fumen.insert(std::make_pair("notes", picojson::value(notesDataList)));
	
    // ���ʐ���
	std::string fileName = "test.json";
	std::ofstream fumenFile(fileName);
	std::string json = static_cast<picojson::value>(fumen).serialize(true);
	fumenFile << json;
	fumenFile.close();
}

/*
    "NOTES": [
        {
            "TYPE": "�m�[�c�^�C�v",
            "LANE": "���[��",
            "TIMING": "����^�C�~���O",
            "NOTES": []
        },
        {
            "TYPE": "�m�[�c�^�C�v",
            "LANE": "���[��",
            "TIMING": "����^�C�~���O",
            "NOTES": [
                {
                    "TYPE": "�m�[�c�^�C�v",
                    "LANE": "���[��",
                    "TIMING": "����^�C�~���O",
                    "NOTES": []
                },
                {
                    "TYPE": "�m�[�c�^�C�v",
                    "LANE": "���[��",
                    "TIMING": "����^�C�~���O",
                    "NOTES": []
                }
            ]
        }
    ]
*/