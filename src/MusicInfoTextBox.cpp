#include "MusicInfoTextBox.hpp"
#include "TextureTextBox.hpp"
#include "Transform.hpp"
#include "NotesEditorMusic.hpp"

const int BOX_SIZE_WIDTH = 252;
const int BOX_SIZE_HEIGHT = 122;
const float TUNINGNUM = 8.f;

void NotesEditor::MusicInfoTextBox::UpdateText()
{
	// 表示テキスト初期化
	textBox->ResetText();

	// 表示テキストの設定
	std::string str = NotesEditorMusic::Instance().GetMusicName();
	textBox->AddText(str);
	str = "BPM:";
	str += std::to_string(static_cast<int>(NotesEditorMusic::Instance().GetBPM()));
	textBox->AddText(str);
	textBox->SetColor(GetColor(0,0,0));
}

NotesEditor::MusicInfoTextBox::MusicInfoTextBox(const char* filePath)
{
	textBox = new Engine::UI::TextureTextBox(filePath);
	textBox->GetTransform().SetPosition(BOX_SIZE_WIDTH / 2.f + TUNINGNUM, BOX_SIZE_HEIGHT / 2.f + TUNINGNUM);
	textBox->GetTransform().SetSize(BOX_SIZE_WIDTH, BOX_SIZE_HEIGHT);
	UpdateText();
}

NotesEditor::MusicInfoTextBox::~MusicInfoTextBox()
{
	delete textBox;
}

void NotesEditor::MusicInfoTextBox::Update()
{
	textBox->Update();
}

void NotesEditor::MusicInfoTextBox::Draw()
{
	textBox->Draw();
}
