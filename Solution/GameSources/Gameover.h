#pragma once
#include "stdafx.h"
#include "SoundMgr.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class GameOverSprite;

	class GameOver : public Stage {
		std::shared_ptr<SoundMgr> m_SoundMgr;

		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateAnimeSprite();
		bool m_CntrolLock;
		int m_SelectStage;

		//スプライトのweak_ptrの配列
		vector<weak_ptr<GameOverSprite>> m_SpVec;
		//選択がチェンジされた
		void ChangeSelect(int num);
	public:
		//構築と破棄
		GameOver() :Stage(), m_CntrolLock(false),
			m_SpVec(3)
		{
		}
		virtual ~GameOver() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

};
