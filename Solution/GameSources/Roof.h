/*!
@file Roof.h
@brief ìVà‰
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Roof : public GameObject;
	//--------------------------------------------------------------------------------------
	class Roof : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		// ç\ízÇ∆îjä¸
		Roof(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)
		{
		}
		virtual ~Roof()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		//virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ
	};

}
//end basecross
