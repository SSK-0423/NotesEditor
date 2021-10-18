#pragma once

/*
* �V���[�g�m�[�c�����ɕK�v�ȃf�[�^
*/

namespace NotesEditor
{
	struct NotesData
	{
		float x;
		float y;
		int lane;
		float timing;
		int barNum;
		int lineNum;

		NotesData() : x(0.f), y(0.f), lane(0), timing(0.f), barNum(0), lineNum(0) {}
		NotesData(float x, float y, int lane, float timing, int barNum, int lineNum) : x(x), y(y), lane(lane), timing(timing), barNum(barNum),lineNum(lineNum) {}
	};
}