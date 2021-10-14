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
	int pivot_index = (right + left) / 2;   // ��_�@�����ł͓K���ɔz��̒����Ƃ���
	float pivot_timing = notesList[pivot_index]->GetTiming();
	
	// ����
	// ��l���E�[�̃f�[�^�ƌ���
	std::swap(notesList[pivot_index], notesList[right - 1]);
	/*
		��l���E�[�Ɂ��S�Ċ�l��菬�����Ƃ��Ă���
		�z����������l�Ɣ�r���s���A��l���傫��
	*/
	int i = left;
	// ��
	for (int j = left; j < right - 1; j++)
	{
		if (notesList[j]->GetTiming() < pivot_timing)
		{
			std::swap(notesList[i], notesList[j]);
			i++;
		}
	}
	std::swap(notesList[i], notesList[right - 1]);

	// �ċA�I�ɉ���
	QuickSort(notesList, left, i);			// ������(pivot_timing)����
	QuickSort(notesList, i + 1, right);		// �E����(pivot_timing)�ȏ�
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

// TODO:�q�m�[�c�쐬�̊֐���
void NotesEditor::FumenJsonGenerator::SaveFumen()
{
	QuickSort(*notesList, 0, notesList->size());
	// Json�I�u�W�F�N�g�̍쐬
	// ���ʃI�u�W�F�N�g
	picojson::object fumen;
	// �y�ȏ��ǉ�
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
	std::string fileName = "notes/" + musicName + ".json";
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