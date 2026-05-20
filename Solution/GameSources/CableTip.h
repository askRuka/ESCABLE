/*!
@file CableTip.h
@brief 第2ステージ用のエネミーの経路を指定するエディター用オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class CableTip : public GameObject;
	//--------------------------------------------------------------------------------------
	class CableTip : public GameObject
	{
		std::shared_ptr<Transform> m_transComp;
		Vec3 m_behind;
		float m_length = 1.0f;
	public:
		// 構築と破棄
		CableTip(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_behind(Vec3(0.0f, 0.0f, 1.0f))
		{
		}
		virtual ~CableTip()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

		void SetTipRotation(const Vec3& rot);
		void SetTipPosition(const Vec3& pos);

		Vec3 GetTipBehind() { return m_behind; }
	};

}
//end basecross
