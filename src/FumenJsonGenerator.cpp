#include "FumenJsonGenerator.hpp"
#include "Notes.hpp"
#include "LongNotes.hpp"
#include "SlideNotes.hpp"
#include "NotesEditorMusic.hpp"
#include <fstream>
#include <Windows.h>

NotesEditor::FumenJsonGenerator::FumenJsonGenerator() : isSaveComplete(true), notesList(nullptr), notesEditorMusic(nullptr)
{
}


NotesEditor::FumenJsonGenerator::~FumenJsonGenerator()
{
	notesList = nullptr;
	notesEditorMusic = nullptr;
}

void NotesEditor::FumenJsonGenerator::Draw()
{
	DrawSaveText();
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
	// �m�[�c�𔻒�^�C�~���O�ŏ����\�[�g
	QuickSort(*notesList, 0, notesList->size());
	// ���ʃI�u�W�F�N�g
	picojson::object fumen;
	// �y�ȏ��ǉ�
	AddMusicInfo(fumen);
	// �m�[�c�f�[�^�ǉ�
	MakeNotesDataList(fumen);

	// ���ʐ���
	std::string fileName = "notes/" + notesEditorMusic->GetMusicName() + ".json";
	std::ofstream fumenFile(fileName);
	std::string json = static_cast<picojson::value>(fumen).serialize(true);
	fumenFile << json;
	fumenFile.close();

	SaveCompleted();
}

void NotesEditor::FumenJsonGenerator::NotSaveCompleted()
{
	isSaveComplete = false;
}

void NotesEditor::FumenJsonGenerator::DrawSaveText()
{
	if (isSaveComplete)
	{
		DrawFormatString(50, 740, GetColor(0, 255, 0), "�ۑ�����");
		return;
	}
	DrawFormatString(50, 740, GetColor(0, 255, 0), "���ۑ��̃f�[�^����");
}

void NotesEditor::FumenJsonGenerator::QuickSort(std::vector<Notes*>& notesList, size_t left, size_t right)
{
	if (right - left <= 1) return;
	size_t pivot_index = (right + left) / 2;   // ��_�@�����ł͓K���ɔz��̒����Ƃ���
	float pivot_timing = notesList[pivot_index]->GetTiming();

	// ����
	// ��l���E�[�̃f�[�^�ƌ���
	std::swap(notesList[pivot_index], notesList[static_cast<size_t>(right) - 1]);
	size_t i = left;
	for (size_t j = left; j < right - 1; j++)
	{
		if (notesList[j]->GetTiming() < pivot_timing)
		{
			std::swap(notesList[i], notesList[j]);
			i++;
		}
	}
	std::swap(notesList[i], notesList[static_cast<size_t>(right) - 1]);

	// �ċA�I�ɉ���
	QuickSort(notesList, left, i);			// ������(pivot_timing)����
	QuickSort(notesList, i + 1, right);		// �E����(pivot_timing)�ȏ�
}

void NotesEditor::FumenJsonGenerator::MakeLongNotesData(picojson::object& parentNotes, Notes& notes)
{
	std::vector<ShortNotes*> childList = dynamic_cast<LongNotes*>(&notes)->GetChildNotesList();

	// �q�m�[�c���X�g
	picojson::array childNotesList;

	// �q�m�[�c���X�g�쐬
	for (auto child : childList)
	{
		NOTESTYPE childType = child->GetNotesType();
		int childLane = child->GetLane();
		float childTiming = child->GetTiming();
		int childBarNum = child->GetBarNum();
		int childLineNum = child->GetLineNum();

		// �q�m�[�c
		picojson::object childNotes;
		childNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(childType))));
		childNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(childLane))));
		childNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(childTiming))));
		childNotes.insert(std::make_pair("barNum", picojson::value(static_cast<double>(childBarNum))));
		childNotes.insert(std::make_pair("lineNum", picojson::value(static_cast<double>(childLineNum))));

		childNotesList.push_back(picojson::value(childNotes));
	}
	parentNotes.insert(std::make_pair("notes", picojson::value(childNotesList)));
}

void NotesEditor::FumenJsonGenerator::MakeSlideNotesData(picojson::object& parentNotes, Notes& notes)
{
	std::vector<ShortNotes*> childList = dynamic_cast<SlideNotes*>(&notes)->GetChildNotesList();

	// �q�m�[�c���X�g
	picojson::array childNotesList;

	// �q�m�[�c���X�g�쐬
	for (auto child : childList)
	{
		NOTESTYPE childType = child->GetNotesType();
		int childLane = child->GetLane();
		float childTiming = child->GetTiming();
		int childBarNum = child->GetBarNum();
		int childLineNum = child->GetLineNum();
		// �q�m�[�c
		picojson::object childNotes;
		childNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(childType))));
		childNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(childLane))));
		childNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(childTiming))));
		childNotes.insert(std::make_pair("barNum", picojson::value(static_cast<double>(childBarNum))));
		childNotes.insert(std::make_pair("lineNum", picojson::value(static_cast<double>(childLineNum))));

		childNotesList.push_back(picojson::value(childNotes));
	}
	parentNotes.insert(std::make_pair("notes", picojson::value(childNotesList)));
}

void NotesEditor::FumenJsonGenerator::MakeNotesDataList(picojson::object& fumen)
{
	picojson::array notesDataList;

	for (auto notes : *notesList)
	{
		NOTESTYPE type = notes->GetNotesType();
		int lane = notes->GetLane();
		float timing = notes->GetTiming();
		int barNum = notes->GetBarNum();
		int lineNum = notes->GetLineNum();
		// �m�[�c
		picojson::object parentNotes;
		parentNotes.insert(std::make_pair("type", picojson::value(static_cast<double>(type))));
		parentNotes.insert(std::make_pair("lane", picojson::value(static_cast<double>(lane))));
		parentNotes.insert(std::make_pair("timing", picojson::value(static_cast<double>(timing))));
		parentNotes.insert(std::make_pair("barNum", picojson::value(static_cast<double>(barNum))));
		parentNotes.insert(std::make_pair("lineNum", picojson::value(static_cast<double>(lineNum))));

		// �����O�m�[�c��������
		if (type == NOTESTYPE::LONG_NOTES)
		{
			MakeLongNotesData(parentNotes, *notes);
		}
		// �X���C�h�m�[�c��������
		if (type == NOTESTYPE::SLIDE_NOTES)
		{
			MakeSlideNotesData(parentNotes, *notes);
		}
		notesDataList.push_back(picojson::value(parentNotes));
	}
	fumen.insert(std::make_pair("notes", picojson::value(notesDataList)));
}

void NotesEditor::FumenJsonGenerator::AddMusicInfo(picojson::object& fumen)
{
	std::string musicName = notesEditorMusic->GetMusicName();
	float bpm = notesEditorMusic->GetBPM();
	int beat = notesEditorMusic->GetBeat();
	std::string audioFilePath = "sounds\\" + musicName + ".ogg";

	fumen.insert(std::make_pair("name", picojson::value(musicName)));
	fumen.insert(std::make_pair("bpm", picojson::value(static_cast<double>(bpm))));
	fumen.insert(std::make_pair("beat", picojson::value(static_cast<double>(beat))));
	fumen.insert(std::make_pair("path", picojson::value(audioFilePath)));
}

void NotesEditor::FumenJsonGenerator::SaveCompleted()
{
	isSaveComplete = true;
}
