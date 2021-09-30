#pragma once
#include <vector>

/*
	���p�`�N���X
*/

using Color = int;

namespace Engine
{
	namespace PrimitiveObj
	{
		struct Point;

		class Polygon {
		private:
			// �|���S���̊e���_
			std::vector<Point*> vertex;
			// �F
			Color color;

		public:
			Polygon();
			// �R�s�[�R���X�g���N�^
			Polygon(const Polygon& polygon);

			~Polygon();
			// �`��
			void Draw();
			// ���_�ǉ�
			void AddPoint(float x, float y);
			// �F�ύX
			void ChangedColor(int r, int g, int b);
			// ���_���X�g�擾
			std::vector<Point> GetVertexList() const;
			// 
			void ResetVertex();
		};
	}
}