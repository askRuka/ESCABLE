#pragma once
/*!
@file Floor.h
@brief è∞
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Floor : public GameObject;
	//--------------------------------------------------------------------------------------
	class ClearFloor : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		// ç\ízÇ∆îjä¸
		ClearFloor(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObject(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)
		{
		}
		virtual ~ClearFloor()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		//virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ
	};

}
//end basecross
