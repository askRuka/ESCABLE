#pragma once
#include "stdafx.h"
#include "State.h"

namespace basecross
{
	class TitleStage;

	class EnterTitle :public State<TitleStage>
	{
	private:
		std::shared_ptr<SoundItem> m_se;

		EnterTitle(){}

	public:
		static EnterTitle* Instance();
		virtual void Enter(TitleStage* title) override;
		virtual void Execute(TitleStage* title) override;
		virtual void Exit(TitleStage* title) override;
	};
}