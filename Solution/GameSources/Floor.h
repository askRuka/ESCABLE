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
	class Floor : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		vector<VertexPositionNormalTexture> m_vertices;

	public:
		// ç\ízÇ∆îjä¸
		Floor(const shared_ptr<Stage>& stage,
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
		virtual ~Floor()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		//virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ

		void SetParameret(const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

	};

}
//end basecross
