/*!
@file Floor.cpp
@brief 設定画面制御
*/

#include "stdafx.h"
#include "Project.h"

//-----------------------------------
///設定画面制御
//-----------------------------------


namespace basecross
{
	void Option::OnCreate()
	{
		CreateMenuSprites();
	}

	void Option::OnUpdate()
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();
		auto scene = app->GetScene<Scene>();

		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		if (!m_lock)
		{
			if (stickY > threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP || keyState.m_bUpKeyTbl['W'])
			{
				m_menuNum = (m_menuNum == 1) ? 3 : m_menuNum - 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				//scene->SEStart(L"Select");
			}
			else if (stickY < -threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN || keyState.m_bUpKeyTbl['S'])
			{
				m_menuNum = (m_menuNum % 3) + 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				//scene->SEStart(L"Select");
			}

			for (int i = 0; i < 3; i++)
			{
				if (auto s = m_SpriteVec[i].lock())
				{
					s->SetSelected((i + 1) == m_menuNum);
				}
			}
		}
		else if (std::abs(stickY) < 0.2f)
		{
			m_lock = false;
		}

		if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			//m_se = XAPtr1->Start(L"Confirm", XAUDIO2_NO_LOOP_REGION, 1.0f);
			//scene->SEStart(L"Confirm");

			switch (m_menuNum)
			{
			case 3:
				//設定終了

				break;
			}
		}

		auto volumeBGMpos = scene->m_volumeBGMpos;
		auto volumeSEpos = scene->m_volumeSEpos;

		auto BGMbar = m_bar_BGMNow.lock();
		BGMbar->GetComponent<Transform>()->SetPosition(Vec3(125.0f + volumeBGMpos, -50.0f, 0.0f));
		auto SEbar = m_bar_SENow.lock();
		SEbar->GetComponent<Transform>()->SetPosition(Vec3(125.0f + volumeSEpos, -150.0f, 0.0f));
	}
	
	void Option::CreateMenuSprites()
	{
		auto& app = App::GetApp();
		auto stage = GetStage();
		auto scene = app->GetScene<Scene>();

		auto volumeBGMpos = scene->m_volumeBGMpos;
		auto volumeSEpos = scene->m_volumeSEpos;

		Col4 baseColor = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		Col4 barSColor = Col4(0.25f, 0.25f, 0.25f, 1.0f);
		Col4 barEColor = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		//サウンド設定
		//BGMテキスト
		auto Button_BGM = stage->AddGameObject<Sprite>
			(L"TEX_T_BGM", true, Vec2(200.0f, 35.0f), Vec2(-250.0f, -50.0f), baseColor, baseColor);
		//SEテキスト
		auto Button_SE = stage->AddGameObject<Sprite>
			(L"TEX_T_SE", true, Vec2(200.0f, 35.0f), Vec2(-250.0f, -150.0f), baseColor, baseColor);

		//オーディオバー
		//BGM
		auto Bar_BGM = stage->AddGameObject<Sprite>
			(L"TEX_T_AudioBar", true, Vec2(400.0f, 3.0f), Vec2(125.0f, -50.0f), barSColor,barEColor);
		//SE
		auto Bar_SE = stage->AddGameObject<Sprite>
			(L"TEX_T_AudioBar", true, Vec2(400.0f, 3.0f), Vec2(125.0f, -150.0f), barSColor, barEColor);

		//オーディオバー現在地
		//BGM
		auto BGM_Now = stage->AddGameObject<Sprite>
			(L"TEX_T_AudioBar", true, Vec2(15.0f, 10.0f), Vec2(125.0f + volumeBGMpos, -50.0f), baseColor, baseColor);
		//SE
		auto SE_Now = stage->AddGameObject<Sprite>
			(L"TEX_T_AudioBar", true, Vec2(15.0f, 10.0f), Vec2(125.0f + volumeSEpos , -150.0f), baseColor, baseColor);


		//設定終了ボタン
		auto Button_Back = stage->AddGameObject<Sprite>
			(L"TEX_B_Back", true, Vec2(400.0f, 40.0f), Vec2(0.0f, -250.0f), baseColor, baseColor);

		m_text_BGM = Button_BGM;
		m_text_SE = Button_SE;
		m_button_Back = Button_Back;

		m_bar_BGM = Bar_BGM;
		m_bar_SE = Bar_SE;

		m_bar_BGMNow = BGM_Now;
		m_bar_SENow = SE_Now;

		m_SpriteVec[0] = Button_BGM;
		m_SpriteVec[1] = Button_SE;
		m_SpriteVec[2] = Button_Back;
	}

	void Option::OptionMenuActive(bool active)
	{
		//BGMテキスト
		auto Text_BGM = m_text_BGM.lock();
		m_text_BGM = Text_BGM;
		Text_BGM->SetDrawActive(active);

		//SEテキスト
		auto Text_SE = m_text_SE.lock();
		m_text_SE = Text_SE;
		Text_SE->SetDrawActive(active);

		//設定終了ボタン
		auto Button_Back = m_button_Back.lock();
		m_button_Back = Button_Back;
		Button_Back->SetDrawActive(active);

		//BGMバー
		auto Bar_BGM = m_bar_BGM.lock();
		m_bar_BGM = Bar_BGM;
		Bar_BGM->SetDrawActive(active);
		//SEバー
		auto Bar_SE = m_bar_SE.lock();
		m_bar_SE = Bar_SE;
		Bar_SE->SetDrawActive(active);

		//BGMバー現在地
		auto BGM_Now = m_bar_BGMNow.lock();
		m_bar_BGMNow = BGM_Now;
		BGM_Now->SetDrawActive(active);
		//SEバー現在地
		auto SE_Now = m_bar_SENow.lock();
		m_bar_SENow = SE_Now;
		SE_Now->SetDrawActive(active);
	}
}
