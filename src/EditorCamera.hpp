#pragma once
#include "Camera2D.hpp"
namespace NotesEditor
{
	class EditorCamera : public Engine::Camera2D{
	private:
	private:
		// �`��ΏۃI�u�W�F�N�g�̃|�C���^
		std::vector<std::vector<GameObject*>*>* objList; // objList[0] = objList objList->size() = 2 objList[0].size() = 2
		// �J�������̕`��\�I�u�W�F�N�g�̃|�C���^
		std::vector<GameObject*> drawList;
		// �J�����̌��_(������W)
		//Components::Position origin;

		void UpdateOrigin();
		// �J�������I�u�W�F�N�g�̍X�V����
		void UpdateInCameraObj();
		// �J�������I�u�W�F�N�g�̕`��
		void DrawInCameraObj();
		// �f�o�b�O�p�`��֐�
		void DebugDraw();
		// �L�[�{�[�h�A�}�E�X����
		void Controll() override;
		// �ړ����E
		void LimitPos() override;
		// �I�u�W�F�N�g���J�������ɓ��������ǂ����𔻒�
		bool Collision(const GameObject& obj);
		// �I�u�W�F�N�g�Ԃ̋������v�Z
		Vector2<float> CalcDistance(const Components::Transform& targetTransform);
		// 2�̃I�u�W�F�N�g�̃T�C�Y�̍��v�l���v�Z
		//Components::Size SumSize(const Components::Transform& targetTransform);

	public:
		EditorCamera();
		EditorCamera(std::vector<std::vector<GameObject*>*>& vec);
		~EditorCamera();

		void Update();
		void Draw();
		// �J�������I�u�W�F�N�g���X�g�̍X�V
		void UpdateDrawList();
		// �`��ΏۃI�u�W�F�N�g�̃������J��
		void DeleteObj();
		// �ړ����E���Z�b�g
		void SetMinposition(float x, float y);
		void SetMaxposition(float x, float y);
	};
}