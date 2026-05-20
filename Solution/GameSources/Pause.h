#pragma once
#include "stdafx.h"
#include "State.h"
#include "Player.h"
#include "Option.h"
#include "HowToPlay.h"
#include "SoundMgr.h"

namespace basecross
{
	class Stage;
	class HowToPlay;

	class Pause : public GameObject
	{
	private:
		State<Pause>* m_currentState = nullptr;

		std::weak_ptr<Sprite> m_backscreen;
		std::weak_ptr<Sprite> m_titlelogo;
		std::weak_ptr<Sprite> m_button_Restart;
		std::weak_ptr<Sprite> m_button_Option;
		std::weak_ptr<Sprite> m_button_HtP;
		std::weak_ptr<Sprite> m_button_Title;

		std::shared_ptr<Player> m_player;
		std::shared_ptr<Camera> m_camera;
		std::shared_ptr<Consent> m_consent;

		std::shared_ptr<Option> m_option;
		std::shared_ptr<HowToPlay> m_howtoplay;

		Col4 baseColor = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		std::weak_ptr<Sprite> m_guide;

		Col4 guideColor = Col4(1.0f, 1.0f, 1.0f, 0.45f);

	public:
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		Pause(const shared_ptr<Stage>& stage):
			GameObject(stage)
		{
		}

		virtual ~Pause() 
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void OpenPause();
		void ClosePause();

		void OpenMenuBS();
		void OpenMenu();
		void CloseMenuBS();
		void CloseMenu();

		void OptionActive();
		void OptionInActive();

		void HowToPlayStart();
		void HowToPlayActive(bool active);
		void HowToPlayInActive();

		void ChangeState(State<Pause>* newState);	//ステート変更
		void TitleBack();

		void StopBGM();
	};
}