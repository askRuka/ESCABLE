#pragma once
#include "stdafx.h"
#include "ButtonSprite.h"
#include "Option.h"
#include "HowToPlay.h"
#include "State.h"
#include "SoundMgr.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		void CreateViewLight(); //ビューの作成
		
	private:
		State<TitleStage>* m_currentState = nullptr;

		std::shared_ptr<Option> m_option;
		std::shared_ptr<HowToPlay> m_howtoplay;

		//std::shared_ptr<XAudio2Manager> m_XAMgr;
		std::shared_ptr<SoundMgr> m_SoundMgr;
		shared_ptr<SoundItem> m_BGM;

		std::weak_ptr<Sprite> m_button_PushA;

		std::weak_ptr<Sprite> m_button_Start;
		std::weak_ptr<Sprite> m_button_Option;
		std::weak_ptr<Sprite> m_button_End;

		enum Button
		{
			Confirm = XINPUT_GAMEPAD_A,	//決定
			Cancel = XINPUT_GAMEPAD_B	//キャンセル
		};
		Button m_button;

		Col4 buttonColor = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		
	public:
		std::vector<std::weak_ptr<Sprite>> m_SpriteVec;

		//コンストラクタ
		TitleStage() :Stage(),
			m_SpriteVec(4),
			m_button(Confirm)
		{
		}

		//デストラクタ
		virtual ~TitleStage() {}

		virtual void OnCreate()override;	//初期化
		virtual void OnUpdate()override;	//継続処理

		void StopBGM();

		void CreateMenuButton();
		void CreatePlayerChara();

		void TitleActive();
		void TitleInActive();

		void MenuButtonActive();
		void MenuButtonInActive();

		void OptionActive();
		void OptionInActive();

		void HowToPlayStart();
		void HowToPlayActive(bool active);
		void HowToPlayInActive();

		void GameStart();

		void ChangeState(State<TitleStage>* newState);	//ステート変更

		virtual void OnDestroy()override;
	};

	
	class TitleChara :public GameObject
	{
		std::shared_ptr<PNTBoneModelDraw> m_drawComp; 
		std::shared_ptr<Transform> m_transComp; // トランスフォームコンポーネント

		enum TCState
		{
			Walk,
			Consent,
		};
		TCState tcState = Walk;

		float m_speed; // 移動の速さ
		Vec3 m_pos;
	public:
		//コンストラクタ
		TitleChara(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(1.0f),
			m_pos(0, 0, 0)
		{
		}

		//デストラクタ
		virtual ~TitleChara() {}

		virtual void OnCreate()override;	//初期化
		virtual void OnUpdate()override;	//継続処理

		void InitDrawComp();
		void InitTransComp();
	};
}
