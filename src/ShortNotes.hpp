#pragma once
#include "Notes.hpp"


class ShortNotes : public Notes {
private:
	Audio clapHandle;
	Color color;
	void PlayClap() noexcept;
	// ノーツ描画
	void DrawNotes();
	// デバッグ用の描画
	void DebugDraw();
public:
	static const int SHORTNOTESWIDTH;
	static const int SHORTNOTESHEIGHT;
	
	ShortNotes(float& x, float& y) noexcept;
	~ShortNotes() noexcept;
	void Update() noexcept override;
	void Draw() noexcept override;
	void SetColor(Color c);
	Color GetNotesColor();
};