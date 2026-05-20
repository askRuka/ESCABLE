/*!
@file ElectricTrigger.cpp
@brief 帯電状態で触れると反応する装置など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Laser::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(1.0f,1.0f,1.0f);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 span; // モデルとトランスフォームの間の差分行列
		span.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)

		);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_LASER");
		ptrDraw->SetMeshToTransformMatrix(span);

	}

	void Laser::OnUpdate()
	{
		HitCheck();
		Push();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");

	}
	void Laser::HitCheck()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		player->SetStatusFlag(PlayerStatus::isGround, false);
		//ステージからオブジェクトの配列を取得
		auto& objs = GetStage()->GetGameObjectVec();
		for (const auto obj : objs)
		{
			auto player = dynamic_pointer_cast<Player>(obj);
			auto wall = dynamic_pointer_cast<Wall>(obj);
			if (player)
			{
				PlayerHitCheck(player);
			}


		}

	}

	void Laser::PlayerHitCheck(const shared_ptr<GameObject>& player)
	{
		auto& app = App::GetApp();
		auto stage = GetStage();
		auto scene = app->GetScene<Scene>();

		//auto ptrXA = app->GetXAudio2Manager();

		auto p = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto laserTrans = GetComponent<Transform>(); // 床のトランスフォームコンポーネント
		Vec3 laserPos = laserTrans->GetPosition(); // 床の座標
		//Vec3 laserScale = laserTrans->GetScale(); // 床のサイズ
		Vec3 pos = player->GetComponent<Transform>()->GetPosition(); // プレイヤーの座標
		//Vec3 scale = player->GetComponent<Transform>()->GetScale(); // プレイヤーのスケール
		//Vec3 distance = pos - laserPos; // 床とプレイヤーの距離
		//Vec3 scaleSum = (laserScale + scale) / 2.0f; // 床とプレイヤーのサイズの合計（密着した時のx,y,zの距離）
		//auto delta = App::GetApp()->GetElapsedTime();

		////x座標とz座標の距離がサイズの合計より小さい、つまり床の上か下にいるとき
		//if (abs(distance.x) < scaleSum.x+2 && abs(distance.z) < scaleSum.z+2)
		//{
		//	//床の上におり、次フレームに床に接触、埋まるとき
		//	if (distance.y+2 >= 0 && distance.y +  delta <= scaleSum.y+2)
		//	{
		//		auto gameObjects = stage->GetGameObjectVec();
		//		m_time = 0.0f;

		//		auto delta = app->GetElapsedTime();
		//		//m_effect = stage->AddGameObject<EffectExplosion>(p);
		//		for (auto& gameObject : gameObjects)
		//		{
		//			auto stage = GetStage();
					//auto gameObjects = stage->GetGameObjectVec();
					//for (auto& gameObject : gameObjects)
					//{
					//	if (dynamic_pointer_cast<Pause>(gameObject))
					//	{
					//		continue;
					//		m_effect = stage->AddGameObject<EffectExplosion>(GetThis<Laser>());
					//		//ptrXA->Start(L"ATTACK", XAUDIO2_NO_LOOP_REGION, 0.10f);
					//	}
					//	gameObject->SetUpdateActive(false);
					//}
		//			if (m_time >= 0.05f)
					//{
		if (Vec3(laserPos - pos).length() < 2.0f)
		{
			auto gameObjects = stage->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				if (dynamic_pointer_cast<Pause>(gameObject))
				{
					m_effect = stage->AddGameObject<EffectExplosion>(GetThis<Laser>());
					continue;
					//ptrXA->Start(L"ATTACK", XAUDIO2_NO_LOOP_REGION, 0.10f);
				}
				SetDrawActive(false);
				gameObject->SetUpdateActive(false);
			}
			scene->SEStart(L"Boom");
			PostEvent(0.0f, GetThis<ObjectInterface>(), p, L"GameOver1");
			//auto gameObjects = stage->GetGameObjectVec();
			//for (auto& gameObject : gameObjects)
			//{
			//	if (dynamic_pointer_cast<Pause>(gameObject))
			//	{
			//		continue;
			//		m_effect = stage->AddGameObject<EffectExplosion>(GetThis<Laser>());
			//		//ptrXA->Start(L"ATTACK", XAUDIO2_NO_LOOP_REGION, 0.10f);
			//	}
			//	gameObject->SetUpdateActive(false);
			//}

			////auto soundMgr = stage->GetSharedGameObject<SoundMgr>(L"SoundMgr");
			////soundMgr->StopStageBGM();
			//App::GetApp()->GetScene<Scene>()->BGMStop();

			//PostEvent(0.5f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
			//p->SetStatusFlag(PlayerStatus::isGround, true);
			//p->OnDestory1();
		}
					//}
					//else
					//{
					//	m_time += delta;
					//}
				//}

				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//ptrXA->Start(L"ATTACK");
				//y方向の移動量を０にし、座標を調整、m_statusFlagを地上にいる状態にする
			//}
		//}
	}


	void Laser::Push()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto targetPtr = GetComponent<Transform>()->GetPosition();
		m_TotalTime += elapsedTime;

		if (m_TotalTime >= m_Fire+m_Delay)
		{
			auto Velocity = m_Velocity;
			targetPtr += elapsedTime * Velocity.normalize() * 30.0f;//15.0f; 
			GetComponent<Transform>()->SetPosition(targetPtr);

			// m_TotalTime = 0.0f;
		}
		if (m_TotalTime >= m_Fade)
		{

			//m_TotalTime = 0.0f;
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());


		}


	}

}
//end basecross
