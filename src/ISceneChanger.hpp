#pragma once

typedef enum 
{
	SCENE_EDIT,
	SCENE_NONE
} SCENE;

namespace Game {

	namespace System {

		//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
		class ISceneChanger{
		public:
			virtual ~ISceneChanger() = 0;
			//�w��V�[���ɕύX����
			virtual void ChangeScene(SCENE NextScene) = 0;
		};
	}
}