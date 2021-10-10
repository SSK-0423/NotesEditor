#include "LongNotesCreator.hpp"
#include "Transform.hpp"
#include "DxLib.h"

bool NotesEditor::LongNotesCreator::isStart = true;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::startNotes = nullptr;
NotesEditor::ShortNotes* NotesEditor::LongNotesCreator::endNotes = nullptr;

NotesEditor::LongNotesCreator::LongNotesCreator()
{
}

NotesEditor::LongNotesCreator::~LongNotesCreator()
{
}

NotesEditor::Notes* NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData)
{
	return nullptr;
}

void NotesEditor::LongNotesCreator::CreateNotes(const NotesData& notesData, std::vector<Engine::GameObject*>& objList)
{
	//�n�_�m�[�c
	if (isStart) 
	{
		//�n�_�m�[�c����
		startNotes = new ShortNotes(notesData);
		startNotes->SetColor(GetColor(0, 128, 255));

		//�I�_�m�[�c�t���O
		isStart = false;

		objList.push_back(startNotes);

		return;
	}

	//�I�_�m�[�c
	//�I�_�m�[�c�̈ʒu���n�_�m�[�c�����(��)�������烍���O�m�[�c�ݒu
	if (notesData.y < startNotes->GetTransform().GetPosition().y) {
		//�I�_�m�[�c����
		NotesData data(startNotes->GetTransform().GetPosition().x, notesData.y, notesData.lane, notesData.timing);
		endNotes = new ShortNotes(data);
		endNotes->SetColor(GetColor(0, 128, 255));
		//�����O�m�[�c����
		LongNotes* longNotes = new LongNotes(*startNotes, *endNotes);

		//�n�_�m�[�c�t���O
		isStart = true;
		//�����ɒǉ�����Ă���n�_�m�[�c�����X�g����폜
		objList.pop_back();
		//�����O�m�[�c�ǉ�
		objList.push_back(longNotes);
		//�n�_�m�[�c�𖳌��ɂ���
		startNotes = nullptr;
	}
}

void NotesEditor::LongNotesCreator::Cancel(std::vector<Engine::GameObject*>& objList)
{
	if (startNotes != nullptr)
	{
		objList.pop_back();
		isStart = true;
		delete startNotes;
		startNotes = nullptr;
	}
}

void NotesEditor::LongNotesCreator::DeleteNotes(Engine::GameObject& notes)
{

}
