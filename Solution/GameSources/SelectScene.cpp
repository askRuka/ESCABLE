/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void SelectScene::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(5.0f, 5.0f, -5.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void SelectScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetIsFirstStart(true);
			scene->SetCheckpointPos(Vec3(0));
			scene->SetCheckpointRotation(Vec3(0));
			CreateButtons();
			CreateBlackoutCurtain();
			scene->BGMStart(L"BGM_Title");

		}
		catch (...) {
			throw;
		}
	}

	void SelectScene::OnUpdate()
	{
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];
		auto keyState = device.GetKeyState();
		auto delta = app->GetElapsedTime();

		if (m_isStart)
		{
			auto drawComp = m_curtain->GetComponent<PCTSpriteDraw>();
			auto col = drawComp->GetDiffuse();
			col.w += 2.5f * delta;
			drawComp->SetDiffuse(col);
			drawComp->SetEmissive(col);
			return;
		}

		int num = scene->GetLoadStageNumber();

		if (pad.fThumbLX > 0.5f && m_pastPadX < 0.5f || keyState.m_bUpKeyTbl['D'])
		{
			num++;
			scene->SEStart(L"Select");
			UpdateNum(false);
		}
		if (pad.fThumbLX < -0.5f && m_pastPadX > -0.5f || keyState.m_bUpKeyTbl['A'])
		{
			num--;
			scene->SEStart(L"Select");
			UpdateNum(false);
		}
		if (pad.fThumbLY > 0.5f && m_pastPadY < 0.5f || keyState.m_bUpKeyTbl['W'])
		{
			num -= 5;
			scene->SEStart(L"Select");
			UpdateNum(true);
		}
		if (pad.fThumbLY < -0.5f && m_pastPadY > -0.5f || keyState.m_bUpKeyTbl['S'])
		{
			num += 5;
			scene->SEStart(L"Select");
			UpdateNum(false);
		}

		if (num <= 0)num = 15;
		if (num > 15)num = 1;

		m_pastPadX = pad.fThumbLX;
		m_pastPadY = pad.fThumbLY;
		bool load0 = true;
		for (int i = 0; i < 5; i++)
		{
			load0 = load0 && m_con[i];
		}
		if (load0)
		{
			num = 0;
		}
		scene->SetLoadStageNumber(num);



		if (pad.wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bUpKeyTbl[VK_LBUTTON])
		{
			PostEvent(0.6f, GetThis<SelectScene>(), scene, L"ToGameStage");
			scene->SEStart(L"Confirm");
			m_isStart = true;
		}

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bUpKeyTbl[VK_RBUTTON])
		{
			PostEvent(0.0f, GetThis<SelectScene>(), scene, L"ToTitleStage");
		}

		ButtonSelect(num);

		//wstringstream ss;
		//ss << scene->GetDebugString();
		//ss << app->GetStepTimer().GetFramesPerSecond() << endl;
		//ss << L"StageNumber : " << to_wstring(num) << endl;
		//scene->SetDebugString(ss.str());

	}

	void SelectScene::AddButton(const Vec3& pos, const Vec3& scale, const Col4& col, int num)
	{
		auto button = AddGameObject<GameObject>();

		float flontUV = 1.0f / 16.0f * num;
		float backUV = 1.0f / 16.0f * (num + 1);

		vector<VertexPositionColorTexture> vertex =
		{
			{Vec3(-25,  25, 0), col, Vec2(flontUV,0.0f)},
			{Vec3( 25,  25, 0), col, Vec2(backUV,0.0f)},
			{Vec3(-25, -25, 0), col, Vec2(flontUV,1.0f)},
			{Vec3( 25, -25, 0), col, Vec2(backUV,1.0f)},
		};

		vector<uint16_t> indices = 
		{ 
			0,1,2,
			1,3,2 
		};

		auto transComp = button->GetComponent<Transform>();
		transComp->SetScale(scale);
		transComp->SetPosition(pos);
		auto drawComp = button->AddComponent<PCTSpriteDraw>(vertex, indices);
		drawComp->SetDiffuse(col);
		drawComp->SetEmissive(col);
		drawComp->SetTextureResource(L"TEX_NUMBER");
		m_buttons.push_back(button);
	}

	void SelectScene::CreateButtons()
	{
		for (int i = 0; i < 15; i++)
		{
			float scalef = 2.5f;
			float width = 50.0f;
			float haba = 20.0f;
			Vec3 basePos = Vec3(-640.0f + ((1280.0f - (5.0f * scalef * (width + haba) - haba * scalef)) / 2.0f) + scalef * width / 2.0f, 150.0f, 0.0f);
			Vec3 pos = basePos + Vec3(float(i % 5) * scalef * (width + haba), -float(i / 5) * scalef * (width + haba), 0.0f);
			Vec3 scale = Vec3(scalef);
			Col4 col = Col4(1.0f, 1.0f, 1.0f, 1.0f);

			AddButton(pos, scale, col, i + 1);
		}

	}

	void SelectScene::ButtonSelect(int num)
	{
		if (num < 1 || num > m_buttons.size())
		{
			return;
		}

		for (auto& button : m_buttons)
		{
			button->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_buttons[num - 1]->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		m_buttons[num - 1]->GetComponent<PCTSpriteDraw>()->SetEmissive(Col4(1.0f, 1.0f, 0.0f, 1.0f));

	}

	void SelectScene::OnDestroy()
	{
		App::GetApp()->GetScene<Scene>()->BGMStop();

	}

	void SelectScene::CreateBlackoutCurtain()
	{
		auto curtain = AddGameObject<GameObject>();
		Col4 col = Col4(0.0f, 0.0f, 0.0f, 1.0f);
		vector<VertexPositionColorTexture> vertex =
		{
			{Vec3(-640,  360, 0), col, Vec2(0.0f,0.0f)},
			{Vec3( 640,  360, 0), col, Vec2(1.0f,0.0f)},
			{Vec3(-640, -360, 0), col, Vec2(0.0f,1.0f)},
			{Vec3( 640, -360, 0), col, Vec2(1.0f,1.0f)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			1,3,2
		};

		auto transComp = curtain->GetComponent<Transform>();
		auto drawComp = curtain->AddComponent<PCTSpriteDraw>(vertex, indices);
		drawComp->SetTextureResource(L"TEX_T_AudioBar");
		col.w = 0.0f;
		drawComp->SetDiffuse(col);
		drawComp->SetEmissive(col);
		curtain->SetAlphaActive(true);
		m_curtain = curtain;
	}

	void SelectScene::UpdateNum(bool b)
	{
		if (b)
		{
			m_con[m_conNum] = true;
			m_conNum++;
			if (m_conNum >= 5)
			{
				m_conNum = 0;
			}
		}
		else
		{
			for (int a = 0; a < 5; a++)
			{
				m_con[a] = false;
			}
			m_conNum = 0;
		}
	}
}
//end basecross
