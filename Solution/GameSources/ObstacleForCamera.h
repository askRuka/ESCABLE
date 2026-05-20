/*!
@file ObstacleForCamera.h
@brief ÉJÉÅÉâópÇÃå©Ç¶Ç»Ç¢è·äQï®
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class ObstacleForCamera : public GameObjectforEdit;
	//--------------------------------------------------------------------------------------
	class ObstacleForCamera : public GameObjectForEdit
	{
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;
	public:
		// ç\ízÇ∆îjä¸
		ObstacleForCamera(const shared_ptr<Stage>& stage,
			const Vec3& scale,
			const Vec3& rotation,
			const Vec3& position
		) :
			GameObjectForEdit(stage),
			m_scale(scale),
			m_rotation(rotation),
			m_position(position)
		{
		}
		virtual ~ObstacleForCamera()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		//virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ
	};

}
//end basecross
