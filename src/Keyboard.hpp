#pragma once
#include "Singleton.hpp"
#include "InputDevice.hpp"

namespace Game {
	
	namespace Input {

		class Keyboard : public Singleton<Keyboard>, public InputDevice{
			friend Singleton<Keyboard>;
		private:
			Keyboard() : InputDevice(KEY_NUM), keyPressingCount(), keyReleasingCount(),keyPressed() {}
	
			// �L�[�̑���
			static constexpr int KEY_NUM = 256;
			// ������J�E���^
			mutable int keyPressingCount[KEY_NUM];
			// ������J�E���^
			mutable int keyReleasingCount[KEY_NUM];
			// �����ꂽ���ǂ���
			mutable bool keyPressed[KEY_NUM];
			// �J�E���^�X�V
			void UpdateCounter() const;
		public:
			void ReadInput() const override;
			int GetPressingCount(KeyCode keyCode) const override;
			int GetReleasingCount(KeyCode keyCode) const override;
			bool IsPressKey(KeyCode keyCode) const override;
			bool IsReleaseKey(KeyCode keyCode) const override;
		};
	}
}