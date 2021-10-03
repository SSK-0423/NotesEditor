#pragma once
#include "GameSymbol.hpp"

namespace Engine
{
	namespace Components
	{
		class Transform;
		class Position;
	}

	class GameObject {
	protected:
		// オブジェクトの位置・サイズ
		Components::Transform* transform;
		// 描画用座標
		Components::Position* screenPos;

	public:
		GameObject();
		virtual ~GameObject();

		const Components::Transform& GetTransform() const
		{
			return *transform;
		}

		Components::Transform& GetTransform()
		{
			return *transform;
		}
		
		Components::Position GetScreenPos();
		void UpdateScreenPos(Components::Position& pos);
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
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