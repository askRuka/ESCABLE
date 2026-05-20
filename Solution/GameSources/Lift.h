#pragma once
#include "stdafx.h"

namespace basecross {

class Lift : public GameObjectForEdit {
	Vec3 m_Scale;
	Vec3 m_Rotation;
	Vec3 m_Position;
	Vec3 m_Velocity;
	bool m_Lift;
	shared_ptr<GameObject>m_Frame;
	float m_backDelay;
	float m_delayTime;
	std::shared_ptr<SoundItem> m_SE; // ÉäÉtÉgÇÃSE

public:
	//ç\ízÇ∆îjä¸
	Lift(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const Vec3& Velocity
	);
	virtual ~Lift();
	//èâä˙âª
	virtual void OnCreate() override;
	virtual void OnUpdate() override;

	//ëÄçÏ
	bool GetLift()const { return m_Lift; }
	void SetLift(bool b);

	Vec3 GetVelocity() const { return m_Velocity; }
	 
	void SetLiftParameter(const Vec3& Scale, const Vec3& Rotation, const Vec3& Position, const Vec3& Velocity)
	{
		m_Scale = Scale;
		m_Rotation = Rotation;
		m_Position = Position;
		m_Velocity = Velocity;
	}
	void SEStop();
};




}
