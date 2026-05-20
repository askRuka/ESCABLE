#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class ElectricTrigger : public GameObject;
	//--------------------------------------------------------------------------------------
	class Luncher : public GameObjectForEdit
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

	public:
		// ç\ízÇ∆îjä¸
		Luncher(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const Vec3& Velocity,
			const float& Fire,
			const float& Fade,
			const float& Delay
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_Velocity(Velocity),
			m_Fire(Fire),
			m_Fade(Fade),
			m_Delay(Delay)
		{
		}
		virtual ~Luncher()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		virtual void OnUpdate() override; // çXêV
		Vec3 GetVelocity() const { return m_Velocity; }
		float GetFire() const  { return m_Fire; }
		float GetFade() const { return m_Fade; }
		float GetDelay() const { return m_Delay; }
		void SetLuncherParameter(const Vec3& scale, const Vec3& rotation, const Vec3& position, const Vec3& velocity, float fire, float fade, float delay)
		{
			m_Scale = scale;
			m_Rotation = rotation;
			m_Position = position;
			m_Velocity = velocity;
			m_Fire = fire;
			m_Fade = fade;
			m_Delay = delay;
		}
	};

}
//end basecross
