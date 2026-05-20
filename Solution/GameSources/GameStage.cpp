/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>();
		camera->SetEye(Vec3(0.0f, 10.0f, -15.0f));
		camera->SetAt(Vec3(0.0f, 3.0f, 0.0f));
		m_camera = camera;

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
		//light->SetAmbientLightColor(Col4(0.5f, 0.5f, 0.5f, 1.0f));
	}

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//PlayBGM();
			//CreateStage();
			//CreateTestStage();


			auto player = AddGameObject<Player>();
			m_camera->SetTargetObject(player);
			auto pause = AddGameObject<Pause>();
			SetSharedGameObject(L"Player", player);
			//エディターの作成
			//AddGameObject<Editor>();

			auto path = App::GetApp()->GetDataDirWString();
			auto loder = AddGameObject<StageLoader>();
			int loadNum = App::GetApp()->GetScene<Scene>()->GetLoadStageNumber();
			loder->LoadStageFile(path + L"Stages\\stage_" + to_wstring(loadNum) + L".stg");
			//loder->LoadStageFile(path + L"\stage.stg");
			//カメラなどからのデバッグストリングを受け取るためのオブジェクト
			auto strMng = AddGameObject<DebugStrMng>();
			SetSharedGameObject(L"DebugStrMng", strMng);

			m_SoundMgr = AddGameObject<SoundMgr>();
			SetSharedGameObject(L"SoundMgr", m_SoundMgr);
			PlayBGM();
			//auto enemy = AddGameObject<Enemy2>(Vec3(2.0f), Vec3(0.0f), Vec3(0.0f));
			//AddGameObject<EnemyRouteMaker>(enemy, nullptr);

			//エディターの作成
			AddGameObject<Editor>();


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::PlayBGM()
	{
		//m_SoundMgr->PlayStageBGM();
		App::GetApp()->GetScene<Scene>()->BGMStart(L"STAGE");
	}

	void GameStage::StopBGM()
	{
		//m_SoundMgr->StopStageBGM();
		App::GetApp()->GetScene<Scene>()->BGMStop();

	}

	void GameStage::CreateStage() {
		AddGameObject<Floor>(
			Vec3(30.0f, 1.0f, 30.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f,  0.0f)
		);

	//	CreateSharedObjectGroup(L"Lifts");
	//	CreateSharedObjectGroup(L"StageObjects");


	//	//----【StageOfset】--------------------------------------------------------------------------------------
	//	Vec3 S1Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ１	(ドアのチュートリアル)
	//	Vec3 S2Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ２	(垂直移動リフトのチュートリアル)
	//	Vec3 S3Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ３	(平行移動リフトのチュートリアル)
	//	Vec3 S4Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ4	(砲台のチュートリアル)
	//	Vec3 S5Pos = Vec3(0.0f, 0.0f, 0.0f);


	//	//----【Stage1】------------------------------------------------------------------------------------------
	//		//<Wall>	
	//			//左壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 15.5f, S1Pos.y + 9.5f, S1Pos.z + -5.0f)
	//	);
	//	//右壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + -15.5f, S1Pos.y + 9.5f, S1Pos.z + -5.0f)
	//	);
	//	//後ろ壁
	//	AddGameObject<Wall>(
	//		Vec3(32.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 9.5f, S1Pos.z + 15.5f)
	//	);

	//	//<Floor>
	//		//全体床
	//	AddGameObject<Floor>(
	//		Vec3(30.0f, 1.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + -0.5f, S1Pos.z + -5.0f)
	//	);

	//	//<Roof>
	//		//全体天井
	//	AddGameObject<Roof>(
	//		Vec3(30.0f, /*1.0f*/0.9f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 19.5f, S1Pos.z + -5.0f)
	//	);
	//	//奥ちょい低め天井
	//	AddGameObject<Roof>(
	//		Vec3(30.0f, 4.0f, 10.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 17.0f, S1Pos.z + -20.0f)
	//	);

	//	//<Consent>
	//		//右壁コンセント
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, -XM_PIDIV2, 0.0f),
	//		Vec3(S1Pos.x + -14.5f, S1Pos.y + 10.0f, S1Pos.z + -5.0f)
	//	);

	//	//<Door>
	//		//正面ドア
	//	auto door01 = AddGameObject<Door>(
	//		Vec3(30.0f, 15.0f, 0.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 7.5f, S1Pos.z + -25.0f)
	//	);
	//	//<ElectricTrigger>
	//		//正面ドア付属スイッチ
	//	auto trigger01 = AddGameObject<ElectricTrigger>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 13.5f, S1Pos.y + 9.0f, S1Pos.z + -5.0f)
	//	);
	//	door01->SwitchSetter(trigger01);

	//	//----【Stage2】----------------------------------------------------------------------------------
	//		//<Wall>
	//			//左壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + 15.5f, S2Pos.y + 9.5f, S2Pos.z + -45.0f)
	//	);
	//	//右壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -15.5f, S2Pos.y + 9.5f, S2Pos.z + -35.0f)
	//	);
	//	//奥壁
	//	AddGameObject<Wall>(
	//		Vec3(32.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + 0.0f, S2Pos.y + 9.5f, S2Pos.z + -65.5f)
	//	);
	//	//右通路左壁
	//	AddGameObject<Wall>(
	//		Vec3(100.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -65.0f, S2Pos.y + 9.5f, S2Pos.z + -65.5f)
	//	);
	//	//右通路右壁
	//	AddGameObject<Wall>(
	//		Vec3(100.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -65.0f, S2Pos.y + 9.5f, S2Pos.z + -45.5f)
	//	);
	//	//右通路奥側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 22.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -115.5f, S2Pos.y + 9.5f, S2Pos.z + -55.0f)
	//	);
	//	//右通路奥側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 22.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -115.5f, S2Pos.y + 30.5f, S2Pos.z + -55.0f)
	//	);
	//	//右通路右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(40.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -95.5f, S2Pos.y + 30.5f, S2Pos.z + -45.5f)
	//	);
	//	//右通路左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(21.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -105.5f, S2Pos.y + 30.5f, S2Pos.z + -65.5f)
	//	);

	//	//右通路手前側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 23.0f, 22.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -75.5f, S2Pos.y + 30.5f, S2Pos.z + -55.0f)
	//	);


	//	//<Floor>
	//		//正面通路床
	//	AddGameObject<Floor>(
	//		Vec3(30.0f, 1.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + 0.0f, S2Pos.y + -0.5f, S2Pos.z + -45.0f)
	//	);
	//	//右通路床
	//	AddGameObject<Floor>(
	//		Vec3(100.0f, 1.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -65.0f, S2Pos.y + -0.5f, S2Pos.z + -55.0f)
	//	);

	//	//<Roof>
	//			//正通路天井
	//	AddGameObject<Roof>(
	//		Vec3(30.0f, 1.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + 0.0f, S2Pos.y + 19.5f, S2Pos.z + -45.0f)
	//	);
	//	//右通路天井
	//	AddGameObject<Roof>(
	//		Vec3(60.0f, 1.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -45.0f, S2Pos.y + 19.5f, S2Pos.z + -55.0f)
	//	);
	//	//右通路奥側上天井
	//	AddGameObject<Roof>(
	//		Vec3(40.0f, 1.0f, 22.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -95.5f, S2Pos.y + 40.5f, S2Pos.z + -55.0f)
	//	);

	//	//<Consent>
	//			//右通路奥側上壁のコンセント
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, -XM_PIDIV2, 0.0f),
	//		Vec3(S2Pos.x + -115.0f, S2Pos.y + 20.5f, S2Pos.z + -55.0f)
	//	);

	//	//<Lift>
	//			//右通路上下移動リフト
	//	auto ptrLift3 = AddGameObject<Lift>(
	//		Vec3(2.5f, 0.5f, 2.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S2Pos.x + -85.5f, S2Pos.y + 0.5f, S2Pos.z + -55.0f),
	//		Vec3(0.0f, 19.5f, 0.0f)
	//	);
	//	SetSharedGameObject(L"Lift3", ptrLift3);
	//	ptrLift3->AddTag(L"Lift3");


	//	//----【Stage3】----------------------------------------------------------------------------------
	//		//<Wall>
	//			//右側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 119.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -95.5f, S3Pos.y + 9.5f, S3Pos.z + -125.5f)
	//	);
	//	//右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 119.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -95.5f, S3Pos.y + 30.5f, S3Pos.z + -125.5f)
	//	);
	//	//左側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 120.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -75.5f, S3Pos.y + 9.5f, S3Pos.z + -125.5f)
	//	);
	//	//左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 120.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -75.5f, S3Pos.y + 30.5f, S3Pos.z + -125.5f)
	//	);




	//	//<Floor>
	//		//手前床
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -85.5f, S3Pos.y + 9.5f, S3Pos.z + -76.0f)
	//	);
	//	//向こう側床
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -85.5f, S3Pos.y + 9.5f, S3Pos.z + -155.0f)
	//	);

	//	//<Checkpoint>
	//	AddGameObject<Checkpoint>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -85.5f, S3Pos.y + 21.0f, S3Pos.z + -155.0f)
	//	);


	//	//<Roof>
	//		//最初の天井
	//	AddGameObject<Roof>(
	//		Vec3(20.0f, 1.0f, 99.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -85.5f, S3Pos.y + 40.5f, S3Pos.z + -115.5f)
	//	);


	//	//<Consent>
	//		//左側上壁のコンセント
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, XM_PIDIV2, 0.0f),
	//		Vec3(S3Pos.x + -76.0f, S3Pos.y + 30.5f, S3Pos.z + -115.5f)
	//	);




	//	//<Lift>
	//		//平行移動リフト
	//	auto ptrLift4 = AddGameObject<Lift>(
	//		Vec3(2.5f, 0.5f, 2.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -85.5f, S3Pos.y + 20.0f, S3Pos.z + -95.0f),
	//		Vec3(0.0f, 0.0f, -40.0f)

	//	);
	//	SetSharedGameObject(L"Lift4", ptrLift4);
	//	ptrLift4->AddTag(L"Lift4");

	//	//----【Stage4】----------------------------------------------------------------------------------

	//		//<Wall>
	//			//右側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -95.5f, S4Pos.y + 9.5f, S4Pos.z + -195.0f)
	//	);
	//	//右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -95.5f, S4Pos.y + 30.5f, S4Pos.z + -195.0f)
	//	);
	//	//奥側下壁
	//	AddGameObject<Wall>(
	//		Vec3(40.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -75.5f, S4Pos.y + 9.5f, S4Pos.z + -205.0f)
	//	);
	//	//奥側上壁
	//	AddGameObject<Wall>(
	//		Vec3(40.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -75.5f, S4Pos.y + 30.5f, S4Pos.z + -205.0f)
	//	);
	//	//左側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -55.5f, S4Pos.y + 9.5f, S4Pos.z + -195.0f)
	//	);
	//	//左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S3Pos.x + -55.5f, S3Pos.y + 30.5f, S3Pos.z + -195.0f)
	//	);
	//	////左側下壁２
	//	//AddGameObject<Wall>(
	//	//	Vec3(1.0f, 21.0f, 20.0f),
	//	//	Vec3(0.0f, 0.0f, 0.0f),
	//	//	Vec3(S3Pos.x + -55.5f, S3Pos.y + 9.5f, S3Pos.z + -175.0f)
	//	//);
	//	//左側上壁２
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -55.5f, S4Pos.y + 30.5f, S4Pos.z + -175.0f)
	//	);
	//	//手前側上壁
	//	AddGameObject<Wall>(
	//		Vec3(20.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.5f, S4Pos.y + 30.5f, S4Pos.z + -165.0f)
	//	);


	//	//長下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 59.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -55.5f, S4Pos.y + 9.5f, S4Pos.z + -135.5f)
	//	);
	//	//砲台横壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 19.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -55.5f, S4Pos.y + 9.5f, S4Pos.z + -75.5f)
	//	);

	//	//手前右通路右側壁
	//	AddGameObject<Wall>(
	//		Vec3(59.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + 9.5f, S4Pos.z + -185.5f)
	//	);
	//	//手前右通路左側壁
	//	AddGameObject<Wall>(
	//		Vec3(59.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + 9.5f, S4Pos.z + -164.5f)
	//	);

	//	//奥右通路右側壁
	//	AddGameObject<Wall>(
	//		Vec3(70.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -20.0f, S4Pos.y + 9.5f, S4Pos.z + -106.5f)
	//	);
	//	//奥右通路左側壁
	//	AddGameObject<Wall>(
	//		Vec3(70.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -20.0f, S4Pos.y + 9.5f, S4Pos.z + -84.5f)
	//	);
	//	//奥右通路奥側壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 22.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + 14.5f, S4Pos.y + 9.5f, S4Pos.z + -95.5f)
	//	);






	//	//<Floor>
	//		//階段床１
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -85.5f, S4Pos.y + 5.5f, S4Pos.z + -175.0f)
	//	);
	//	//階段床２
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -85.5f, S4Pos.y + 0.5f, S4Pos.z + -195.0f)
	//	);
	//	//階段床３
	//	AddGameObject<Floor>(
	//		Vec3(19.5f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.75f, S4Pos.y + -4.5f, S4Pos.z + -195.0f)
	//	);
	//	//長床
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 1.0f, 120.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.5f, S4Pos.y + -0.5f, S4Pos.z + -125.0f)
	//	);

	//	//手前右通路側長床
	//	AddGameObject<Floor>(
	//		Vec3(60.0f, 1.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + -0.5f, S4Pos.z + -175.0f)
	//	);

	//	//奥右通路側長床
	//	AddGameObject<Floor>(
	//		Vec3(70.0f, 1.0f, 21.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -20.5f, S4Pos.y + -0.5f, S4Pos.z + -95.5f)
	//	);




	//	//<Roof>

	//	AddGameObject<Roof>(
	//		Vec3(20.0f, 1.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -85.5f, S4Pos.y + 40.5f, S4Pos.z + -185.0f)
	//	);

	//	AddGameObject<Roof>(
	//		Vec3(20.0f, 1.0f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.5f, S4Pos.y + 40.5f, S4Pos.z + -185.0f)
	//	);

	//	//長天井
	//	AddGameObject<Roof>(
	//		Vec3(20.0f, 1.0f, 99.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.5f, S4Pos.y + 20.5f, S4Pos.z + -115.0f)
	//	);

	//	//手前右通路側長天井
	//	AddGameObject<Roof>(
	//		Vec3(59.0f, 1.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + 20.5f, S4Pos.z + -175.0f)
	//	);
	//	//手前右通路側ちょい低め天井
	//	AddGameObject<Roof>(
	//		Vec3(20.0f, 5.5f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + 17.5f, S4Pos.z + -175.0f)
	//	);

	//	//奥右通路側長床
	//	AddGameObject<Roof>(
	//		Vec3(70.0f, 1.0f, 21.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -20.5f, S4Pos.y + 20.5f, S4Pos.z + -95.5f)
	//	);


	//	//<Door>
	//		//手前右通路側ドア
	//	auto door02 = AddGameObject<Door>(
	//		Vec3(0.5f, 15.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -25.5f, S4Pos.y + 7.5f, S4Pos.z + -175.0f)
	//	);

	//	//<ElectricTrigger>
	//		//手前右通路側ドア付属スイッチ
	//	auto trigger02 = AddGameObject<ElectricTrigger>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + 0.0f, S4Pos.y + 5.5f, S4Pos.z + -95.5f)
	//	);
	//	door02->SwitchSetter(trigger02);



	//	//<Consent>
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S4Pos.x + -65.5f, S4Pos.y + 15.0f, S4Pos.z + -66.0f)
	//	);




	//	//<Luncher>
	//	AddGameObject<Luncher>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, -XM_PIDIV2, 0.0f),
	//		Vec3(S4Pos.x + -74.5f, S4Pos.y + 2.0f, S4Pos.z + -120.5f),
	//		Vec3(1.0f, 0.0f, 0.0f),
	//		float(3.0f),
	//		float(12.0f),
	//		float(1.0f)
	//	);
	//	AddGameObject<Luncher>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, XM_PIDIV2, 0.0f),
	//		Vec3(S4Pos.x + -56.5f, S4Pos.y + 2.0f, S4Pos.z + -140.5f),
	//		Vec3(-1.0f, 0.0f, 0.0f),
	//		float(3.0f),
	//		float(12.0f),
	//		float(0.0f)
	//	);

	//	//----【Stage5】------------------------------------------------------------------------------------

	//		//<Wall>
	//			//右上壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 30.5f, S5Pos.z + -205.0f)
	//	);
	//	//右上壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 50.5f, S5Pos.z + -205.0f)
	//	);


	//	//右下壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 9.5f, S5Pos.z + -205.0f)
	//	);

	//	//左上壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 30.5f, S5Pos.z + -145.0f)
	//	);
	//	//左上壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 50.5f, S5Pos.z + -145.0f)
	//	);


	//	//左下壁
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 9.5f, S5Pos.z + -145.0f)
	//	);

	//	//右上壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 30.5f, S5Pos.z + -205.0f)
	//	);
	//	//右上壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 50.5f, S5Pos.z + -205.0f)
	//	);

	//	//右下壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 9.5f, S5Pos.z + -205.0f)
	//	);

	//	//左上壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 30.5f, S5Pos.z + -145.0f)
	//	);
	//	//左上壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 50.5f, S5Pos.z + -145.0f)
	//	);

	//	//左下壁2
	//	AddGameObject<Wall>(
	//		Vec3(60.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 94.5f, S5Pos.y + 9.5f, S5Pos.z + -145.0f)
	//	);


	//	//奥左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 30.5f, S5Pos.z + -155.0f)
	//	);
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 50.5f, S5Pos.z + -155.0f)
	//	);

	//	//奥左側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 9.5f, S5Pos.z + -155.0f)
	//	);
	//	//奥右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 30.5f, S5Pos.z + -195.0f)
	//	);
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 50.5f, S5Pos.z + -195.0f)
	//	);

	//	//奥右側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 9.5f, S5Pos.z + -195.0f)
	//	);
	//	//奥中央上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 31.5f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 30.5f, S5Pos.z + -175.0f)
	//	);
	//	//奥中央上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 31.5f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 50.5f, S5Pos.z + -175.0f)
	//	);


	//	//手前左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 30.5f, S5Pos.z + -155.0f)
	//	);
	//	//手前左側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 50.5f, S5Pos.z + -155.0f)
	//	);

	//	//手前左側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 9.5f, S5Pos.z + -155.0f)
	//	);
	//	//手前右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 30.5f, S5Pos.z + -195.0f)
	//	);
	//	//手前右側上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 50.5f, S5Pos.z + -195.0f)
	//	);

	//	//手前右側下壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 9.5f, S5Pos.z + -195.0f)
	//	);
	//	//手前中央上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 30.5f, S5Pos.z + -175.0f)
	//	);
	//	//手前中央上壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 4.5f, S5Pos.y + 50.5f, S5Pos.z + -175.0f)
	//	);






	//	//<Floor>
	//		//全体床
	//	AddGameObject<Floor>(
	//		Vec3(120.0f, 1.0f, 60.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 64.5f, S5Pos.y + -0.5f, S5Pos.z + -175.0f)
	//	);
	//	//<Roof>
	//		//全体天井
	//	AddGameObject<Roof>(
	//		Vec3(120.0f, 1.0f, 60.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 64.5f, S5Pos.y + 59.5f, S5Pos.z + -175.0f)
	//	);


	//	//<Consent>
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 5.5f, S5Pos.z + -145.5f)
	//	);

	//	//<Door>
	//		//奥側ドア
	//	auto door03 = AddGameObject<Door>(
	//		Vec3(0.5f, 15.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 124.5f, S5Pos.y + 7.5f, S5Pos.z + -175.0f)
	//	);
	//	//<ElectricTrigger>
	//		//奥側ドア付属スイッチ
	//	auto trigger03 = AddGameObject<ElectricTrigger>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S5Pos.x + 34.5f, S5Pos.y + 5.5f, S5Pos.z + -195.0f)
	//	);
	//	door03->SwitchSetter(trigger03);

	//	//<Enemy>
	//		//お部屋の敵
	//	AddGameObject<Enemy>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, XM_PIDIV2, 0.0f),
	//		Vec3(S5Pos.x + 100.0f, S5Pos.y + 0.0f, S5Pos.z + -175.0f)
	//	);

	//}

	//void GameStage::CreateTestStage() {

	//	Vec3 S0Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ０(最初に作成したでかいステージの仮名)
	//	Vec3 S1Pos = Vec3(0.0f, 0.0f, 0.0f); //ステージ１
	//	//----【Stage1】------------------------------------------------------------------------------------------
	////<Wall>	
	//	//左壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 15.5f, S1Pos.y + 9.5f, S1Pos.z + 0.0f)
	//	);
	//	//右壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + -15.5f, S1Pos.y + 9.5f, S1Pos.z + 0.0f)
	//	);
	//	//後ろ壁
	//	AddGameObject<Wall>(
	//		Vec3(32.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 9.5f, S1Pos.z + 15.5f)
	//	);

	//	//<Floor>
	//		//全体床
	//	AddGameObject<Floor>(
	//		Vec3(30.0f, 1.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + -0.5f, S1Pos.z + 0.0f)
	//	);

	//	//<Roof>
	//		//全体天井
	//	AddGameObject<Roof>(
	//		Vec3(30.0f, /*1.0f*/0.9f, 40.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 19.5f, S1Pos.z + -5.0f)
	//	);
	//	////奥ちょい低め天井
	//	//AddGameObject<Roof>(
	//	//	Vec3(30.0f, 4.0f, 10.0f),
	//	//	Vec3(0.0f, 0.0f, 0.0f),
	//	//	Vec3(S1Pos.x + 0.0f, S1Pos.y + 17.0f, S1Pos.z + -20.0f)
	//	//);

	//	//<Consent>
	//		//右壁コンセント
	//	AddGameObject<Consent>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, -XM_PIDIV2, 0.0f),
	//		Vec3(S1Pos.x + -14.5f, S1Pos.y + 10.0f, S1Pos.z + -5.0f)
	//	);

	//	//<Door>
	//		//正面ドア
	//	auto door01 = AddGameObject<Door>(
	//		Vec3(30.0f, 15.0f, 0.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 0.0f, S1Pos.y + 7.5f, S1Pos.z + -25.0f)
	//	);
	//	//<ElectricTrigger>
	//		//正面ドア付属スイッチ
	//	auto trigger01 = AddGameObject<ElectricTrigger>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S1Pos.x + 13.5f, S1Pos.y + 9.0f, S1Pos.z + -5.0f)
	//	);
	//	door01->SwitchSetter(trigger01);
	//	//----【Stage0】----------------------------------------------------------------------------------

	//	//<Piller>
	//		// 中央の柱
	//	AddGameObject<Piller>(
	//		Vec3(30.0f, 100.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 50.0f, S0Pos.z + -70.0f)
	//	);

	//	//<Wall>
	//			//全体の壁 
	//				//右側
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 101.0f, 110.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -55.5f, S0Pos.y + 49.5f, S0Pos.z + -70.0f)
	//	);
	//	//左側
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 101.0f, 110.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 55.5f, S0Pos.y + 49.5f, S0Pos.z + -70.0f)
	//	);
	//	//奥側
	//	AddGameObject<Wall>(
	//		Vec3(112.0f, 101.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 49.5f, S0Pos.z + -125.5f)
	//	);
	//	//手前側
	//	AddGameObject<Wall>(
	//		Vec3(40.0f, 101.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -36.0f, S0Pos.y + 49.5f, S0Pos.z + -14.5f)
	//	);
	//	AddGameObject<Wall>(
	//		Vec3(40.0f, 101.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 36.0f, S0Pos.y + 49.5f, S0Pos.z + -14.5f)
	//	);
	//	AddGameObject<Wall>(
	//		Vec3(32.0f, 60.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 70.0f, S0Pos.z + -14.5f)
	//	);

	//	//ゴールの壁
	//		//左壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 15.5f, S0Pos.y + 29.5f, S0Pos.z + 0.0f)
	//	);
	//	//右壁
	//	AddGameObject<Wall>(
	//		Vec3(1.0f, 21.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -15.5f, S0Pos.y + 29.5f, S0Pos.z + 0.0f)
	//	);
	//	//後ろ壁
	//	AddGameObject<Wall>(
	//		Vec3(32.0f, 21.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 29.5f, S0Pos.z + 15.5f)
	//	);


	//	//<Floor>
	//			//ステージ全体の床
	//	AddGameObject<Floor>(
	//		Vec3(110.0f, 1.0f, 110.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + -0.5f, S0Pos.z + -70.0f)
	//	);
	//	//1Fの壁兼2Fの床
	//		//左手前側
	//	AddGameObject<Floor>(
	//		Vec3(40.0f, 20.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 35.0f, S0Pos.y + 10.0f, S0Pos.z + -25.0f)
	//	);
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 20.0f, 25.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 45.0f, S0Pos.y + 10.0f, S0Pos.z + -47.5f)
	//	);
	//	//右手前側
	//	AddGameObject<Floor>(
	//		Vec3(40.0f, 20.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -35.0f, S0Pos.y + 10.0f, S0Pos.z + -25.0f)
	//	);
	//	//左奥側
	//	AddGameObject<Floor>(
	//		Vec3(60.0f, 60.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 25.0f, S0Pos.y + 30.0f, S0Pos.z + -115.0f)
	//	);
	//	//右奥側
	//	AddGameObject<Floor>(
	//		Vec3(20.0f, 20.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -45.0f, S0Pos.y + 10.0f, S0Pos.z + -115.0f)
	//	);
	//	//真ん中手前上橋
	//	AddGameObject<Floor>(
	//		Vec3(30.0f, 5.0f, 20.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 17.5f, S0Pos.z + -25.0f)
	//	);
	//	//ゴールの床
	//	AddGameObject<Floor>(
	//		Vec3(30.0f, 1.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 19.5f, S0Pos.z + 0.0f)
	//	);

	//	//<Roof>
	//		//ゴールの天井
	//	AddGameObject<Roof>(
	//		Vec3(30.0f, 1.0f, 30.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 39.5f, S0Pos.z + 0.0f)
	//	);
	//	//ガチ天井
	//	AddGameObject<Roof>(
	//		Vec3(110.0f, 1.0f, 110.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 99.5f, S0Pos.z + -70.0f)
	//	);


	//	//<Consent>
	//		//柱左側のコンセント
	//	AddGameObject<Consent>(
	//		Vec3(0.5f, 0.5f, 0.5f),
	//		Vec3(0.0f, -XM_PIDIV2, 0.0f),
	//		Vec3(S0Pos.x + 15.0f, S0Pos.y + 10.0f, S0Pos.z + -70.0f)
	//	);
	//	//柱右側のコンセント
	//	AddGameObject<Consent>(
	//		Vec3(0.5f, 0.5f, 0.5f),
	//		Vec3(0.0f, XM_PIDIV2, 0.0f),
	//		Vec3(S0Pos.x + -15.0f, S0Pos.y + 20.0f, S0Pos.z + -70.0f)
	//	);

	//	//<Door>
	//	auto door00 = AddGameObject<Door>(
	//		Vec3(30.0f, 20.0f, 0.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 30.0f, S0Pos.z + -14.5f)
	//	);
	//	auto trigger00 = AddGameObject<ElectricTrigger>(
	//		Vec3(0.5f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -5.0f, S0Pos.y + 45.0f, S0Pos.z + -115.0f)
	//	);
	//	door00->SwitchSetter(trigger00);

	//	//<Cannon>
	//	AddGameObject<Cannon>(
	//		Vec3(S0Pos.x + 0.0f, S0Pos.y + 30.0f, S0Pos.z + -70.0f),
	//		Vec3(S0Pos.x + -55.0f, S0Pos.y + 30.0f, S0Pos.z + -70.0f)

	//	);

	//	//<Luncher>
	//		//レーザー発射装置
	//	AddGameObject<Luncher>(
	//		Vec3(1.0f, 1.0f, 1.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -50.0f, S0Pos.y + 21.0f, S0Pos.z + -75.0f),
	//		Vec3(1.0f, 0.0f, 0.0f),
	//		float(1.0f),
	//		float(3.0f),
	//		float(0.0f)
	//	);




	//	//<Lift>
	//			//左側上下移動リフト
	//	auto ptrLift = AddGameObject<Lift>(
	//		Vec3(2.5f, 0.5f, 2.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + 45.0f, S0Pos.y + 0.0f, S0Pos.z + -70.0f),
	//		Vec3(0.0f, 20.0f, 0.0f)
	//	);
	//	SetSharedGameObject(L"Lift", ptrLift);
	//	ptrLift->AddTag(L"Lift");

	//	//右上側横移動リフト
	//	auto ptrLift1 = AddGameObject<Lift>(
	//		Vec3(2.5f, 0.5f, 2.5f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(S0Pos.x + -45.0f, S0Pos.y + 20.0f, S0Pos.z + -45.0f),
	//		Vec3(0.0f, 0.0f, -50.0f)

	//	);
	//	SetSharedGameObject(L"Lift1", ptrLift1);
	//	ptrLift1->AddTag(L"Lift1");











	}

}

//end basecross
