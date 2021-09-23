#pragma once
#include <vector>

/*
	���p�`�N���X
*/

namespace Game
{
	using Color = int;

	namespace Object
	{
		namespace Polygon
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
				void Init();
			};
		}
	}
}