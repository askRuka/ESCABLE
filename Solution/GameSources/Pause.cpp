/*!
@file Floor.cpp
@brief ポーズ画面制御
*/

#include "stdafx.h"
#include "Project.h"

//-----------------------------------
///ポーズ画面制御
//-----------------------------------

namespace basecross
{
	//初期化
	void Pause::OnCreate()
	{
		auto stage = GetStage();

		//ポーズ背景
		auto backScreen = stage->AddGameObject<Sprite>(L"TEX_BackScreen", true, Vec2(800.0f, 200.0f), Vec2(0.0f, 0.0f), baseColor, baseColor);
		m_backscreen = backScreen;

		//タイトルロゴ
		auto titleLogo = stage->AddGameObject<Sprite>(L"TEX_TestTitle", true, Vec2(800.0f, 80.0f), Vec2(0.0f, 250.0f), baseColor, baseColor);
		m_titlelogo = titleLogo;

		//ツヅケル
		auto button_Restart = stage->AddGameObject<Sprite>(L"TEX_B_Restart", true, Vec2(400.0f, 40.0f), Vec2(0.0f, 90.0f), baseColor, baseColor);
		m_button_Restart = button_Restart;

		//セッテイ
		auto button_Option = stage->AddGameObject<Sprite>(L"TEX_B_Option", true, Vec2(400.0f, 40.0f), Vec2(0.0f, -20.0f), baseColor, baseColor);
		m_button_Option = button_Option;

		//アソビカタ
		auto button_HtP = stage->AddGameObject<Sprite>(L"TEX_B_HowToPlay", true, Vec2(400.0f, 40.0f), Vec2(0.0f, -130.0f), baseColor, baseColor);
		m_button_HtP = button_HtP;

		//タイトルヘ
		auto button_Title = stage->AddGameObject<Sprite>(L"TEX_B_Title", true, Vec2(400.0f, 40.0f), Vec2(0.0f, -240.0f), baseColor, baseColor);
		m_button_Title = button_Title;


		m_SpriteVec.push_back(button_Restart);
		m_SpriteVec.push_back(button_Option);
		m_SpriteVec.push_back(button_HtP);
		m_SpriteVec.push_back(button_Title);


		//照準
		auto guide = stage->AddGameObject<Sprite>(L"TEX_CableGuide", true, Vec2(40.0f, 10.0f), Vec2(0.0f, 0.0f), guideColor, guideColor);
		stage->SetSharedGameObject(L"Guide", guide);
		m_guide = guide;


		ChangeState(PauseClosed::Instance());
	}

	void Pause::OnUpdate()
	{
		if (m_currentState)
		{
			m_currentState->Execute(this);
		}
	}

	void Pause::OpenPause()
	{
		auto& app = App::GetApp();
		auto stage = GetStage();
		auto gameObjects = stage->GetGameObjectVec();

		for (auto& gameObject : gameObjects)
		{
			if (dynamic_pointer_cast<Pause>(gameObject))
			{
				continue;
			}
			gameObject->SetUpdateActive(false);
		}
		for (auto& sprite : m_SpriteVec)
		{
			auto spriteVec = sprite.lock();
			spriteVec->SetUpdateActive(true);
		}
	}

	void Pause::ClosePause()
	{
		auto stage = GetStage();
		auto gameObjects = stage->GetGameObjectVec();
		for (auto& gameObject : gameObjects)
		{
			if (dynamic_pointer_cast<Pause>(gameObject))
			{
				continue;
			}
			gameObject->SetUpdateActive(true);
		}
	}

	void Pause::OpenMenuBS()
	{
		//ポーズ背景表示
		auto backScreen = m_backscreen.lock();
		m_backscreen = backScreen;
		backScreen->SetDrawActive(true);

		//タイトルロゴ表示
		auto titleLogo = m_titlelogo.lock();
		m_titlelogo = titleLogo;
		titleLogo->SetDrawActive(true);

		//照準非表示
		auto guide = m_guide.lock();
		m_guide = guide;
		guide->SetDrawActive(false);
	}

	void Pause::OpenMenu()
	{
		//ツヅケル表示
		auto button_Restart = m_button_Restart.lock();
		m_button_Restart = button_Restart;
		button_Restart->SetDrawActive(true);

		//セッテイ表示
		auto button_Option = m_button_Option.lock();
		m_button_Option = button_Option;
		button_Option->SetDrawActive(true);

		//アソビカタ表示
		auto button_HtP = m_button_HtP.lock();
		m_button_HtP = button_HtP;
		button_HtP->SetDrawActive(true);

		//タイトルヘ表示
		auto button_Title = m_button_Title.lock();
		m_button_Title = button_Title;
		button_Title->SetDrawActive(true);
	}

	void Pause::CloseMenuBS()
	{
		//ポーズ背景非表示
		auto backScreen = m_backscreen.lock();
		m_backscreen = backScreen;
		backScreen->SetDrawActive(false);

		//タイトルロゴ非表示
		auto titleLogo = m_titlelogo.lock();
		m_titlelogo = titleLogo;
		titleLogo->SetDrawActive(false);

		//照準非表示
		auto guide = m_guide.lock();
		m_guide = guide;
		guide->SetDrawActive(true);
	}

	void Pause::CloseMenu()
	{

		//ツヅケル非表示
		auto button_Restart = m_button_Restart.lock();
		m_button_Restart = button_Restart;
		button_Restart->SetDrawActive(false);

		//セッテイ非表示
		auto button_Option = m_button_Option.lock();
		m_button_Option = button_Option;
		button_Option->SetDrawActive(false);

		//アソビカタ非表示
		auto button_HtP = m_button_HtP.lock();
		m_button_HtP = button_HtP;
		button_HtP->SetDrawActive(false);

		//タイトルヘ非表示
		auto button_Title = m_button_Title.lock();
		m_button_Title = button_Title;
		button_Title->SetDrawActive(false);



	}

	void Pause::OptionActive()
	{
		auto stage = GetStage();
		m_option = stage->AddGameObject<Option>();
		m_option->OptionMenuActive(true);
	}

	void Pause::OptionInActive()
	{
		m_option->OptionMenuActive(false);
	}

	void Pause::HowToPlayStart()
	{
		auto stage = GetStage();
		m_howtoplay = stage->AddGameObject<HowToPlay>();
		m_howtoplay->HowToPlayMenuActive(true);
	}

	void Pause::HowToPlayActive(bool active)
	{
		m_howtoplay->HowToPlayMenuActive(active);
	}


	void Pause::HowToPlayInActive()
	{
		m_howtoplay->HowToPlayInMenuActive();
	}


	void Pause::ChangeState(State<Pause>* newState)
	{
		if (m_currentState) m_currentState->Exit(this);
		m_currentState = newState;
		if (m_currentState)m_currentState->Enter(this);
	}

	void Pause::TitleBack()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<Pause>(), scene, L"ToTitleStage");
	}

	void Pause::StopBGM()
	{
		//auto& app = App::GetApp();
		//auto stage = GetStage();
		//auto soundMgr = stage->GetSharedGameObject<SoundMgr>(L"SoundMgr");
		//soundMgr->StopStageBGM();
		App::GetApp()->GetScene<Scene>()->BGMStop();

	}
}