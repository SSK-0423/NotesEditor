#include "LongNotes.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "NotesColor.hpp"
#include "DxLib.h"

NotesEditor::LongNotes::LongNotes(ShortNotes& start)// : startNotes(&start)
{
	lane = start.GetLane();
	timing = start.GetTiming();
	barNum = start.GetBarNum();
	lineNum = start.GetLineNum();
	start.SetColor(NotesColor::longNotesColor);
	// 始点ノーツ追加
	notesList.push_back(&start);

	Init();
}

NotesEditor::LongNotes::~LongNotes()
{
}

NotesEditor::NOTESTYPE NotesEditor::LongNotes::GetNotesType()
{
	return NOTESTYPE::LONG_NOTES;
}

bool NotesEditor::LongNotes::Collision(float x, float y)
{
	return notesList[0]->Collision(x, y) || notesList.back()->Collision(x, y) || collision->Collision(x, y, *collider);
}

void NotesEditor::LongNotes::Update()
{
	UpdateNotes();
	UpdateNotesScreenPos();
}

void NotesEditor::LongNotes::Draw()
{
	DrawMiddleLine();
	DrawNotes();
}

void NotesEditor::LongNotes::ChangedTransformByScale(float scale, bool isScaleUp)
{
	// 倍率が上がった場合
	if (isScaleUp)
	{
		// 座標とスケールの更新
		transform->SetPosition(transform->GetPosition().x,
			transform->GetPosition().y - 6.f * lineNum - 192.f * barNum);
	}
	else
	{
		transform->SetPosition(transform->GetPosition().x,
			transform->GetPosition().y + 6.f * lineNum + 192.f * barNum);
	}

	for (auto notes : notesList)
		notes->ChangedTransformByScale(scale, isScaleUp);

	Init();
	transform->Scaling(1.f, scale);
	// スケール1倍の時のサイズを設定する
	Engine::Components::Size size = transform->GetSize();
	transform->SetSize(size.width, size.height / scale);
	collider->Update();
}

void NotesEditor::LongNotes::AddEndNotes(ShortNotes& end)
{
	end.SetColor(NotesColor::longNotesColor);
	notesList.push_back(&end);
	Init();
}

std::vector<NotesEditor::ShortNotes*> NotesEditor::LongNotes::GetChildNotesList()
{
	return notesList;
}

void NotesEditor::LongNotes::UpdateNotes()
{
	for (auto notes : notesList)
	{
		notes->Update();
	}
}

void NotesEditor::LongNotes::UpdateNotesScreenPos()
{
	for (auto notes : notesList)
	{
		Engine::Components::Position newNotesScreenPos;
		newNotesScreenPos.x = screenPos->x;
		newNotesScreenPos.y = screenPos->y + (notes->GetTransform().GetPosition().y - transform->GetPosition().y);
		notes->UpdateScreenPos(newNotesScreenPos);
	}
}

void NotesEditor::LongNotes::DrawNotes()
{
	for (auto notes : notesList)
	{
		notes->Draw();
	}
}

void NotesEditor::LongNotes::Init()
{
	Engine::Components::Position startNotesPos = notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetTransform().GetPosition();
	Engine::Components::Position endNotesPos = notesList.back()->GetTransform().GetPosition();

	float width = notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetTransform().GetSize().width;
	float height = fabsf(endNotesPos.y - startNotesPos.y);
	if (notesList.size() == 1)
		height = notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetTransform().GetSize().height;
	float x = startNotesPos.x;
	float y = (startNotesPos.y + endNotesPos.y) / 2.f;

	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	collider->Update();
}

void NotesEditor::LongNotes::DrawMiddleLine()
{
	if (notesList.size() == 2)
	{
		DrawLineAA(notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetScreenPos().x, notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetScreenPos().y,
			notesList[static_cast<int>(LONGNOTES::ENDNOTES)]->GetScreenPos().x, notesList[static_cast<int>(LONGNOTES::ENDNOTES)]->GetScreenPos().y, NotesColor::longNotesLineColor, notesList[static_cast<int>(LONGNOTES::STARTNOTES)]->GetTransform().GetSize().width);
	}
}
