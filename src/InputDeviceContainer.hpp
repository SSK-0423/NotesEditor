#pragma once
#include "IInputDevice.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Singleton.hpp"
#include <vector>

/*
	���̓f�o�C�X�̃C���X�^���X���擾���邽�߂̃N���X
*/

namespace Engine
{
	namespace Input {

		class InputDeviceContainer : public Singleton<InputDeviceContainer> {
			friend Singleton<InputDeviceContainer>;
		private:
			InputDeviceContainer() {}

		public:
			// �L�[�{�[�h�̃C���X�^���X�擾
			const Keyboard& GetKeyboard() const
			{
				return Keyboard::Instance();
			}
			// �}�E�X�̃C���X�^���X�擾
			const Mouse& GetMouse() const
			{
				return Mouse::Instance();
			}
		};
	}
}

	/*
		����������
		�V�����f�o�C�X���ǉ����ꂽ�ꍇ�A�����ɐV�K��Get*���\�b�h��ǋL����K�v������B
		�����̃R�[�h�ɂ͕ύX�͉����Ȃ��Ă悢���I�[�v���N���[�Y�h�̌���
		Instance()���\�b�h�̒��g��Singleton�N���X���ő��ɕύX�͂Ȃ����ڍׂɈˑ����Ă���킯�ł͂Ȃ�
		�e���v���[�g�������ꍇ�̃����b�g
		�E�V����InputDevice���쐬���邾���ŁAInputDeviceContainer�ɂ͕ύX�������邱�ƂȂ����p�ł���
		�^�`�F�b�N�����悤�ɂ��AT�̃C���X�^���X���Ȃ��ƃ_����T���V���O���g�����ǂ����𒲂ׂ邽�߂ɃC���X�^���X�����Ȃ��Ⴂ���Ȃ����z��
	*/