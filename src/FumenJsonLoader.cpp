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
	// �Ȃ̑��Đ�����
	float totalTime = static_cast<float>(notesEditorMusic->GetTotalTime());
	// �Ȃ̔��q
	float beat = static_cast<float>(notesEditorMusic->GetBeat());
	// 1���߂̒���
	float barTimeLength = 60.f * 1000.f / static_cast<float>(notesEditorMusic->GetBPM()) * beat;
	// �ŏ������̒���
	float minimumNoteTimeLength = barTimeLength / BarManager::MAXNOTENUM;
	// �ŏ��P�ʉ���������̍��W
	float minimunNotePosY = static_cast<float>(WINDOW_SIZE_HEIGHT) / BarManager::MAXNOTENUM;
	// 32�����C�����Ԗڂ� * 32�����C��1�������Y���W
	int myLineNum = std::roundf(timing * 1000.f / minimumNoteTimeLength);

	return static_cast<float>(WINDOW_SIZE_HEIGHT) - myLineNum * minimunNotePosY;
}

NotesEditor::NotesData NotesEditor::FumenJsonLoader::MakeNotesData(picojson::value notesVal, NOTESTYPE parentType)
{
	/*
		���̊֐��̃^�X�N
		�ENotesData�̍쐬
		�E���[���擾
		�E�^�C�~���O�擾
		�EX���W�̌���
		�EY���W�̌v�Z
	*/
	// ���[��
	int lane = notesVal.get<picojson::object>()["lane"].get<double>();
	// �^�C�~���O
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
		���ʂ�JSON�t�@�C����ǂݍ���Ńm�[�c�𐶐�����
		�EJSON�t�@�C���ǂݍ���
		�E�ȓǂݍ���
		�E�m�[�c����
	*/
	// JSON�t�@�C��
	picojson::value fumen;
	// JSON�t�@�C���ǂݍ���
	OpenFileExplorer openFileExplorer;
	openFileExplorer.OpenJsonFile(fumen);
	// �ȓǂݍ���
	notesEditorMusic->LoadMusicFromFumen(fumen);
	// �m�[�c����
	CreateNotes(fumen);

	/*
		Json�ǂݍ���
		type�łǂ̃m�[�c�𐶐����邩���f
		type == long�̎���notes���擾���Ďn�_�ƏI�_�ɒǉ�
		type == slide�̎���notes���擾���Ďq�m�[�c��ǉ�

		�m�[�c�쐬
		NotesData���쐬���m�[�c����
		���[�����X���W�Z�o��laneManager��lanePosX,slideLanePosX���g��
		�^�C�~���O���Y���W�Z�o���^�C�~���O * 1000.f / ���Đ����� * ���߂̖��[���W�܂ł̕ψ�
		�^�C�~���O�����Ԗڂ̃��C���������߂āA1���C��������̍��W���|����
		�^�C�~���O * 1000.f / 32��������̎��� * 32��������̍��W
		�^�C�~���O * 1000.f / �P��y���W������̌o�ߎ��� = ���[����̕ψ�
		lane���̂܂ܑ��
		timing���̂܂ܑ��
	*/
}