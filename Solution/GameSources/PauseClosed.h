#pragma once
#include "stdafx.h"
#include "State.h"

namespace basecross
{
	class Pause;

	class PauseClosed :public State<Pause>
	{
	private:
		PauseClosed() {}

	public:
		static PauseClosed* Instance();
		virtual void Enter(Pause* pause) override;
		virtual void Execute(Pause* pause) override;
		virtual void Exit(Pause* pause) override;
	};
}