#pragma once
#include "stdafx.h"

namespace basecross
{
	class Option :public GameObject
	{
	private:
		//スプライトのweak_ptr配列
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		std::weak_ptr<Sprite> m_text_BGM;
		std::weak_ptr<Sprite> m_text_SE;
		std::weak_ptr<Sprite> m_button_Back;

		std::weak_ptr<Sprite> m_bar_BGM;
		std::weak_ptr<Sprite> m_bar_SE;
		std::weak_ptr<Sprite> m_bar_BGMNow;
		std::weak_ptr<Sprite> m_bar_SENow;

		std::shared_ptr<SoundItem> m_se;

		bool m_isActive;
		int m_menuNum;
		bool m_lock;

	public:
		Option(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_SpriteVec(5),
			m_isActive(false),
			m_menuNum(1),
			m_lock(false)
		{

		}

		virtual ~Option() {}

		void SetActive(bool active)
		{
			m_isActive = active;
		}

		bool GetActive()
		{
			return m_isActive;
		}

		void CreateMenuSprites();
		//void OptionMenuActive();
		//void OptionMenuInActive();
		void OptionMenuActive(bool active);

		virtual void OnCreate();
		virtual void OnUpdate();
	};
}