#pragma once
#include "stdafx.h"
#include "State.h"

namespace basecross
{
	class LaserOnState :public ObjState<Cannon>
	{
		LaserOnState() {}
	public:
		static shared_ptr<LaserOnState> Instance();
		virtual void Enter(const shared_ptr<Cannon>& laser) override;
		virtual void Execute(const shared_ptr<Cannon>& laser) override;
		virtual void Exit(const shared_ptr<Cannon>& laser) override;
	};

	class LaserOffState :public ObjState<Cannon>
	{
		LaserOffState() {}
	public:
		static shared_ptr<LaserOffState> Instance();
		virtual void Enter(const shared_ptr<Cannon>& laser) override;
		virtual void Execute(const shared_ptr<Cannon>& laser) override;
		virtual void Exit(const shared_ptr<Cannon>& laser) override;
	};
}