#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	PauseMenu* PauseMenu::Instance()
	{
		static PauseMenu instance;
		return &instance;
	}

	void PauseMenu::Enter(Pause* pause)
	{
		pause->OpenMenuBS();	//背景
		pause->OpenPause();		//停止
		pause->OpenMenu();		//メニュー画面

		m_menuNum = 1;
	}

	void PauseMenu::Execute(Pause* pause)
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();
		auto scene = app->GetScene<Scene>();

		float stickX = cntr.fThumbLX;
		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		// スタートボタンでポーズを終了する
		//if (!cntr.bConnected) return;
		if (cntr.wPressedButtons & XINPUT_GAMEPAD_START ||
			cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			pause->ChangeState(PauseClosed::Instance());
		}

		// Lスティックでメニューを選択
		if (!m_lock)
		{
			if (stickY > threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP || keyState.m_bUpKeyTbl['W'])
			{
				m_menuNum = (m_menuNum == 1) ? 4 : m_menuNum - 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");
			}
			else if (stickY < -threshold || cntr.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN || keyState.m_bUpKeyTbl['S'])
			{
				m_menuNum = (m_menuNum % 4) + 1;
				m_lock = true;
				//m_se = XAPtr1->Start(L"Select", XAUDIO2_NO_LOOP_REGION, 1.0f);
				scene->SEStart(L"Select");

			}

			for (int i = 0; i < 4; i++)
				if (auto s = pause->m_SpriteVec[i].lock())
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
				//ツヅケル
				pause->ChangeState(PauseClosed::Instance());
				break;

			case 2:
				//セッテイ
				pause->ChangeState(PauseMenuOption::Instance());
				break;

			case 3:
				//アソビカタ
				pause->ChangeState(PauseMenuHowToPlay::Instance());
				break;

			case 4:
				pause->StopBGM();
				pause->TitleBack();
				break;
			}
		}


	}
	void PauseMenu::Exit(Pause* pause)
	{
		pause->ClosePause();
	}

	//-----------------------------------
	///設定画面ステートクラス
	//-----------------------------------


	PauseMenuOption* PauseMenuOption::Instance()
	{
		static PauseMenuOption instance;
		return &instance;
	}

	void PauseMenuOption::Enter(Pause* pause)
	{
		pause->OptionActive();
		pause->OpenPause();
		pause->CloseMenu();
		m_menuNum = 1;
	}

	void PauseMenuOption::Execute(Pause* pause)
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();

		auto scene = app->GetScene<Scene>();

		float stickX = cntr.fThumbLX;
		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		float SoundBarSpeed = 3.0f;
		float SoundBarMax = 200;

		// スタートボタンでポーズを終了する
		//if (!cntr.bConnected) return;
		if (cntr.wPressedButtons & XINPUT_GAMEPAD_START || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			pause->ChangeState(PauseClosed::Instance());
		}
		// Bボタンでポーズ画面に戻る
		if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			pause->ChangeState(PauseMenu::Instance());
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
				if (auto s = pause->m_SpriteVec[i].lock())
				{
					s->SetSelected((i + 1) == m_menuNum);
				}
		}
		else if (std::abs(stickY) < 0.25f)
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
			}
			if (stickX < -threshold || keyState.m_bPushKeyTbl['A'])
			{
				scene->m_volumeBGMpos -= SoundBarSpeed;
				if (scene->m_volumeBGMpos <= -SoundBarMax) scene->m_volumeBGMpos = -SoundBarMax;
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
				pause->ChangeState(PauseMenu::Instance());
				break;
			}
		}

		wstringstream ws;
		ws << m_menuNum << endl;
		scene->SetDebugString(ws.str());
	}

	void PauseMenuOption::Exit(Pause* pause)
	{
		pause->OptionInActive();
	}

	//-----------------------------------
	///あそびかた画面ステートクラス
	//-----------------------------------


	PauseMenuHowToPlay* PauseMenuHowToPlay::Instance()
	{
		static PauseMenuHowToPlay instance;
		return &instance;
	}

	void PauseMenuHowToPlay::Enter(Pause* pause)
	{
		pause->HowToPlayStart();
		pause->OpenPause();
		pause->CloseMenu();
		m_menuNum = 1;
	}

	void PauseMenuHowToPlay::Execute(Pause* pause)
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		auto scene = app->GetScene<Scene>();

		float stickY = cntr.fThumbLY;
		float threshold = 0.25f;

		// スタートボタンでポーズを終了する
		//if (!cntr.bConnected) return;
		if (cntr.wPressedButtons & XINPUT_GAMEPAD_START || keyState.m_bUpKeyTbl[VK_SPACE])
		{
			pause->ChangeState(PauseClosed::Instance());
		}

		switch (m_menuNum)
		{
		case 1:
			if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
			{
				pause->HowToPlayActive(false);
				m_menuNum = 2;
				break;
			}
			else if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
			{
				pause->ChangeState(PauseMenu::Instance());
				break;
			}
		case 2:
			if (cntr.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
			{
				pause->ChangeState(PauseMenu::Instance());
				break;
			}
			else if (cntr.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
			{
				pause->HowToPlayActive(true);
				m_menuNum = 1;
				break;
			}
		}
	}


	void PauseMenuHowToPlay::Exit(Pause* pause)
	{
		pause->HowToPlayInActive();
	}


}