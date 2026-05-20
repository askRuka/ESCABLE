/*!
@file Floor.cpp
@brief Ý’è‰æ–Ê§Œä
*/

#include "stdafx.h"
#include "Project.h"

//-----------------------------------
///Ý’è‰æ–Ê§Œä
//-----------------------------------


namespace basecross
{
	void HowToPlay::OnCreate()
	{
		CreateSprites();
	}

	void HowToPlay::OnUpdate()
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		if (!cntr.bConnected) return;

		auto scene = app->GetScene<Scene>();

		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;
	}

	void HowToPlay::CreateSprites()
	{
		auto& app = App::GetApp();
		auto stage = GetStage();

		Col4 baseColor = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		auto HowToPlay1 = stage->AddGameObject<Sprite>
			(L"TEX_HtP_Game", true, Vec2(1280.0f, 720.0f / 4), Vec2(0.0f, 0.0f), baseColor, baseColor);

		auto HowToPlay2 = stage->AddGameObject<Sprite>
			(L"TEX_HtP_Control", true, Vec2(1280.0f, 720.0f / 4), Vec2(0.0f, 0.0f), baseColor, baseColor);

		m_HtP1 = HowToPlay1;
		m_HtP2 = HowToPlay2;

		m_SpriteVec[0] = HowToPlay1;
		m_SpriteVec[1] = HowToPlay2;
	}

	void HowToPlay::HowToPlayMenuActive(bool active)
	{
		//‚ ‚»‚Ñ‚©‚½‚P•\Ž¦
		auto HtP1 = m_HtP1.lock();
		m_HtP1 = HtP1;
		HtP1->SetDrawActive(active);

		//‚ ‚»‚Ñ‚©‚½‚Q•\Ž¦
		auto HtP2 = m_HtP2.lock();
		m_HtP2 = HtP2;
		HtP2->SetDrawActive(!active);
	}

	void HowToPlay::HowToPlayInMenuActive()
	{
		//‚ ‚»‚Ñ‚©‚½‚P”ñ•\Ž¦
		auto HtP1 = m_HtP1.lock();
		m_HtP1 = HtP1;
		HtP1->SetDrawActive(false);

		//‚ ‚»‚Ñ‚©‚½‚Q”ñ•\Ž¦
		auto HtP2 = m_HtP2.lock();
		m_HtP2 = HtP2;
		HtP2->SetDrawActive(false);
	}
}
