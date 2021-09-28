#include "CrossingNumberAlgorithm.hpp"
#include "Point.hpp"
#include "Polygon.hpp"

// 点と多角形の内外判定アルゴリズム
bool Component::Collision::CrossingNumberAlgorithm::Collision(const PolygonObject::Point& target, const PolygonObject::Polygon& polygon)
{
	// ポリゴンの頂点配列取得
	std::vector<PolygonObject::Point> vertex = polygon.GetVertexList();
	// 末尾に始点を追加
	vertex.push_back(vertex[0]);
	// 辺と点からX方向に水平に飛ばしたRayとの交差回数
	int crossCount = 0;
	// yの上昇率
	float yIncreaseRatio = 0.f;

	for (size_t i = 0; i < vertex.size() - 1; i++)
	{
		// y座標に関する判定
		// 上向きの辺 [始点,終点)の中にあるか
		if ((vertex[i].y >= target.y) && (target.y > vertex[i + 1].y)
			// 下向きの辺 (始点,終点]の中にあるか
			|| (vertex[i].y < target.y) && (target.y <= vertex[i + 1].y))
		{
			// 点からX方向に平行でたRayが辺と交差するか判定
			yIncreaseRatio = (target.y - vertex[i].y) / (vertex[i + 1].y - vertex[i].y);
			if (target.x < vertex[i].x + yIncreaseRatio * (vertex[i + 1].x - vertex[i].x))
			{
				crossCount++;
			}
		}
	}

	// 辺との交差回数が奇数だったら点は内側にある
	if (crossCount % 2 != 0)
		return true;

	return false;
}
