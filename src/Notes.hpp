#pragma once
#include "GameObject.hpp"

namespace NotesEditor
{
	class Notes : public Engine::GameObject
	{
	protected:
		// ����^�C�~���O�����ߐ��̖��[���W / �Ȃ̒��� * �m�[�c�̍��W
		float timing;
		// �m�[�c�̃��[��
		int lane;
	public:
		//virtual void Put() noexcept {}

		// �^�C�~���O�擾
		float GetTiming() noexcept;
		// ���[���ԍ��擾
		int GetLane() noexcept;

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}