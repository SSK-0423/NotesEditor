#include "ShortNotes.hpp"
#include "WindowSize.hpp"
#include "AudioSource.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Transform.hpp"
#include "NotesData.hpp"
#include "NotesColor.hpp"
#include "NotesEditorMusic.hpp"
#include "AudioSource.hpp"
#include "InputDeviceContainer.hpp"
#include "DxLib.h"
#include <math.h>
#include <stdlib.h>

NotesEditor::NotesEditorMusic& NotesEditor::ShortNotes::notesEditorMusic = NotesEditor::NotesEditorMusic::Instance();
const int NotesEditor::ShortNotes::SHORTNOTESWIDTH = 80;
const int NotesEditor::ShortNotes::SHORTNOTESHEIGHT = 20;
const float NotesEditor::ShortNotes::playRange = 0.016f;

NotesEditor::ShortNotes::ShortNotes(const NotesData& notesData) : color(NotesColor::shortNotesColor)
{
	handClap = new Engine::Components::AudioSource("sounds/clap.ogg");
	transform->SetPosition(notesData.x, notesData.y);
	transform->SetSize(SHORTNOTESWIDTH, SHORTNOTESHEIGHT);
	screenPos->SetPosition(notesData.x, notesData.y);
	
	lane = notesData.lane;
	timing = notesData.timing;
	barNum = notesData.barNum;
	lineNum = notesData.lineNum;
	collider->Update();
}

NotesEditor::ShortNotes::~ShortNotes()
{
	delete handClap;
}

void NotesEditor::ShortNotes::Update()
{
	if (!notesEditorMusic.IsPlaying()) return;
	// TODO: timingと経過時間の差の計算を関数化する
	if (fabsf(timing - (static_cast<float>(notesEditorMusic.GetElapsedTime()) / 1000.f)) <= ShortNotes::playRange)
	{
		PlayClap();
	}
}

void NotesEditor::ShortNotes::Draw()
{
	DrawNotes();
	collider->Draw();
}

void NotesEditor::ShortNotes::ChangedScale(float size, bool isScaleUp)
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

	collider->Update();
}

NotesEditor::NOTESTYPE NotesEditor::ShortNotes::GetNotesType()
{
	return NOTESTYPE::SHORT_NOTES;
}

bool NotesEditor::ShortNotes::Collision(float x, float y)
{
	return collision->Collision(x, y, *collider);
}

void NotesEditor::ShortNotes::SetColor(Color c)
{
	color = c;
}

//ハンドクラップ再生
void NotesEditor::ShortNotes::PlayClap()
{
	// 多重再生回避の為に、
	// 1度再生が終わってから次の再生を行うようにする
	if (handClap->IsPlaying()) return;
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