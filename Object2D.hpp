#pragma once
struct Vector2D {
	float x;
	float y;
};

struct Object2D {
	Vector2D position;			//�I�u�W�F�N�g���W(�`��)
	Vector2D collisionPos;		//�I�u�W�F�N�g�̓����蔻��ʒu
	int width;					//��
	int height;					//����
};