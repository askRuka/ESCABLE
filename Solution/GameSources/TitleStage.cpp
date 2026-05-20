#include "stdafx.h"
#include "Project.h"
#include "State.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void TitleStage::CreateViewLight() 
	{
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(2.0f, 1.0f, -6.0f));
		camera->SetAt(Vec3(0.0f, 1.5f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void TitleStage::OnCreate() 
	{
		try 
		{
			//ビューとライトの作成
			CreateViewLight();
			StopBGM();
			ChangeState(EnterTitle::Instance());

			CreateMenuButton();
			MenuButtonInActive();
			CreatePlayerChara();

			SetCursorPos(640, 360);

		}
		catch (...) 
		{
			throw;
		}
	}

	void TitleStage::OnUpdate()
	{
		if (m_currentState)
		{
			m_currentState->Execute(this);
		}


	}

	void TitleStage::StopBGM()
	{
		auto& app = App::GetApp();
		auto m_XAMgr = app->GetXAudio2Manager();
	}

	void TitleStage::CreateMenuButton()
	{
		auto Button_Start = AddGameObject<Sprite>(L"TEX_B_Start", true, Vec2(350.0f, 35.0f), Vec2(0.0f, -75.0f), buttonColor, buttonColor);
		auto Button_Option = AddGameObject<Sprite>(L"TEX_B_Option", true, Vec2(350.0f, 35.0f), Vec2(0.0f, -150.0f), buttonColor, buttonColor);
		auto Button_End = AddGameObject<Sprite>(L"TEX_B_End", true, Vec2(350.0f, 35.0f), Vec2(0.0f, -225.0f), buttonColor, buttonColor);
		//Button_Start->SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));

		m_button_Start = Button_Start;
		m_button_Option = Button_Option;
		m_button_End = Button_End;

		m_SpriteVec[0] = Button_Start;
		m_SpriteVec[1] = Button_Option;
		m_SpriteVec[2] = Button_End;
	}

	void TitleStage::CreatePlayerChara()
	{
		auto character = AddGameObject<TitleChara>();
	}

	void TitleStage::TitleActive()
	{	
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		//auto ptrXA = App::GetApp()->GetXAudio2Manager();

		//タイトルロゴ
		auto Button_Title = AddGameObject<Sprite>(L"TEX_TestTitle", true, Vec2(1350.0f, 135.0f), Vec2(0.0f, 125.0f), buttonColor, buttonColor);
		//「Push A Button」
		auto Button_PushA = AddGameObject<Sprite>(L"TEX_Test01", true, Vec2(512.0f, 40.0f), Vec2(0.0f, -200.0f), buttonColor, buttonColor);
		m_button_PushA = Button_PushA;
		Button_PushA->SetDrawActive(true);

		//ptrXA->Stop(m_BGM);
		//m_BGM = ptrXA->Start(L"BGM_Title", XAUDIO2_LOOP_INFINITE, 1.0);//scene->m_volumeBGM);
		scene->BGMStop();
		scene->BGMStart(L"BGM_Title");

	}

	void TitleStage::TitleInActive()
	{
		//スタートボタン
		auto button_PushA = m_button_PushA.lock();
		m_button_PushA = button_PushA;
		button_PushA->SetDrawActive(false);

	}

	void TitleStage::MenuButtonActive()
	{
		//スタートボタン
		auto Button_Start = m_button_Start.lock();
		m_button_Start = Button_Start;
		Button_Start->SetDrawActive(true);

		//オプションボタン
		auto Button_Option = m_button_Option.lock();
		m_button_Option = Button_Option;
		Button_Option->SetDrawActive(true);

		//終了ボタン
		auto Button_End = m_button_End.lock();
		m_button_End = Button_End;
		Button_End->SetDrawActive(true);
	}

	void TitleStage::MenuButtonInActive()
	{
		//スタートボタン
		auto Button_Start = m_button_Start.lock();
		m_button_Start = Button_Start;
		Button_Start->SetDrawActive(false);

		//オプションボタン
		auto Button_Option = m_button_Option.lock();
		m_button_Option = Button_Option;
		Button_Option->SetDrawActive(false);

		//終了ボタン
		auto Button_End = m_button_End.lock();
		m_button_End = Button_End;
		Button_End->SetDrawActive(false);
	}


	void TitleStage::OptionActive()
	{
		m_option = AddGameObject<Option>();
		m_option->OptionMenuActive(true);
	}

	void TitleStage::OptionInActive()
	{
		m_option->OptionMenuActive(false);
	}

	void TitleStage::HowToPlayStart()
	{
		m_howtoplay = AddGameObject<HowToPlay>();
		m_howtoplay->HowToPlayMenuActive(true);
	}

	void TitleStage::HowToPlayActive(bool active)
	{
		m_howtoplay->HowToPlayMenuActive(active);
	}

	void TitleStage::HowToPlayInActive()
	{
		m_howtoplay->HowToPlayInMenuActive();
	}

	void TitleStage::GameStart()
	{
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();

		//auto ptrXA = App::GetApp()->GetXAudio2Manager();
		//ptrXA->Stop(m_BGM);
		//ptrXA->OnDestroy();
		scene->BGMStop();
		PostEvent(0.0f, GetThis<TitleStage>(), scene, L"ToSelectScene");
	}

	void TitleStage::ChangeState(State<TitleStage>* newState)
	{
		if (m_currentState) m_currentState->Exit(this);
		m_currentState = newState;
		if (m_currentState)m_currentState->Enter(this);
	}

	void TitleStage::OnDestroy()
	{

	}

	//---------------------------------------------
	// タイトルキャラクター
	//---------------------------------------------

	void TitleChara::OnCreate()
	{
		InitDrawComp();
		InitTransComp();
	}

	void TitleChara::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		float animeSpeed = delta * m_speed;
		m_drawComp->UpdateAnimation(animeSpeed);

		m_pos.x += delta * 1.10f;
		m_transComp->SetPosition(m_pos);
	}

	void TitleChara::InitDrawComp()
	{
		m_drawComp = AddComponent<PNTBoneModelDraw>();
		m_drawComp->SetMultiMeshResource(L"MODEL_PLAYER_WALK");
		m_drawComp->AddAnimation(L"ANN_WALK", 0, 29, true);
	}

	void TitleChara::InitTransComp()
	{
		m_transComp = GetComponent<Transform>();

		m_pos = Vec3(-7.5f, 0.0f, 0.0f);
		m_transComp->SetPosition(m_pos);

		Vec3 rot;
		rot = Vec3(0.0f, -1.0f, 0.0f);
		m_transComp->SetRotation(rot);
	}
}