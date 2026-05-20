/*!
@file Checkpoint.cpp
@brief チェックポイントなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void ClearObject::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetRotation(m_rotation);
		transComp->SetScale(m_scale);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		SetDrawActive(false);

		auto respawnArea = GetStage()->AddGameObject<Aura>(Aura::InitParams(L"line", 30, 2.0f, 1.0f, 1.0f, Col4(1.0f, 2.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 2.0f), 4.0f));
		respawnArea->GetComponent<Transform>()->SetPosition(m_position);

		auto light = GetStage()->AddGameObject<Aura>(Aura::InitParams(L"", 30, 0.0f, 0.0f, 2.0f, Col4(1.0f, 1.0f, 1.0f, 1.0f), Col4(0.2f, 0.2f, 0.2f, 0.0f), Vec2(0.0f)));
		light->GetComponent<Transform>()->SetPosition(m_position);

	}

	////更新
	//void ClearObject::OnUpdate()
	//{
	//	auto player = GetStage()->GetSharedGameObject<Player>(L"Player");

	//	if (player)
	//	{
	//		auto playerPos = player->GetComponent<Transform>()->GetPosition();
	//		auto playerRot = player->GetComponent<Transform>()->GetRotation();
	//		auto playerPo = player->GetComponent<Transform>();
	//		auto pos = GetComponent<Transform>()->GetPosition();
	//		auto po = GetComponent<Transform>();
	//		auto distance = Vec3(playerPos - pos);
	//		auto scale = GetComponent<Transform>()->GetScale();
	//		bool isCheck = abs(distance.x) < scale.x && abs(distance.y) < scale.y && abs(distance.z) < scale.z;
	//		if (isCheck && !m_isPass)
	//		{   

	//			player->SetDrawActive(false);
	//			GetStage()->AddGameObject<ClearChara>();
	//			CreateTitle();
	//			ClearPause();
	//			PostEvent(5.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	//			
	//		}

	//	}

	//}

	void ClearObject::OnUpdate()
	{
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = GetStage();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		if (player)
		{
			auto playerPos = player->GetComponent<Transform>()->GetPosition();
			auto pos = GetComponent<Transform>()->GetPosition();
			auto distance = Vec3(playerPos - pos);
			auto scale = GetComponent<Transform>()->GetScale();
			bool isCheck = abs(distance.x) < scale.x && abs(distance.y) < scale.y && abs(distance.z) < scale.z;
			if (isCheck && !m_isPass)
			{
				//auto soundMgr = stage->GetSharedGameObject<SoundMgr>(L"SoundMgr");
				//soundMgr->StopStageBGM();
				App::GetApp()->GetScene<Scene>()->BGMStop();
				scene->SEStart(L"Clear");
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClear");
			}
		}

	}

	void ClearObject::CreateTitle()
	{
		Col4 Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		//タイトルロゴ
		auto Button_Title = GetStage()->AddGameObject<Sprite>(L"TEX_Clear", true, Vec2(1000.0f, 100.0f), Vec2(0.0f, 200.0f), Color, Color);

	}

	void ClearObject::ClearPause()
	{
		auto stage = GetStage();
		auto gameObjects = stage->GetGameObjectVec();
		for (auto& gameObject : gameObjects)
		{
			if (dynamic_pointer_cast<ClearChara>(gameObject))
			{
				continue;
			}
			gameObject->SetUpdateActive(false);
		}


	}


}
//end basecross
