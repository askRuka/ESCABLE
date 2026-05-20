#pragma once
#include "stdafx.h"
#include "State.h"

namespace basecross
{
	class Pause;

	class PauseMenu :public State<Pause>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;
		std::shared_ptr<SoundItem> m_stageBGM;
		std::shared_ptr<SoundItem> m_se;

		enum Menu
		{
			Restart,
			Option,
			HowtoPlay,
			Escape
		};
		Menu m_pause;
		int m_menuNum;
		bool m_lock;

		PauseMenu() :State(),
			m_SpriteVec(4),
			m_pause(Restart),
			m_menuNum(1),
			m_lock(false) 
		{
		}

	public:
		static PauseMenu* Instance();
		virtual void Enter(Pause* pause) override;
		virtual void Execute(Pause* pause) override;
		virtual void Exit(Pause* pause) override;
	};

	class PauseMenuOption :public State<Pause>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		int m_menuNum;
		float m_SETime;
		bool m_lock;
		std::shared_ptr<SoundItem> m_se;


		PauseMenuOption() :State(),
			m_SpriteVec(5),
			m_menuNum(1),
			m_lock(false)
		{
		}


	public:
		static PauseMenuOption* Instance();
		virtual void Enter(Pause* pause) override;
		virtual void Execute(Pause* pause) override;
		virtual void Exit(Pause* pause) override;
	};

	class PauseMenuHowToPlay :public State<Pause>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		int m_menuNum;
		bool m_lock;

		PauseMenuHowToPlay() :State(),
			m_SpriteVec(5),
			m_menuNum(1),
			m_lock(false)
		{
		}


	public:
		static PauseMenuHowToPlay* Instance();
		virtual void Enter(Pause* pause) override;
		virtual void Execute(Pause* pause) override;
		virtual void Exit(Pause* pause) override;
	};


}