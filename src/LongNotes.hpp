//#pragma once
//#include "Notes.hpp"
//#include "ShortNotes.hpp"
//#include <vector>
//
//namespace NotesEditor
//{
//	class LongNotes : public Notes {
//	private:
//		// ノーツの色
//		static unsigned int color;
//		//始点ノーツ
//		ShortNotes* startNotes;
//		// 終点ノーツ
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