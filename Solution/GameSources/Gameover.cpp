#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameOver::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameOver::OnCreate() {
		try {
			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			//ビューとライトの作成
			CreateViewLight();
			CreateAnimeSprite();
			//StageNumの初期化
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			PtrScene->SetStageNum(1);
			
			scene->SEStart(L"GameOver");
		}
		catch (...) {
			throw;
		}
	}
	void GameOver::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			PtrScene->SEStart(L"Confirm");
			//ゲームステージへ
			//Aボタン
			switch (PtrScene->GetStageNum()) {
			case 1:
				PtrScene->SetIsFirstStart(false);
				PtrScene->BGMStop();
				//CSVファイルの確定
				PostEvent(0.0f, GetThis<GameOver>(), PtrScene, L"ToGameStage");
				break;
			case 2:
				PtrScene->SetIsFirstStart(true);
				PtrScene->SetCheckpointPos(Vec3(0));
				PtrScene->BGMStop();
				//CSVファイルの確定
				PostEvent(0.0f, GetThis<GameOver>(), PtrScene, L"ToTitleStage");
				break;
			//case 3:
			//	PtrScene->SetIsFirstStart(true);
			//	PtrScene->BGMStop();
			//	//CSVファイルの確定
			//	PostEvent(0.0f, GetThis<GameOver>(), PtrScene, L"ToTitleStage");
			//	break;
			}
		}
		if (!m_CntrolLock) {
			if (CntlVec[0].fThumbLY >= 0.8f || keyState.m_bUpKeyTbl['W']) {
				StageNum--;
				if (StageNum < 1) {
					StageNum = 2;
				}
				m_CntrolLock = true;
				PtrScene->SetStageNum(StageNum);
				ChangeSelect(StageNum);
				PtrScene->SEStart(L"Select");
			}
			else if (CntlVec[0].fThumbLY <= -0.8f || keyState.m_bUpKeyTbl['S']) {
				StageNum++;
				if (StageNum > 2) {
					StageNum = 1;
				}
				m_CntrolLock = true;
				PtrScene->SetStageNum(StageNum);
				ChangeSelect(StageNum);
				PtrScene->SEStart(L"Select");

			}
		}
		else {
			if (CntlVec[0].fThumbLY == 0.0f) {
				m_CntrolLock = false;
			}
		}

	}
	void GameOver::CreateAnimeSprite() {
		//auto PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_CheckPoint", true,
		//	Vec2(400.0f, 150.0f), Vec2(0.0f, 100.0f));
		//PtrSp->SetSelect(true);
		//m_SpVec[0] = PtrSp;
		//PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_First", true,
		//	Vec2(400.0f, 150.0f), Vec2(0.0f, 0.0f));
		//m_SpVec[1] = PtrSp;
		//PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_Title", true,
		//	Vec2(400.0f, 150.0f), Vec2(0.0f, -100.0f));
		//m_SpVec[2] = PtrSp;
		auto PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_Restart", true,
			Vec2(400.0f, 150.0f), Vec2(0.0f, 50.0f));
		PtrSp->SetSelect(true);
		m_SpVec[0] = PtrSp;
		PtrSp = AddGameObject<GameOverSprite>(L"TEX_B_Title", true,
			Vec2(400.0f, 150.0f), Vec2(0.0f, -50.0f));
		m_SpVec[1] = PtrSp;
	}
	void GameOver::ChangeSelect(int num) {
		for (int i = 0; i < 2; i++) {
			shared_ptr<GameOverSprite> shptr = m_SpVec[i].lock();
			if (shptr) {
				if ((i + 1) == num) {
					shptr->SetSelect(true);
				}
				else {
					shptr->SetSelect(false);
				}
			}
		}
	}

}