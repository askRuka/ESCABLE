/*!
@file SelectScene.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectScene : public Stage {
		void CreateViewLight(); //ビューの作成
		float m_pastPadX;
		float m_pastPadY;
		shared_ptr<GameObject> m_curtain;
		bool m_isStart;
		vector<shared_ptr<GameObject>> m_buttons;
		int m_conNum;
		bool m_con[5];
	public:
		//構築と破棄
		SelectScene() :
			Stage(),
			m_pastPadX(0),
			m_pastPadY(0),
			m_isStart(false),
			m_conNum(0)
		{}
		virtual ~SelectScene() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate() override; // 更新
		virtual void OnDestroy() override; // 消去時の処理

		void AddButton(const Vec3& pos, const Vec3& scale, const Col4& col, int num);
		void CreateButtons();
		void ButtonSelect(int num);
		void CreateBlackoutCurtain();

		void UpdateNum(bool b);
	};

}
//end basecross

