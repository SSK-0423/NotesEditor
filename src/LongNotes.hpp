//#pragma once
//#include "Notes.hpp"
//#include "ShortNotes.hpp"
//#include <vector>
//
//namespace NotesEditor
//{
//	class LongNotes : public Notes {
//	private:
//		// �m�[�c�̐F
//		static unsigned int color;
//		//�n�_�m�[�c
//		ShortNotes* startNotes;
//		// �I�_�m�[�c
//		ShortNotes* endNotes;
//	public:
//		LongNotes(ShortNotes& start) ;
//		LongNotes(ShortNotes& start, ShortNotes& end) ;
//		~LongNotes() ;
//		void SetStartNotes(ShortNotes& start) ;
//		void SetEndNotes(ShortNotes& end) ;
//		void SetObjSize(int w, int h) ;
//		void Update()  override;
//		void Draw()  override;
//	};
//}