#pragma once
#include "GameObject.hpp"
#include "IPlayable.hpp"
#include "GameSymbol.hpp"
#include "Transform.hpp"
#include "TestObject.h"
#include <vector>

namespace Engine
{
	namespace Collider 
	{
		class ICollider;
	}
	
	namespace Collision
	{
		class RectWithRect;
	}

	class Camera2D : public GameObject, IPlayable {
	private:
		// �`��ΏۃI�u�W�F�N�g�̃|�C���^
		std::vector<Engine::GameObject*>& objList;
		// �J�������̕`��\�I�u�W�F�N�g�̃|�C���^
		std::vector<GameObject*> drawList;
		// �J�����̌��_(������W)
		Components::Position origin;
		
		// �J�����̌��_���W�X�V
		void UpdateOrigin();
		// �J�������I�u�W�F�N�g���X�g�̍X�V
		void UpdateDrawList();
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
		Components::Size SumSize(const Components::Transform& targetTransform);

		void AutoScroll();
	public:
		Camera2D(std::vector<Engine::GameObject*>& objList);
		~Camera2D();

		void Update();
		void Draw();
		// �`��ΏۃI�u�W�F�N�g�̃������J��
		void DeleteObj();
		// �J�����̌��_���W�擾
		Components::Position GetOriginPos();
		// �ړ����E���Z�b�g
		void SetMinposition(float x, float y);
		void SetMaxposition(float x, float y);

	};
}