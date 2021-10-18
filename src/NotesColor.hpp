#pragma once
#include "DxLib.h"
#include "GameUtility.hpp"

/*
* ノーツの色をまとめた構造体
*/

namespace NotesEditor
{
	struct NotesColor
	{
		static Color shortNotesColor;
		static Color longNotesColor;
		static Color longNotesLineColor;
		static Color slideNotesColor;
		static Color slideNotesLineColor;
		static Color puttingNotesColor;
		static Color puttingLineColor;
	};
}