#pragma once
#include "stdafx.h"
#include "ButtonSprite.h"
#include "Option.h"
#include "State.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------

	class Clear : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreatePlayerChara();
		void CreateFloor();
		void CreateTitle();
		void CreateAnimeSprite();

		//スプライトの作成
		bool m_CntrolLock;
		int m_SelectStage;

		vector<weak_ptr<GameOverSprite>> m_SpVec;
		//スプライトのweak_ptrの配列
		//選択がチェンジされた
	 public:
		//構築と破棄
		 Clear() :Stage(), m_CntrolLock(false),
	     m_SpVec(1)
		 {
		}
		virtual ~Clear() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

	class ClearChara :public GameObject
	{
		std::shared_ptr<PNTDXModelDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp; // トランスフォームコンポーネント

		enum TCState
		{
			Walk,
			Consent,
		};
		TCState tcState = Walk;

		float m_speed; // 移動の速さ
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rot;

	public:
		//コンストラクタ
		ClearChara(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(1.0f),
			m_pos(0, 0, 0),
			m_scale(0, 0, 0),
			m_rot(0, 0, 0)

		{
		}

		//デストラクタ
		virtual ~ClearChara() {}

		virtual void OnCreate()override;	//初期化
		virtual void OnUpdate()override;	//継続処理

		void InitDrawComp();
		void InitTransComp();
	};

};
