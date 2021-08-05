#pragma once
#include "Game.hpp"
#include "Object.hpp"
class GameObject : public Object{
protected:

	// �摜�n���h��
	int imageHandle;

	// �I�u�W�F�N�g�̍����A��
	int width;
	int height;

public:
	GameObject() noexcept;
	~GameObject() noexcept;

	// �I�u�W�F�N�g�̕`����W
	Position<float> position;
	// �I�u�W�F�N�g�̍��W
	Position<float> collisionPos;

	// �摜�̐ݒ�
	void SetHandle(int handle) noexcept;
	// �ʒu�̐ݒ�E�X�V
	void SetPosition(float x, float y) noexcept;
	// ���̎擾
	int GetObjWidth() noexcept;
	// �����̎擾
	int GetObjHeight() noexcept;

	virtual void Update() noexcept;
	virtual void Draw() noexcept;
};

//class GameObject : public Object {
//protected:
//	Transform transform;
//public:
//	GameObject();
//	~GameObject();
////	virtual void Update() noexcept;
////	virtual void Draw() noexcept;
//};
//
//int main() {
//	GameObject obj;
//	obj.GetComponent<Transform>().
//}
