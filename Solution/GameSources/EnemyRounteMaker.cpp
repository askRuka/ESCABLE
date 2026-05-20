/*!
@file EnemyRouteMaker.cpp
@brief 第2ステージ用のエネミーの経路を指定するエディター用オブジェクト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void EnemyRouteMaker::OnCreate()
	{
		// ターゲットのポインターのロックとキャスト
		if (m_target.expired()) return;
		auto target = m_target.lock();
		if (!target) return;
		auto enemy = dynamic_pointer_cast<Enemy2>(target);
		if (!enemy) return;

		// 親となるオブジェクトの存在の確認
		bool parentExist = true;
		if (m_parent.expired()) parentExist = false;
		// もし存在する場合に保存するためのポインタ
		shared_ptr<GameObject> parent = nullptr;
		shared_ptr<EnemyRouteMaker> parentMark = nullptr;
		// 存在したら親オブジェクトのロック
		if (parentExist)
		{
			parent = m_parent.lock();
			if (!parent) parentExist = false;
		}
		// 存在したら親オブジェクトのキャスト
		if (parentExist)
		{
			parentMark = dynamic_pointer_cast<EnemyRouteMaker>(parent);
			if (!parentMark) parentExist = false;
		}
		// 親オブジェクトが存在したらする処理
		if (parentExist)
		{
			int num = parentMark->GetNum();
			m_num = num + 1;
		}
		else // 親オブジェクトがいない、このオブジェクトがルートの初めであるとき
		{
			m_num = 0;
		}

		// 子オブジェクトの生成
		if (m_num >= 0 && enemy->GetMovePositionsNum() > m_num)
		{
			GetStage()->AddGameObject<EnemyRouteMaker>(enemy, GetThis<EnemyRouteMaker>());
		}

		// 見た目の設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		// 座標の設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(enemy->GetMovePosition(m_num));
	}

	void EnemyRouteMaker::OnUpdate()
	{

	}

	void EnemyRouteMaker::SetRoutePosition(const Vec3& pos, const Vec3& rot)
	{
		// ターゲットのポインターのロックとキャスト
		if (m_target.expired()) return;
		auto target = m_target.lock();
		if (!target) return;
		auto enemy = dynamic_pointer_cast<Enemy2>(target);
		if (!enemy) return;

		enemy->SetMovePosition(m_num, pos);
	}
}
//end basecross
