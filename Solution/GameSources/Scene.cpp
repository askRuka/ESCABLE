
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {

		//アプリケーション取得
		auto& app = App::GetApp();
		auto mediaPath = app->GetDataDirWString();

		//----【テクスチャ】--------------------------------------------------------------------

		auto texPath = mediaPath + L"Textures\\"; // テクスチャパス取得

		// PUSH A BUTTON 
		app->RegisterTexture(L"TEX_Test01", texPath + L"test01.png");

		// 始める
		app->RegisterTexture(L"TEX_B_Start", texPath + L"Button_Start.png");

		// 設定
		app->RegisterTexture(L"TEX_B_Option", texPath + L"Button_Option.png");

		// 終了
		app->RegisterTexture(L"TEX_B_End", texPath + L"Button_End.png");

		// BGM
		app->RegisterTexture(L"TEX_T_BGM", texPath + L"Text_BGM.png");

		// SE
		app->RegisterTexture(L"TEX_T_SE", texPath + L"Text_SE.png");

		// オーディオ設定バー
		app->RegisterTexture(L"TEX_T_AudioBar", texPath + L"T_AudioBar.png");

		// 戻る
		app->RegisterTexture(L"TEX_B_Back", texPath + L"Button_Back.png");

		// 続ける
		app->RegisterTexture(L"TEX_B_Restart", texPath + L"Button_Restart.png");

		// はじめから
		app->RegisterTexture(L"TEX_B_First", texPath + L"Button_First.png");

		// チェックポイントから
		app->RegisterTexture(L"TEX_B_CheckPoint", texPath + L"Button_CheckPoint.png");

		// 操作説明
		app->RegisterTexture(L"TEX_B_HowToPlay", texPath + L"Button_HowToPlay.png");

		// タイトルへ戻る
		app->RegisterTexture(L"TEX_B_Title", texPath + L"Button_Title.png");

		// ステージセレクトへ
		app->RegisterTexture(L"TEX_B_Select", texPath + L"Button_NextStage.png");

		// メニュー画面の背景
		app->RegisterTexture(L"TEX_BackScreen", texPath + L"BackScreen.png");

		// タイトルロゴ
		app->RegisterTexture(L"TEX_TestTitle", texPath + L"test_TitleLogo.png");

		//ケーブル照準
		app->RegisterTexture(L"TEX_CableGuide", texPath + L"T_CableGuide.png");

		//床テクスチャ
		app->RegisterTexture(L"TEX_Floor", texPath + L"T_Floor.png");

		//壁01テクスチャ
		app->RegisterTexture(L"TEX_Wall01", texPath + L"T_Wall01.png");

		//壁02テクスチャ
		app->RegisterTexture(L"TEX_Wall02", texPath + L"T_Wall02.png");

		//柱テクスチャ
		app->RegisterTexture(L"TEX_Piller", texPath + L"T_Piller.png");

		//天井テクスチャ
		app->RegisterTexture(L"TEX_Roof", texPath + L"T_Roof.png");

		//ドアテクスチャ
		app->RegisterTexture(L"TEX_Door01", texPath + L"T_Door01.png");

		//ドアテクスチャ2
		app->RegisterTexture(L"TEX_Door02", texPath + L"T_Door02.png");

		// 透明テクスチャ
		app->RegisterTexture(L"TEX_No", texPath + L"notexture.png");

		//レーザーテクスチャ
		app->RegisterTexture(L"TEX_Laser", texPath + L"T_Laser.png");

		//ゲームオーバーロゴ
		app->RegisterTexture(L"TEX_First", texPath + L"First.png");

		//ゲームオーバーロゴ
		app->RegisterTexture(L"TEX_Titl", texPath + L"Titl.png");

		//ゲームオーバーの時のチェックポイントから
		app->RegisterTexture(L"TEX_CheckPoint", texPath + L"checkpoint.png");

		//あそびかた・仕様
		app->RegisterTexture(L"TEX_HtP_Game", texPath + L"HowToPlay_Game.png");

		//あそびかた・操作
		app->RegisterTexture(L"TEX_HtP_Control", texPath + L"HowToPlay_Control.png");

		//ケーブルのテクスチャ
		app->RegisterTexture(L"TEX_EF_Elec", texPath + L"EF_Electric.png");

		// 繝励Λ繧ｰ繧､繝ｳ繧ｨ繝輔ぉ繧ｯ繝・
		app->RegisterTexture(L"TEX_EF_PlugIn", texPath + L"EF_PlugIn.png");

		//�����G�t�F�N�g
		app->RegisterTexture(L"TEX_EF_Explosion", texPath + L"EF_Explosion.png");

		//�E�P�E�[�E�u�E��E��E�̃e�E�N�E�X�E�`�E��E�
		//・ｽP・ｽ[・ｽu・ｽ・ｽ・ｽﾌテ・ｽN・ｽX・ｽ`・ｽ・ｽ

		app->RegisterTexture(L"TEX_Cabel", texPath + L"cable.png");

		//芝生
		app->RegisterTexture(L"TEX_Grass", texPath + L"Grass.png");

		// クリア文字
		app->RegisterTexture(L"TEX_Clear", texPath + L"Text_Clear.png");

		//クリアオーラ
		app->RegisterTexture(L"line", texPath + L"line.png"); 
		// 数字
		app->RegisterTexture(L"TEX_NUMBER", texPath + L"T_Number.png");

		// マウスカーソル
		app->RegisterTexture(L"TEX_CURSOR", texPath + L"cursor.png");


		//----【モデル】------------------------------------------------------------------------

		auto modelPath = mediaPath + L"Models\\"; // モデルパス取得

		//コンセント
		if (app->CheckResource<MeshResource>(L"MODEL_CONSENT"))return; //2回目の読み込みを防ぐ
		auto meshConsent = MeshResource::CreateStaticModelMesh(modelPath + L"Consent\\", L"consent.bmf");
		app->RegisterResource(L"MODEL_CONSENT", meshConsent);

		//リフト床
		auto meshFloor = MeshResource::CreateStaticModelMesh(modelPath + L"Lift\\" + L"Lift_01\\", L"Floor.bmf");
		app->RegisterResource(L"MODEL_FLOOR", meshFloor);

		//リフト枠
		auto meshFrame = MeshResource::CreateStaticModelMesh(modelPath + L"Lift\\" + L"Lift_Fream\\", L"Frame.bmf");
		app->RegisterResource(L"MODEL_FRAME", meshFrame);

		//スイッチ
		auto meshSwitch = MeshResource::CreateStaticModelMesh(modelPath + L"Switch\\", L"Switch01.bmf");
		app->RegisterResource(L"MODEL_SWITCH", meshSwitch);

		//スイッチ変更後
		auto meshSwitch1 = MeshResource::CreateStaticModelMesh(modelPath + L"Switch1\\", L"Switch02.bmf");
		app->RegisterResource(L"MODEL_SWITCH1", meshSwitch1);

		//発射装置
		auto meshLauncher = MeshResource::CreateStaticModelMesh(modelPath + L"Launcher02\\", L"Luncher02.bmf");
		app->RegisterResource(L"MODEL_LAUNCHER", meshLauncher);

		//砲弾
		auto meshLaser = MeshResource::CreateStaticModelMesh(modelPath + L"Laser\\", L"Laser.bmf");
		app->RegisterResource(L"MODEL_LASER", meshLaser);

		//プレイヤーのボルタン
		auto meshPlayer = MultiMeshResource::CreateBoneModelMultiMesh(modelPath + L"PlayerVoltan\\", L"Animation_PlayerVoltan_WB.bmf");
		app->RegisterResource(L"MODEL_PLAYER", meshPlayer);
		auto meshPlayerWalk = MultiMeshResource::CreateBoneModelMultiMesh(modelPath + L"PlayerVoltan\\", L"Animation_PlayerVoltan_Walk.bmf");
		app->RegisterResource(L"MODEL_PLAYER_WALK", meshPlayerWalk);

		{
			auto dxmodel = dxm::DXModel::CreateFromFile(modelPath + L"PlayerVoltan" + L"\\" + L"Player_Voltan" + L".dxm");
			DXModelResource::RegisterDXModel(L"MODEL_PLAYER_DX_NORMAL", dxmodel);
		}
		{
			auto dxmodel = dxm::DXModel::CreateFromFile(modelPath + L"PlayerVoltan" + L"\\" + L"Player_Voltan_NoArm" + L".dxm");
			DXModelResource::RegisterDXModel(L"MODEL_PLAYER_DX_NO_ARM", dxmodel);
		}
		{
			auto dxmodel = dxm::DXModel::CreateFromFile(modelPath + L"PlayerVoltan" + L"\\" + L"Player_Voltan_OnlyLeft" + L".dxm");
			DXModelResource::RegisterDXModel(L"MODEL_PLAYER_DX_NO_RIGHT", dxmodel);
		}
		{
			auto dxmodel = dxm::DXModel::CreateFromFile(modelPath + L"PlayerVoltan" + L"\\" + L"Player_Voltan_OnlyRight" + L".dxm");
			DXModelResource::RegisterDXModel(L"MODEL_PLAYER_DX_NO_LEFT", dxmodel);
		}


		//エネミー
		auto meshEnemy = MultiMeshResource::CreateStaticModelMultiMesh(modelPath + L"Enemy\\", L"Enemy_BoxEnemy.bmf");
		app->RegisterResource(L"MODEL_ENEMY", meshEnemy);


		//----【オーディオ】--------------------------------------------------------------------

		auto soundPath = mediaPath + L"Sounds\\" + L"BGM\\";
		//app->RegisterWav(L"STAGE", soundPath + L"GameStage.wav");
		app->RegisterWav(L"BGM_Title", soundPath + L"Title.wav");
		app->RegisterWav(L"STAGE", soundPath + L"GameStage2.wav");
		app->RegisterWav(L"CHANGE", soundPath + L"FinalStage.wav");



		//SE
		auto CursorWav = mediaPath + L"Sounds\\" + L"SE\\";
		app->RegisterWav(L"ARMARRIVE", CursorWav + L"ArmArrive.wav");
		app->RegisterWav(L"ARRIVE", CursorWav + L"Arrive.wav");
		app->RegisterWav(L"ATTACK", CursorWav + L"ArmArrive.wav");
		app->RegisterWav(L"Select", CursorWav + L"SE_Select01.wav");
		app->RegisterWav(L"Confirm", CursorWav + L"SE_Confirm01.wav");
		app->RegisterWav(L"Cancel", CursorWav + L"SE_Cancel.wav");
		app->RegisterWav(L"CableThrow", CursorWav + L"cableThrow.wav");
		app->RegisterWav(L"CableBack", CursorWav + L"cableBack.wav");
		app->RegisterWav(L"LiftMove", CursorWav + L"lift.wav");
		app->RegisterWav(L"Boom", CursorWav + L"boom.wav");
		app->RegisterWav(L"Clear", CursorWav + L"Clear01.wav");
		app->RegisterWav(L"Walk", CursorWav + L"Walk01.wav");
		app->RegisterWav(L"GameOver", CursorWav + L"GameOver.wav");
	}

	void Scene::OnCreate() {
		try {
			// Shadowmap の描画範囲を拡大（x,z ±1000 程度をカバー）
			// 必要に応じてライトの奥行きも拡大（影が途中で切れる場合）
			Shadowmap::SetViewSize(2200.0f);
			Shadowmap::SetLightFar(3000.0f);

			// Shadowmap の解像度を拡大（最初の生成で確定するため、ここで先に作っておく）
			auto dev = App::GetApp()->GetDeviceResources();
			dev->GetShadowMapRenderTarget(8192.0f*2);

			//リソース作成
			CreateResourses();

			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//タイトルステージの設定
			// 背景色を設定
			SetClearColor(Col4(0.0f, 0.70f, 0.80f, 1.0f)); // みずいろ
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToGameStage") {
			//ゲームステージの設定
			// 背景色を設定
			SetClearColor(Col4(0.0f, 0.0f, 0.0f, 0.0f)); // 黒
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToGameOver") {
			//・ｽ^・ｽC・ｽg・ｽ・ｽ・ｽX・ｽe・ｽ[・ｽW・ｽﾌ設抵ｿｽ
			// ・ｽw・ｽi・ｽF・ｽ・ｽﾝ抵ｿｽ
			SetClearColor(Col4(0.0f, 0.0f, 0.0f, 0.0f)); // ・ｽ・ｽ
			ResetActiveStage<GameOver>();
		}
		if (event->m_MsgStr == L"ToClear") {

			//タイトルステージの設定
			// 背景色を設定
			SetClearColor(Col4(0.0f, 0.70f, 0.80f, 1.0f)); // みずいろ
			ResetActiveStage<Clear>();
		}
		if (event->m_MsgStr == L"ToSelectScene") {

			//タイトルステージの設定
			// 背景色を設定
			SetClearColor(Col4(0.0f, 0.70f, 0.80f, 1.0f)); // みずいろ
			ResetActiveStage<SelectScene>();
		}

	}

	void Scene::OnUpdate()
	{
		SetDebugString(L""); //デバッグ文字列を空にする
		SceneBase::OnUpdate();
	}

	void Scene::BGMStart(const wstring& name)
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAMng->Start(name, XAUDIO2_LOOP_INFINITE, m_volumeBGM);

	}
	void Scene::BGMStop()
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		XAMng->Stop(m_BGM);
	}
	void Scene::SEStart(const wstring& name)
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		XAMng->Start(name, 0, m_volumeSE);
	}

	void Scene::ChangeBGMVolume()
	{
		if (m_BGM->m_SourceVoice)
		{
			m_BGM->m_SourceVoice->SetVolume(m_volumeBGM);
		}
	}
}
//end basecross
