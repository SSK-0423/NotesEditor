#pragma once
#include <vector>

/*
	多角形クラス
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
				// ポリゴンの各頂点
				std::vector<Point*> vertex;
				// 色
				Color color;

			public:
				Polygon();
				~Polygon();
				// 描画
				void Draw();
				// 頂点追加
				void AddPoint(float x, float y);
				// 色変更
				void ChangedColor(int r, int g, int b);
				// 頂点リスト取得
				std::vector<Point> GetVertexList() const;
				// 
				void Init();
			};
		}
	}
}