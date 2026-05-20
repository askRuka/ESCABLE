/*!
@file Enemy.h
@brief エネミー
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Enemy : public GameObjectForEdit;
	//--------------------------------------------------------------------------------------
	class Enemy : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_shotTime;
		float m_eyeDis;
		Vec3 m_eyePosition;
		vector<std::weak_ptr<Lift>> m_liftVec;
		const float m_baseHight = 17.0f;
		bool m_isDead;
		bool m_isStay;
	public:
		// 構築と破棄
		Enemy(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_shotTime(0.0f),
			m_eyeDis(3.0f),
			m_eyePosition(Vec3(0.0f, 15.0f, 3.0f))

		{
		}
		virtual ~Enemy()
		{
		}

		Vec3 TargetPlayer(const shared_ptr<GameObject>& player);
		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		void LiftVecSetting();
		float LiftCollision();
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
