/*!
@file EnemyLaser.h
@brief “G‚ÌUŒ‚
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class EnemyLaser : public GameObject;
	//--------------------------------------------------------------------------------------
	class EnemyLaser : public GameObject
	{
		Vec3 m_position;
		Vec3 m_direction;
		Vec3 m_hitPosition;
		shared_ptr<Transform> m_transComp;

	public:
		// \’z‚Æ”jŠü
		EnemyLaser(const shared_ptr<Stage>& stage, const Vec3& position, const Vec3& direction) :
			GameObject(stage),
			m_position(position),
			m_direction(direction),
			m_hitPosition(Vec3(0.0f, -10.0f, 0.0f))
		{
		}
		virtual ~EnemyLaser()
		{
		}

		virtual void OnCreate() override; // ‰Šú‰»
		virtual void OnUpdate() override; // XV
		void HitPositionCalc();
		//virtual void OnDraw() override; // •`‰æ
	};

}
//end basecross
