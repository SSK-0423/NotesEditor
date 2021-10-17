#pragma once

/*
* ショートノーツ生成に必要なデータ
*/

namespace NotesEditor
{
	struct NotesData
	{
		float x;
		float y;
		int lane;
		float timing;

		NotesData() : x(0.f), y(0.f), lane(0), timing(0.f) {}
		NotesData(float x, float y, int lane, float timing) : x(x), y(y), lane(lane), timing(timing) {}
	};
}