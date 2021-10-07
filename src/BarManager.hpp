#pragma once
#include "GameObject.hpp"
#include "GameSymbol.hpp"
#include "Singleton.hpp"
#include <vector>

namespace NotesEditor
{
	class Bar;

	class BarManager : public Singleton<BarManager> {
		friend Singleton<BarManager>;
	private:
		BarManager();
		// �����������ߐ��I�u�W�F�N�g
		std::vector<Bar*> barList;

	public:
		void CreateBar(std::vector<Engine::GameObject*>& objList, int barNum);
		//���߃^�C�v�ύX 1/1
		void ChangeBarType();
		//���߃^�C�v�ύX1/4
		void ChangeBarType4();
		//���߃^�C�v�ύX 1/8
		void ChangeBarType8();
		//���߃^�C�v�ύX 1/16
		void ChangeBarType16();
		//���߃^�C�v�ύX 1/32
		void ChangeBarType32();

		void ChangeSize();
		bool Collision(float x, float y);
	};
}
