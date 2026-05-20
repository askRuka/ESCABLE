/*!
@file EnemyRouteMaker.h
@brief 第2ステージ用のエネミーの経路を指定するエディター用オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class EnemyRouteMaker : public GameObjectForEdit;
	//--------------------------------------------------------------------------------------
	class EnemyRouteMaker : public GameObjectForEdit
	{
		std::weak_ptr<GameObject> m_parent;
		std::weak_ptr<GameObject> m_target;
		int m_num;
		std::shared_ptr<Transform> m_transComp;
	public:
		// 構築と破棄
		EnemyRouteMaker(const shared_ptr<Stage>& stage, const shared_ptr<GameObject>& target, const shared_ptr<GameObject>& parent) :
			GameObjectForEdit(stage),
			m_target(target),
			m_parent(parent),
			m_num(-1)
		{
		}
		virtual ~EnemyRouteMaker()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		//void SetTargetObject(const shared_ptr<GameObject>& obj)
		//{
		//	m_target = obj;
		//}
		//void SetParentObject(const shared_ptr<GameObject>& obj)
		//{
		//	m_parent = obj;
		//}
		void SetRoutePosition(const Vec3& pos, const Vec3& rot);
		int GetNum() { return m_num; }
	};

}
//end basecross
