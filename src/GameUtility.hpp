#pragma once
#include <cmath>

// �Q�[���J���Ŏg���\���̂�萔�A���K�͊֐����܂Ƃ߂��t�@�C��

enum RESULT
{
	RESULT_SUCCEED = 0,
	RESULT_ERROR = -1
};

const int NONE = -1;

// �F
using Color = unsigned int;
// �摜
using Image = int;
// �I�[�f�B�I
using Audio = int;
// �t�H���g
using Font = int;
// �p�x
using Degree = float;
// ���W�A��
using Radian = float;
// �b
using Second = float;
// �~���b
using Msecond = float;

inline Radian DegreeToRadian(Degree angle)
{
	return acosf(-1.f) / 180.f * angle;
}

inline Msecond SecToMsec(Second sec)
{
	return sec * 1000.f;
}

inline Second MsecToSec(Msecond ms)
{
	return ms / 1000.f;
}