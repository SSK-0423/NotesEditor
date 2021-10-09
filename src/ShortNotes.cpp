#include "ShortNotes.hpp"
#include "WindowSize.hpp"
#include "AudioSource.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Transform.hpp"
#include "NotesData.hpp"
#include "NotesEditorMusic.hpp"
#include "AudioSource.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"
#include <math.h>
#include <stdlib.h>

//クラス変数実体化
//Engine::Components::AudioSource NotesEditor::ShortNotes::handClap("sounds/clap.ogg");
NotesEditor::NotesEditorMusic& NotesEditor::ShortNotes::notesEditorMusic = NotesEditor::NotesEditorMusic::Instance();
const int NotesEditor::ShortNotes::SHORTNOTESWIDTH = 80;
const int NotesEditor::ShortNotes::SHORTNOTESHEIGHT = 20;
float NotesEditor::ShortNotes::playRange = 0.001f;

NotesEditor::ShortNotes::ShortNotes(const NotesData& notesData) : color(GetColor(0, 255, 0))
{
	type = NOTESTYPE::SHORT_NOTES;
	handClap = new Engine::Components::AudioSource("sounds/clap.ogg");
	collider = new Engine::Components::BoxCollider(*transform);
	collision = new Engine::Collision::PointWithPolygon();

	transform->SetPosition(notesData.x, notesData.y);
	transform->SetSize(SHORTNOTESWIDTH, SHORTNOTESHEIGHT);
	screenPos->SetPosition(notesData.x, notesData.y);
	
	lane = notesData.lane;
	timing = notesData.timing;

	collider->Update();
}

NotesEditor::ShortNotes::~ShortNotes()
{
	delete handClap;
	delete collider;
	delete collision;
}

void NotesEditor::ShortNotes::Update()
{
	if (notesEditorMusic.IsPlaying())
	{
		if (fabsf(timing - (static_cast<float>(notesEditorMusic.GetElapsedTime()) / 1000.f)) <= ShortNotes::playRange)
		{
			PlayClap();
		}
	}
}

void NotesEditor::ShortNotes::Draw()
{
	DrawNotes();
	DebugDraw();
}

void NotesEditor::ShortNotes::SetColor(Color c)
{
	color = c;
}

Color NotesEditor::ShortNotes::GetNotesColor()
{
	return color;
}

//ハンドクラップ再生
void NotesEditor::ShortNotes::PlayClap()
{
	handClap->PlayOneShot();
}

// ノーツ描画
void NotesEditor::ShortNotes::DrawNotes()
{
	Engine::Components::Position pos = *screenPos;
	Engine::Components::Size size = transform->GetSize();

	DrawBoxAA(pos.x - size.width / 2.f, pos.y - size.height / 2.f,
		pos.x + size.width / 2.f, pos.y + size.height / 2.f, color, true);
}

// デバッグ用描画
void NotesEditor::ShortNotes::DebugDraw()
{
	DrawFormatString(800, 650, GetColor(0, 255, 0), "timing:%f", timing);
	if (fabsf(timing - static_cast<float>(notesEditorMusic.GetElapsedTime()) / 1000.f) <= ShortNotes::playRange)
	{
		DrawFormatString(800, 700, GetColor(0, 255, 0), "再生！");
	}
	else
	{
		DrawFormatString(800, 725, GetColor(0, 255, 0), "再生しない");
	}
}