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
		// ���C����
		int lineNum;
	public:
		// 1���ߓ�����̍ő剹����
		static const int MAXNOTENUM = 32;

		void CreateBar(std::vector<Engine::GameObject*>& objList, int barNum, int lineNum);
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
		float Collision(float x, float y);
		float CalcTiming(float y);
		unsigned int GetBarNum();
		int GetLineNum();
		void Delete();
	};
}
