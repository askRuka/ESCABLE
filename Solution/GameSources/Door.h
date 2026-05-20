/*!
@file Door.h
@brief ÉhÉA
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Door : public GameObject;
	//--------------------------------------------------------------------------------------
	class Door : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	private:
		shared_ptr<GameObject> m_Switch;
		bool m_OnDoor;
		float m_DeleteTime;
	public:
		// ç\ízÇ∆îjä¸
		Door(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_DeleteTime(5.0f)
		{
		}
		virtual ~Door()
		{
		}

		virtual void OnCreate() override; // èâä˙âª
		virtual void OnUpdate() override; // çXêV
		//virtual void OnDraw() override; // ï`âÊ
		void OnMove();
		void SwitchSetter(shared_ptr<GameObject> set);

		shared_ptr<GameObject> GetSwitchObject();
	};

}
//end basecross
