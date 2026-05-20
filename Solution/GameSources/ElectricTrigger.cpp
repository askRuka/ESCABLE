/*!
@file ElectricTrigger.cpp
@brief ‘Ñ“dó‘Ô‚ÅG‚ê‚é‚Æ”½‰‚·‚é‘•’u‚È‚ÇÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//‰Šú‰»
	void ElectricTrigger::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_SWITCH");

		//m_effectEl = GetStage()->AddGameObject<EffectElec>(L"TEX_EF_Elec", Vec3(1.5f, 1.5f, 1.5f), Col4(0.5f, 0.25f, 0.0f, 1.0f), Col4(0.90f, 0.45f, 0.0f, 1.0f));
		//m_effectEl->SetOwner(GetThis<ElectricTrigger>());
		//m_effectEl->SetDrawActive(false);
	}

	void ElectricTrigger::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		if (m_isCharging)
		{
			m_chargeTime += delta;
			if (m_chargeTime > 0.0f)
			{
				m_Trigger = true;
			}
		}
		else
		{
			m_chargeTime = 0.0f;
		}
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
			if (m_Trigger)
			{
				ptrDraw->SetMeshResource(L"MODEL_SWITCH1");
				//m_effectEl->SetDrawActive(true);
			}

	}

	void ElectricTrigger::SetIsCharging(bool b)
	{
		m_isCharging = b;
	}

}
//end basecross
