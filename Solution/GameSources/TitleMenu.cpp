#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//-----------------------------------
	///タイトルメニューステートクラス
	//-----------------------------------

	TitleMenu* TitleMenu::Instance()
	{
		static TitleMenu instance;
		return &instance;
	}

	void TitleMenu::Enter(TitleStage* title)
	{
		title->MenuButtonActive();
		m_menuNum = 1;
	}

	void TitleMenu::Execute(TitleStage* title)
	{
		auto& app = App::GetApp();
		auto keyState = app->GetInputDevice().GetKeyState();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		//if (!cntr.bConnected) return;

		auto scene = app->GetScene<Scene>();
		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();

		float stickX = cntr.fThumbLX;
		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		if (!m_lock)
		{
			if (stickY > threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP || keyState.m_bUpKeyTbl['W'])
			{
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");
				m_menuNum = (m_menuNum == 1) ? 3 : m_menuNum - 1;
				m_lock = true;
			}
			else if (stickY < -threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN || keyState.m_bUpKeyTbl['S'])
			{
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");
				m_menuNum = (m_menuNum % 3) + 1;
				m_lock = true;
			}

			for (int i = 0; i < 3; i++)
				if (auto s = title->m_SpriteVec[i].lock())
				{
					s->SetSelected((i + 1) == m_menuNum);
				}
		}
		else if (std::abs(stickY) < 0.25f)
		{
			m_lock = false;
		}

		if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			//m_se = XAPtr1->Start(L"Confirm", XAUDIO2_NO_LOOP_REGION, 1.0f);
			scene->SEStart(L"Confirm");
			switch (m_menuNum)
			{
			case 1:
				//ゲームスタート
				title->ChangeState(HowToPlayMenu::Instance());
				break;

			case 2:
				//設定
				title->ChangeState(OptionMenu::Instance());
				break;

			case 3:
				//ゲーム終了
				PostQuitMessage(0);
				break;
			}
		}

		if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			//m_se = XAPtr1->Start(L"Cancel", XAUDIO2_NO_LOOP_REGION, 1.0f);
			scene->SEStart(L"Cancel");
			title->ChangeState(EnterTitle::Instance());
		}

		//wstringstream ws;
		//ws << m_menuNum << endl;
		//scene->SetDebugString(ws.str());
	}

	void TitleMenu::Exit(TitleStage* title)
	{
		title->MenuButtonInActive();
	}

	//-----------------------------------
	///設定画面ステートクラス
	//-----------------------------------

	OptionMenu* OptionMenu::Instance()
	{
		static OptionMenu instance;
		return &instance;
	}

	void OptionMenu::Enter(TitleStage* title)
	{
		title->OptionActive();
		m_menuNum = 1;
	}

	void OptionMenu::Execute(TitleStage* title)
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();
		auto scene = app->GetScene<Scene>();

		float v = 0.0f;

		float stickX = cntr.fThumbLX;
		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		float Volume = 0.1f;
		float VolumeMax = 10.0f;

		float SoundBarSpeed = 2.0f;
		float SoundBarMax = 200;

		if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			title->ChangeState(TitleMenu::Instance());
		}

		if (!m_lock)
		{
			if (stickY > threshold || keyState.m_bUpKeyTbl['W'])
			{
				m_menuNum = (m_menuNum == 1) ? 3 : m_menuNum - 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");
			}
			else if (stickY < -threshold || keyState.m_bUpKeyTbl['S'])
			{
				m_menuNum = (m_menuNum % 3) + 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");
			}

			for (int i = 0; i < 3; i++)
				if (auto s = title->m_SpriteVec[i].lock())
				{
					s->SetSelected((i + 1) == m_menuNum);
				}
		}
		else if (std::abs(stickY) < 0.25f || !cntr.bConnected)
		{
			m_lock = false;
		}

		auto delta = app->GetElapsedTime();
		switch (m_menuNum)
		{
		case 1:
			//BGM
			if (stickX > threshold || keyState.m_bPushKeyTbl['D'])
			{
				scene->m_volumeBGMpos += SoundBarSpeed;
				if (scene->m_volumeBGMpos >= SoundBarMax) scene->m_volumeBGMpos = SoundBarMax;

				scene->m_volumeBGM = 1;
				//scene->m_volumeBGM += Volume;
				//if (scene->m_volumeBGM >= VolumeMax)scene->m_volumeBGM = VolumeMax;


			}
			if (stickX < -threshold || keyState.m_bPushKeyTbl['A'])
			{
				scene->m_volumeBGMpos -= SoundBarSpeed;
				if (scene->m_volumeBGMpos <= -SoundBarMax) scene->m_volumeBGMpos = -SoundBarMax;

				scene->m_volumeBGM = 0;
				//scene->m_volumeBGM -= Volume;
				//if (scene->m_volumeBGM <= 0)scene->m_volumeBGM = 0;
			}
			scene->m_volumeBGM = (scene->m_volumeBGMpos + SoundBarMax) / (SoundBarMax * 2);
			scene->ChangeBGMVolume();
			break;

		case 2:
			//SE
			if (stickX > threshold || keyState.m_bPushKeyTbl['D'])
			{
				scene->m_volumeSEpos += SoundBarSpeed;
				if (scene->m_volumeSEpos >= SoundBarMax) scene->m_volumeSEpos = SoundBarMax;
				m_SETime += delta;
			}
			if (stickX < -threshold || keyState.m_bPushKeyTbl['A'])
			{
				scene->m_volumeSEpos -= SoundBarSpeed;
				if (scene->m_volumeSEpos <= -SoundBarMax) scene->m_volumeSEpos = -SoundBarMax;
				m_SETime += delta;
			}
			scene->m_volumeSE = (scene->m_volumeSEpos + SoundBarMax) / (SoundBarMax * 2);
			if (m_SETime > 0.5f)
			{
				scene->SEStart(L"Confirm");
				m_SETime = 0;
			}
			break;

		case 3:
			if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
			{

				//設定画面終了
				title->ChangeState(TitleMenu::Instance());
				break;
			}
		}

	}

	void OptionMenu::Exit(TitleStage* title)
	{
		title->OptionInActive();
	}


//-----------------------------------
///あそびかた画面ステートクラス
//-----------------------------------


	HowToPlayMenu* HowToPlayMenu::Instance()
	{
		static HowToPlayMenu instance;
		return &instance;
	}

	void HowToPlayMenu::Enter(TitleStage* title)
	{
		title->HowToPlayStart();
		m_menuNum = 1;
	}

	void HowToPlayMenu::Execute(TitleStage* title)
	{
		auto& app = App::GetApp();
		auto keyState = app->GetInputDevice().GetKeyState();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		//if (!cntr.bConnected) return;

		auto scene = app->GetScene<Scene>();

		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		switch (m_menuNum)
		{
		case 1:
			if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
			{
				title->HowToPlayActive(false);
				m_menuNum = 2;
				break;
			}
			else if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
			{
				title->ChangeState(TitleMenu::Instance());
				break;
			}
		case 2:
			if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
			{
				title->GameStart();
				break;
			}
			else if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
			{
				title->HowToPlayActive(true);
				m_menuNum = 1;
				break;
			}
		}
	}

	
	void HowToPlayMenu::Exit(TitleStage* title)
	{
		title->HowToPlayInActive();
	}

}