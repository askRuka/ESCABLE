#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	PauseClosed* PauseClosed::Instance()
	{
		static PauseClosed instance;
		return &instance;
	}

	void PauseClosed::Enter(Pause* pause)
	{
		pause->CloseMenuBS();
		pause->ClosePause();
		pause->CloseMenu();
	}

	void PauseClosed::Execute(Pause* pause)
	{
		auto& app = App::GetApp();
		auto cntr = app->GetInputDevice().GetControlerVec()[0];
		auto keyState = app->GetInputDevice().GetKeyState();
		//if (!cntr.bConnected) return;

		if (cntr.wPressedButtons & XINPUT_GAMEPAD_START || keyState.m_bUpKeyTbl[VK_SPACE])
		{
			pause->ChangeState(PauseMenu::Instance());
		}
	}

	void PauseClosed::Exit(Pause* pause)
	{

	}
}