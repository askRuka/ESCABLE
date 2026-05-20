/*!
@file ElectricTrigger.h
@brief ‘Ñ“dó‘Ô‚ÅG‚ê‚é‚Æ”½‰‚·‚é‘•’u‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class ElectricTrigger : public GameObject;
	//--------------------------------------------------------------------------------------
	class ElectricTrigger : public GameObjectForEdit
	{
	public:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	private:
		//std::shared_ptr<EffectElec> m_effectEl;

		bool m_Trigger;
		bool m_isCharging;
		float m_chargeTime;
	public:
		// \’z‚Æ”jŠü
		ElectricTrigger(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_Trigger(false),
			m_isCharging(false),
			m_chargeTime(0.0f)
		{
		}
		virtual ~ElectricTrigger()
		{
		}

		virtual void OnCreate() override; // ‰Šú‰»
		virtual void OnUpdate() override; // XV
		//virtual void OnDraw() override; // •`‰æ

		bool GetTrigger() const { return m_Trigger; }
		void SetTrigger(bool val) { m_Trigger = val; }		

		void SetIsCharging(bool b);
	};

}
//end basecross
