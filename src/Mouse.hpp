#pragma once
#include "DxLib.h"
#include "Game.hpp"
#include "Singleton.hpp"
#include "InputDevice.hpp"

namespace Game {

	namespace Input {

		class Mouse : public Singleton<Mouse>, public InputDevice{
			friend Singleton<Mouse>;

		private:
			Mouse() : InputDevice(KEY_NUM),buttonPressingCount(),buttonReleasingCount(),buttonPressed() {}

			// �L�[����
			static constexpr int KEY_NUM = 8;

			// �}�E�X�|�C���^�̍��W
			mutable Position2D<int> mousePos;

			// ������J�E���^
			mutable int buttonPressingCount[KEY_NUM];
			// ������J�E���^
			mutable int buttonReleasingCount[KEY_NUM];
			// �����ꂽ���ǂ���
			mutable bool buttonPressed[KEY_NUM];
			// �J�E���^�X�V
			void UpdateCounter() const;

		public:
			static constexpr int LEFT_CLICK = 0;
			static constexpr int RIGHT_CLICK = 1;

			// �X�V
			void ReadInput() const override;
			// keyCode�̃L�[��������Ă���t���[�������擾
			int GetPressingCount(KeyCode keyCode) const override;
			// keyCode�̃L�[��������Ă���t���[�������擾
			int GetReleasingCount(KeyCode keyCode) const override;
			// �L�[�������ꂽ��
			bool IsPressKey(KeyCode keyCode) const override;
			// �L�[���痣���ꂽ��
			bool IsReleaseKey(KeyCode keyCoce) const override;

			// �}�E�X�|�C���^�̍��W�擾
			Position2D<int> GetPosition() const { return mousePos; }
			// �}�E�X�|�C���^��X���W�擾
			int GetPosX() const { return mousePos.x; }
			// �}�E�X�|�C���^��Y���W�擾
			int GetPosY() const { return mousePos.y; }
		};
	}
}