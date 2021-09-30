#pragma once
/*
	�I�u�W�F�N�g�̃X�P�[����ێ�����N���X
*/
namespace Engine
{
	namespace Components
	{
		class Scale {
		private:
			float scaleWidth;
			float scaleHeight;

		public:
			Scale() : scaleWidth(1.f), scaleHeight(1.f){}
			Scale(float scaleW, float scaleH) : scaleWidth(scaleW),scaleHeight(scaleH)
			{
			}
			void Scaling(float scaleW, float scaleH) 
			{
				scaleWidth = scaleW;
				scaleHeight = scaleH;
			}
			float GetScaleWidth()
			{
				return scaleWidth;
			}
			float GetScaleHeight()
			{
				return scaleHeight;
			}
		};
	}
}