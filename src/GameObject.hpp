#pragma once
#include "GameSymbol.hpp"
#include "Transform.hpp"

namespace Game
{

	namespace Object
	{
		
		namespace GameObject
		{

			class GameObject {
			protected:
				// オブジェクトの位置・サイズ
				Component::Transform transform;

			public:
				GameObject() noexcept;
				~GameObject() noexcept;

				const Component::Transform& GetTransform() const
				{
					return transform;
				}

				Component::Transform& GetTransform()
				{
					return transform;
				}

				virtual void Update() = 0;
				virtual void Draw() = 0;
			};
		}
	}
}

/*
	なぜTransformを作ったか
	・クラスにTransformを持たせるだけで、位置・サイズというパラメータとそのgetter/setterを実現することができるから
	・いちいち書く必要がなくなって楽

	Transformのgetterをポインタではなく値を返すようにすると
	・Transformをコンポジットするクラスに位置やサイズのgetter/setterを書く必要が出てくる
	・Transformを作った理由に反する

	ポインタを返す際の問題点
	・座標を取得したいだけの場合でも、座標・サイズの変更が可能になってしまう
	　例：Camera2D::Collision
*/