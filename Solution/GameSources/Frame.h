#pragma once
#include "stdafx.h"

namespace basecross {

	class Frame : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool m_Lift;

	public:
		//\’z‚Æ”jŠü
		Frame(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Frame();
		//‰Šú‰»
		virtual void OnCreate() override;
		//‘€ì
		bool GetLift()const { return m_Lift; }
		void SetLift(bool b);
	};




}
