#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//レーザーオンステート
	shared_ptr<LaserOnState> LaserOnState::Instance()
	{
		static shared_ptr<LaserOnState> instance(new LaserOnState);
		return instance;
	}

	void LaserOnState::Enter(const shared_ptr<Cannon>& laser)
	{
		laser->SetTime(0);
		laser->SetLaserActive(true);
	}

	void LaserOnState::Execute(const shared_ptr<Cannon>& laser)
	{
		int second = 4;
		if (laser->m_time >= second)
		{
			laser->LaserOff();
		}
		else
		{
			laser->ActiveTimer();
		}
	}

	void LaserOnState::Exit(const shared_ptr<Cannon>& laser)
	{

	}

	//レーザーオフステート
	shared_ptr<LaserOffState> LaserOffState::Instance()
	{
		static shared_ptr<LaserOffState> instance(new LaserOffState);
		return instance;
	}

	void LaserOffState::Enter(const shared_ptr<Cannon>& laser)
	{
		laser->SetTime(0);
		laser->SetLaserActive(false);
	}

	void LaserOffState::Execute(const shared_ptr<Cannon>& laser)
	{
		int second = 4;
		if (laser->m_time >= second)
		{
			laser->LaserOn();
		}
		else
		{
			laser->ActiveTimer();
		}
	}

	void LaserOffState::Exit(const shared_ptr<Cannon>& laser)
	{

	}
}