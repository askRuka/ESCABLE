/*!
@file Enemy.cpp
@brief エネミー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Enemy::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetMultiMeshResource(L"MODEL_ENEMY");

	}

    void Enemy::OnUpdate()
    {
		LiftVecSetting();
		auto camera = GetStage()->GetView()->GetTargetCamera();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");

		if (m_isDead)
		{
			auto hight = LiftCollision();
			if (hight > 1.0f)
			{
				GetStage()->AddGameObject<Enemy2>(m_Scale, m_Rotation, m_Position);
				GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());

			}
			player->SetIsControl(true);
			PostEvent(0.0f, GetThis<ObjectInterface>(), camera, L"TargetPlayer");
			return;
		}

		auto hight = LiftCollision();
		if (hight < 1.0f)
		{
			GetComponent<Transform>()->SetScale(Vec3(1.0f, hight, 1.0f));
			if (hight < 0.1f)
			{
				m_isDead = true;
				SetDrawActive(false);
			}
			// 敵がつぶされそうなときにカメラにイベントを送りステートを変更する
			// イベントを使った理由はEnemyのオブジェクトを送るため
			m_isStay = true;
			player->SetIsControl(false);
			PostEvent(0.0f, GetThis<ObjectInterface>(), camera, L"TargetEnemy");
		}
		else
		{
			hight = 1.0f;
			m_isStay = false;
			player->SetIsControl(true);
			PostEvent(0.0f, GetThis<ObjectInterface>(), camera, L"TargetPlayer");

		}

		if (!m_isStay)
		{
			auto dis = TargetPlayer(player);
			auto delta = App::GetApp()->GetElapsedTime();
			auto pos = GetComponent<Transform>()->GetPosition();
			//GetStage()->GetSharedGameObject<DebugStrMng>(L"DebugStrMng")->AddDebugString(to_wstring(dis.length()));
			if (dis.length() < 40)
			{
				m_shotTime += delta;
				if (m_shotTime >= 2.0f)
				{
					m_shotTime = 0.0f;
					Vec3 eyePos = m_eyePosition;
					eyePos.y *= hight;
					pos += eyePos;
					GetStage()->AddGameObject<EnemyLaser>(pos, dis.normalize() * 2);
				}
			}
		}

	}

	Vec3 Enemy::TargetPlayer(const shared_ptr<GameObject>& player)
	{
		auto playerTrans = player->GetComponent<Transform>();
		auto transComp = GetComponent<Transform>();
		Vec3 playerPos = playerTrans->GetPosition();
		Vec3 pos = transComp->GetPosition();
		pos += m_eyePosition;

		Vec3 dis = playerPos - pos;
		float rotY = atan2f(-dis.z, dis.x);
		m_eyePosition.x = cosf(rotY) * m_eyeDis;
		m_eyePosition.z = -sinf(rotY) * m_eyeDis;
		rotY -= XM_PIDIV2;
		transComp->SetRotation(Vec3(0.0f, rotY, 0.0f));
		return dis;
	}


	void Enemy::LiftVecSetting()
	{
		if (m_liftVec.size() > 0)return;

		auto objs = GetStage()->GetGameObjectVec();
		for (auto& obj : objs)
		{
			auto lift = dynamic_pointer_cast<Lift>(obj);
			if (lift)
			{
				m_liftVec.push_back(lift);
			}
		}
	}
	float Enemy::LiftCollision()
	{
		float hight = 1.0f;
		for (auto& liftptr : m_liftVec)
		{
			if (liftptr.expired())return hight;
			auto lift = liftptr.lock();
			if (!lift) return hight;

			//リフトの判定
			auto liftTrans = lift->GetComponent<Transform>();
			Vec3 liftPos = liftTrans->GetPosition(); //リフトの位置
			Vec3 liftScale = liftTrans->GetScale() * 8.0f; // リフトの大きさ
			liftScale.y /= 40.0f;
			auto transComp = GetComponent<Transform>();
			Vec3 pos = transComp->GetPosition(); // エネミーの位置
			Vec3 scale = transComp->GetScale(); //エネミーの大きさ
			Vec3 distance = pos - liftPos; // リフトとエネミーの距離
			Vec3 scaleSum = (liftScale + scale) / 2.0f; // 大きさの合計
			auto delta = App::GetApp()->GetElapsedTime();
			//x座標とz座標の距離がサイズの合計より小さい、つまりリフトの上か下にいるとき
			if (abs(distance.x) < scaleSum.x && abs(distance.z) < scaleSum.z)
			{
				hight = liftPos.y / m_baseHight;
			}
		}
		return hight;
	}

}
//end basecross
