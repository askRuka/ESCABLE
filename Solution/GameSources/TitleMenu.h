#pragma once
#include "stdafx.h"
#include "State.h"

namespace basecross
{
	class TitleStage;

	class TitleMenu :public State<TitleStage>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;
		std::shared_ptr<SoundItem> m_BGM;
		std::shared_ptr<SoundItem> m_se;

		enum Menu
		{
			Start,
			Option,
			StaffRoll,
			Escape
		};
		Menu m_menu;
		int m_menuNum;
		bool m_lock;
	

		TitleMenu() :State(),
			m_SpriteVec(5),
			m_BGM(0),
			m_menu(Start),
			m_menuNum(1),
			m_lock(false)
		{
		}


	public:
		static TitleMenu* Instance();
		virtual void Enter(TitleStage* title) override;
		virtual void Execute(TitleStage* title) override;
		virtual void Exit(TitleStage* title) override;
	};


	//オプションクラス
	class OptionMenu :public State<TitleStage>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		int m_menuNum;
		bool m_lock;

		std::shared_ptr<SoundItem> m_se;
		float m_SETime;

		OptionMenu() :State(),
			m_SpriteVec(5),
			m_menuNum(1),
			m_lock(false)
		{
		}


	public:
		static OptionMenu* Instance();
		virtual void Enter(TitleStage* title) override;
		virtual void Execute(TitleStage* title) override;
		virtual void Exit(TitleStage* title) override;
	};

	//操作説明クラス
	class HowToPlayMenu :public State<TitleStage>
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		int m_menuNum;
		bool m_lock;

		HowToPlayMenu() :State(),
			m_SpriteVec(5),
			m_menuNum(1),
			m_lock(false)
		{
		}


	public:
		static HowToPlayMenu* Instance();
		virtual void Enter(TitleStage* title) override;
		virtual void Execute(TitleStage* title) override;
		virtual void Exit(TitleStage* title) override;
	};

}