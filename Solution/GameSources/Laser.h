#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class ElectricTrigger : public GameObject;
	//--------------------------------------------------------------------------------------
	class Laser : public GameObject
	{
	public:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_Velocity;
		float m_Fire;
		float m_Fade;
		float m_Delay;
		float m_TotalTime;
		shared_ptr<GameObject>m_Launcher;
		shared_ptr<EffectExplosion>m_effect;

		float m_time;
	public:
		// 構築と破棄
		Laser(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const Vec3& Velocity,
			const float& Fire,
			const float& Fade,
			const float& Delay
		) :
			GameObject(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_Velocity(Velocity),
			m_Fire(Fire),
			m_Fade(Fade),
			m_Delay(Delay),
			m_time(0.0f)
		{
		}
		virtual ~Laser()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		void Push();
		void HitCheck();
		void PlayerHitCheck(const shared_ptr<GameObject>& player); //特定のオブジェクトとの接触を確認する
		void WallHitCheck(const shared_ptr<GameObject>& wall); //特定のオブジェクトとの接触を確認する

	};

}
//end basecross
