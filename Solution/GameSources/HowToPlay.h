#pragma once
#include "stdafx.h"

namespace basecross
{
	class HowToPlay :public GameObject
	{
	private:
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		std::weak_ptr<Sprite> m_HtP1;
		std::weak_ptr<Sprite> m_HtP2;

		bool m_isActive;
		int m_menuNum;
		bool m_lock;

	public:
		HowToPlay(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_SpriteVec(2),
			m_isActive(false),
			m_menuNum(1),
			m_lock(false)
		{

		}

		virtual ~HowToPlay() {}

		void SetActive(bool active)
		{
			m_isActive = active;
		}

		bool GetActive()
		{
			return m_isActive;
		}

		void CreateSprites();
		void HowToPlayMenuActive(bool active);
		void HowToPlayInMenuActive();

		virtual void OnCreate();
		virtual void OnUpdate();
	};
}