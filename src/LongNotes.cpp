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

	float width = startNotesPos.x;
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

void NotesEditor::LongNotes::Update()
{
	startNotes->Update();
	endNotes->Update();

	Engine::Components::Position startNotesScreenPos;
	startNotesScreenPos.x = screenPos->x;
	startNotesScreenPos.y = screenPos->y + transform->GetSize().height / 2.f;
	startNotes->UpdateScreenPos(startNotesScreenPos);

	Engine::Components::Position endNotesScreenPos;
	endNotesScreenPos.x = screenPos->x;
	endNotesScreenPos.y = screenPos->y - transform->GetSize().height / 2.f;
	endNotes->UpdateScreenPos(endNotesScreenPos);
}

void NotesEditor::LongNotes::Draw()
{
	collider->Draw();
	DrawMiddleLine();
	startNotes->Draw();
	endNotes->Draw();
	DrawFormatString(700, 350, color, "width:%f,height:%f", transform->GetSize().width, transform->GetSize().height);
}

void NotesEditor::LongNotes::DrawMiddleLine()
{
	DrawFormatString(700, 300, color, "sx:%f,sy:%f", startNotes->GetScreenPos().x, startNotes->GetScreenPos().y);
	DrawFormatString(700, 325, color, "ex:%f,ey:%f", endNotes->GetScreenPos().x, endNotes->GetScreenPos().y);
	DrawLineAA(startNotes->GetScreenPos().x, startNotes->GetScreenPos().y,
		endNotes->GetScreenPos().x, endNotes->GetScreenPos().y, color, startNotes->GetTransform().GetSize().width);
}
