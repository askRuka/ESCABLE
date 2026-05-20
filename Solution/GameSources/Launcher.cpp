/*!
@file ElectricTrigger.cpp
@brief 帯電状態で触れると反応する装置など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Luncher::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 span; // モデルとトランスフォームの間の差分行列
		span.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)

		);


		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_LAUNCHER");
		ptrDraw->SetMeshToTransformMatrix(span);


	}

	void Luncher::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();

		m_TotalTime += elapsedTime;

		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto launcherTrans = GetComponent<Transform>(); // 大砲のトランスフォームコンポーネント
		Vec3 launcherPos = launcherTrans->GetPosition(); // 大砲の座標
		Vec3 launcherScale = launcherTrans->GetScale(); // 大砲のサイズ
		Vec3 plPos = player->GetComponent<Transform>()->GetPosition(); // プレイヤーの座標
		Vec3 plScale = player->GetComponent<Transform>()->GetScale(); // プレイヤーのサイズ
		Vec3 distance = plPos - launcherPos; // 大砲とプレイヤーの距離
		Vec3 scaleSum = (launcherScale + plScale) * 30.0f; // 大砲とプレイヤーのサイズの合計（密着した時のx,y,zの距離）
		auto delta = App::GetApp()->GetElapsedTime();
		//auto ptrXA = App::GetApp()->GetXAudio2Manager();

		if (m_TotalTime >= m_Fire + m_Delay)
		{

			if (abs(distance.x) < scaleSum.x + 2 && abs(distance.z) < scaleSum.z + 2)
			{
				//床の上におり、次フレームに範囲内に接触、埋まるとき
				if (distance.y + 2 >= 0 && distance.y + delta <= scaleSum.y + 2)
				{
					//発射音を鳴らす
					//ptrXA->Start(L"ARRIVE", XAUDIO2_NO_LOOP_REGION, 2.0f);
					App::GetApp()->GetScene<Scene>()->SEStart(L"ARRIVE");
				}
			}

			GetStage()->AddGameObject<Laser>(
				m_Scale,
				m_Rotation,
				m_Position,
				m_Velocity,
				m_Fire,
				m_Fade,
				m_Delay);

			m_TotalTime = 0.0f;
		}

	}

}
//end basecross
