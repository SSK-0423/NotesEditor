#include "CrossingNumberAlgorithm.hpp"
#include "Point.hpp"
#include "Polygon.hpp"

// �_�Ƒ��p�`�̓��O����A���S���Y��
bool Component::Collision::CrossingNumberAlgorithm::Collision(const PolygonObject::Point& target, const PolygonObject::Polygon& polygon)
{
	// �|���S���̒��_�z��擾
	std::vector<PolygonObject::Point> vertex = polygon.GetVertexList();
	// �����Ɏn�_��ǉ�
	vertex.push_back(vertex[0]);
	// �ӂƓ_����X�����ɐ����ɔ�΂���Ray�Ƃ̌�����
	int crossCount = 0;
	// y�̏㏸��
	float yIncreaseRatio = 0.f;

	for (size_t i = 0; i < vertex.size() - 1; i++)
	{
		// y���W�Ɋւ��锻��
		// ������̕� [�n�_,�I�_)�̒��ɂ��邩
		if ((vertex[i].y >= target.y) && (target.y > vertex[i + 1].y)
			// �������̕� (�n�_,�I�_]�̒��ɂ��邩
			|| (vertex[i].y < target.y) && (target.y <= vertex[i + 1].y))
		{
			// �_����X�����ɕ��s�ł�Ray���ӂƌ������邩����
			yIncreaseRatio = (target.y - vertex[i].y) / (vertex[i + 1].y - vertex[i].y);
			if (target.x < vertex[i].x + yIncreaseRatio * (vertex[i + 1].x - vertex[i].x))
			{
				crossCount++;
			}
		}
	}

	// �ӂƂ̌����񐔂����������_�͓����ɂ���
	if (crossCount % 2 != 0)
		return true;

	return false;
}
