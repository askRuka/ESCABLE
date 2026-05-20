/*!
@file EnemyLaser.cpp
@brief 敵の攻撃実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void EnemyLaser::OnCreate()
	{
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");
		draw->SetDiffuse(Col4(0.7f, 0.0f, 0.0f, 1.0f));
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(m_position);

		HitPositionCalc();
	}

	void EnemyLaser::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		auto stage = GetStage();
		auto pos = m_transComp->GetPosition();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();

		auto nextPos = pos + m_direction * delta * 50.0f;
		Vec3 hit;
		float playerDis;
		float hitDis;
		playerPos.y += 0.5f;
		RayHitCheck::HitTestVirtualSphere(playerPos, pos, nextPos, hit, playerDis, 1.0f, false);
		RayHitCheck::HitTestVirtualSphere(m_hitPosition, pos, nextPos, hit, hitDis, 1.0f, false);
		pos = nextPos;
		m_transComp->SetPosition(pos);

		// オブジェクトの消去処理
		// 消える条件
		bool isOutRange = Vec3(pos - m_position).length() > 80.0f;
		bool isObjHit = hitDis < 1.0f;
		bool isPlayerHit = playerDis < 1.0f;
		if (isPlayerHit)
		{
			stage->AddGameObject<EffectExplosion>(GetThis<GameObject>());
			App::GetApp()->GetScene<Scene>()->SEStart(L"Boom");
			PostEvent(0.0f, GetThis<ObjectInterface>(), player, L"GameOver1");
		}

		if (isOutRange || isObjHit)
		{
			stage->RemoveGameObject<EnemyLaser>(GetThis<EnemyLaser>());
			return;
		}




	}


	void EnemyLaser::HitPositionCalc()
	{
		//カメラの向いている方向と開始地点から判定を確認
		Vec3 startPos = m_position;
		Vec3 endPos = startPos + m_direction * 100;
		Vec3 hitPos; // 当たった時の座標を受け取る用の変数
		vector<Vec3> hitPositions; // 当たった座標を保存しておく配列
		for (auto& v : GetStage()->GetGameObjectVec())
		{
			auto player = dynamic_pointer_cast<Player>(v);
			auto cable = dynamic_pointer_cast<Cable>(v);
			auto enemy = dynamic_pointer_cast<Enemy>(v);
			auto lift = dynamic_pointer_cast<Lift>(v);
			if (player || cable || enemy)
			{
				continue;
			}

			// 当たり判定の確認
			bool isLift = lift == nullptr;
			bool isHit = RayHitCheck::HitTest(v, startPos, endPos, hitPos, isLift);

			//当たっていたら配列に保存
			if (isHit)
			{
				hitPositions.push_back(hitPos);
			}
		}

		//判定がとられた座標から最も開始地点から近い場所をHitPositionにする
		if (hitPositions.size() > 0)
		{
			m_hitPosition = hitPositions[0];
			for (int i = 0; i < hitPositions.size(); i++)
			{
				auto newDis = startPos - hitPositions[i];
				auto nowDis = startPos - m_hitPosition;
				if (newDis.length() < nowDis.length())
				{
					m_hitPosition = hitPositions[i];
				}
			}
		}

	}
}
//end basecross
