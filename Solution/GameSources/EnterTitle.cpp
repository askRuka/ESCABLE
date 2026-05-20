#include "stdafx.h"
#include "Project.h"
#include "EnterTitle.h"

namespace basecross
{
	EnterTitle* EnterTitle::Instance()
	{
		static EnterTitle instance;
		return &instance;
	}

	void EnterTitle::Enter(TitleStage* title)
	{
		title->TitleActive();
	}

	void EnterTitle::Execute(TitleStage* title)
	{
		auto& app = App::GetApp();
		auto keyState = app->GetInputDevice().GetKeyState();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();

		//if (!cntr.bConnected) return;

		auto scene = app->GetScene<Scene>();

		if ((cntr.wPressedButtons & XINPUT_GAMEPAD_A )|| keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			//m_se = XAPtr1->Start(L"Confirm", XAUDIO2_NO_LOOP_REGION, 1.0f);
			scene->SEStart(L"Confirm");
			title->ChangeState(TitleMenu::Instance());
		}
	}

	void EnterTitle::Exit(TitleStage* title)
	{
		title->TitleInActive();
	}
}