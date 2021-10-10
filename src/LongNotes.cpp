#include "LongNotes.hpp"
#include "Transform.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "DxLib.h"

Color NotesEditor::LongNotes::color = GetColor(0, 0, 255);

NotesEditor::LongNotes::LongNotes(ShortNotes& start, ShortNotes& end) : startNotes(&start), endNotes(&end)
{
	Engine::Components::Position startNotesPos = start.GetTransform().GetPosition();
	Engine::Components::Position endNotesPos = end.GetTransform().GetPosition();

	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();

	float width = start.GetTransform().GetSize().width;
	float height = fabsf(endNotesPos.y - startNotesPos.y);
	float x = startNotesPos.x;
	float y = (startNotesPos.y + endNotesPos.y) / 2.f;

	transform->SetPosition(x, y);
	transform->SetSize(width, height);

	collider->Update();
}

NotesEditor::LongNotes::~LongNotes()
{
	delete transform;
	delete collider;
	delete collision;
}

NotesEditor::NOTESTYPE NotesEditor::LongNotes::GetNotesType()
{
	return NOTESTYPE::LONG_NOTES;
}

bool NotesEditor::LongNotes::Collision(float x, float y)
{
	return startNotes->Collision(x,y) || endNotes->Collision(x,y) || collision->Collision(x,y,*collider);
}

void NotesEditor::LongNotes::Update()
{
	startNotes->Update();
	endNotes->Update();

	Engine::Components::Position startNotesScreenPos;
	startNotesScreenPos.x = screenPos->x;
	startNotesScreenPos.y = screenPos->y + (startNotes->GetTransform().GetPosition().y - transform->GetPosition().y);
	startNotes->UpdateScreenPos(startNotesScreenPos);

	Engine::Components::Position endNotesScreenPos;
	endNotesScreenPos.x = screenPos->x;
	endNotesScreenPos.y = screenPos->y + (endNotes->GetTransform().GetPosition().y - transform->GetPosition().y);
	endNotes->UpdateScreenPos(endNotesScreenPos);
}

void NotesEditor::LongNotes::Draw()
{
	DrawMiddleLine();
	startNotes->Draw();
	endNotes->Draw();
	collider->Draw();
}

void NotesEditor::LongNotes::DrawMiddleLine()
{
	DrawLineAA(startNotes->GetScreenPos().x, startNotes->GetScreenPos().y,
		endNotes->GetScreenPos().x, endNotes->GetScreenPos().y, color, startNotes->GetTransform().GetSize().width);
}
