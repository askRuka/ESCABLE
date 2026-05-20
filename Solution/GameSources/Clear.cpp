#include "stdafx.h"
#include "Project.h"
#include "State.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void Clear::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(-5.0f, 1.0f, -2.0f));
		PtrCamera->SetAt(Vec3(0.0f, 1.5f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

	}

	void Clear::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePlayerChara();
			CreateFloor();
			CreateTitle();
			CreateAnimeSprite();
			//StageNumの初期化
			auto PtrScene = App::GetApp()->GetScene<Scene>();

		}
		catch (...) {
			throw;
		}
	}
	void Clear::OnUpdate() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			//ゲームステージへ
			//Aボタン
			//switch (PtrScene->GetStageNum()) {
			//case 1:
				PtrScene->SetIsFirstStart(true);
				//CSVファイルの確定
				PostEvent(0.0f, GetThis<Clear>(), PtrScene, L"ToSelectScene");
			//	break;
			//}
		}

	}
	void Clear::CreatePlayerChara()
	{
		auto character = AddGameObject<ClearChara>();
	}
	void Clear::CreateFloor()
	{
		auto floor = AddGameObject<ClearFloor>(
			Vec3(10.0f, 1.0f, 10.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

	}

	void Clear::CreateTitle()
	{
		Col4 Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		//タイトルロゴ
		auto Button_Title = AddGameObject<Sprite>(L"TEX_Clear", true, Vec2(1000.0f, 100.0f), Vec2(0.0f, 150.0f), Color, Color);

	}
	void Clear::CreateAnimeSprite() {
		auto PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_Select", true,
			Vec2(400.0f, 150.0f), Vec2(0.0f, 0.0f));
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;
	}


	void ClearChara::OnCreate()
	{
		InitDrawComp();
		InitTransComp();
	}

	void ClearChara::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		float animeSpeed = delta * m_speed;
		m_drawComp->UpdateAnimation(animeSpeed);

		//m_pos.x += delta * 0.50f;
		m_transComp->SetPosition(m_pos);
	}

	void ClearChara::InitDrawComp()
	{
		m_drawComp = AddComponent<PNTDXModelDraw>();
		m_drawComp->SetMultiMeshResource(L"MODEL_PLAYER_DX_NORMAL");
		m_drawComp->AddAnimation(L"ANN_CLESR", 80, 30, true);
	}

	void ClearChara::InitTransComp()
	{
		m_transComp = GetComponent<Transform>();

		m_pos = Vec3(0.0f, 0.0f, 0.0f);
		m_transComp->SetPosition(m_pos);

		m_scale = Vec3(0.1f, 0.1f, 0.1f);
		m_transComp->SetScale(m_scale);

		Vec3 rot;
		rot = Vec3(0.0f, 1.3f, 0.0f);
		m_transComp->SetRotation(rot);
	}

}