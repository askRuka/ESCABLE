
#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Checkpoint : public GameObject;
	//--------------------------------------------------------------------------------------
	class ClearObject : public GameObjectForEdit
	{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		bool m_isPass;
	public:
		// ç\ízÇ∆îjä¸
		ClearObject(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rotation, const Vec3& position) :
			GameObjectForEdit(stage),
			m_scale(scale),
			m_rotation(rotation),
			m_position(position),
			m_isPass(false)
		{
		}
		virtual ~ClearObject()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ
		void CreateTitle();
		void ClearPause();

	};

}
//end basecross
