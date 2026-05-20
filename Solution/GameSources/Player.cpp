/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate()
	{
		//各コンポーネントの初期化
		InitDrawComp();
		InitTransComp();
		//左右ケーブルの生成と設定
		m_cable[0] = GetStage()->AddGameObject<Cable>(true);
		m_cable[0]->SetDrawActive(false);
		m_cable[0]->SetPlayer(GetThis<Player>());
		m_cable[0]->SetPlayerDraw(GetThis<Player>());
		m_cable[0]->SetArmBoneName(L"Shoulder_Left");

		m_cable[1] = GetStage()->AddGameObject<Cable>(false);
		m_cable[1]->SetDrawActive(false);
		m_cable[1]->SetPlayer(GetThis<Player>());
		m_cable[1]->SetPlayerDraw(GetThis<Player>());
		m_cable[1]->SetArmBoneName(L"Shoulder_Right");

		m_effectEl = GetStage()->AddGameObject<EffectElec>(L"TEX_EF_Elec", Vec3(1.5f, 1.5f, 1.5f), Col4(0.25f, 0.5f, 1.0f, 1.0f), Col4(0.0f, 0.45f, 0.90f, 1.0f));
		m_effectEl->SetOwner(GetThis<Player>());
		m_effectEl->SetDrawActive(false);

		//PlayerBGM1();
	}

	void Player::OnUpdate()
	{
		//Appとゲームパッドの取得
		auto& app = App::GetApp();
		auto pad = app->GetInputDevice().GetControlerVec()[0];
		//プレイヤーの動き
		NormalMove();
		AnimationUpdate();

		//ケーブルの処理
		InputTriggerCheck(true);
		InputTriggerCheck(false);
		CablesStateCheck();
		//ヒット判定
		//HitCheck();
		//HitCheck2();

		//仮の帯電状態の表現
		//if (GetStatusFlag(PlayerStatus::isCharging))
		//{
		//	m_drawComp->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		//	m_drawComp->SetEmissive(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		//}
		//else
		//{
		//	m_drawComp->SetEmissive(Col4(1.0f, 1.0f, 0.0f, 1.0f));

		//	m_drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		//}
		//デバッグ用文字列
		//auto scene = app->GetScene<Scene>();
		//auto point = app->GetInputDevice().GetKeyState().m_MouseClientPoint;
		//wstringstream ss;
		//ss << scene->GetDebugString();
		//ss << app->GetStepTimer().GetFramesPerSecond() << endl;
		//ss << m_velocityY << endl;
		//ss << m_transComp->GetPosition().x << endl;
		//ss << m_transComp->GetPosition().y << endl;
		//ss << m_transComp->GetPosition().z << endl;
		//ss << m_cableTension.length() << endl;
		//scene->SetDebugString(ss.str());

	}

	// Drawコンポーネントの初期化
	void Player::InitDrawComp()
	{
		//Mat4x4 span; // モデルとトランスフォームの間の差分行列
		//span.affineTransformation(
		//	Vec3(1.7f, 1.7f, 1.7f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//);


		m_drawComp = AddComponent<PNTDXModelDraw>();
		m_drawComp->SetMultiMeshResource(L"MODEL_PLAYER_DX_NORMAL");
		m_drawComp->AddAnimation(L"ANN_IDLE", 0, 30, true);
		m_drawComp->AddAnimation(L"ANN_WALK", 40, 30, true);
		m_drawComp->AddAnimation(L"ANN_CLESR", 80, 30, true);
		m_drawComp->AddAnimation(L"ANN_DEAD", 120, 30, true);
		m_drawComp->ChangeCurrentAnimation(L"ANN_IDLE");

		//m_drawComp->SetMeshToTransformMatrix(span);

		// 影付け
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMultiMeshResource(L"MODEL_PLAYER_DX_NORMAL");

		// 色などの変更
		float emissive = 0.3f;
		m_drawComp->SetEmissive(Col4(emissive, emissive, emissive, 1.0f));
		
		//m_drawComp->AddAnimation(L"Default", 0, 50, true, 20.0f);
		//m_drawComp->ChangeCurrentAnimation(L"Default");
	}

	// Transformコンポーネントの初期化
	void Player::InitTransComp()
	{
		Vec3 pos;
		Vec3 rot;
		if (App::GetApp()->GetScene<Scene>()->GetIsFirstStart())
		{
			pos = Vec3(0, 0, 0);
		}
		else
		{
			pos = App::GetApp()->GetScene<Scene>()->GetCheckpointPos();
			rot = App::GetApp()->GetScene<Scene>()->GetCheckpointRotation();
		}
		m_transComp = GetComponent<Transform>();

//デバッグ用----------------------------------
		// pos = Vec3(20.0f, 0.0f, -175.0f); 
		// pos = Vec3(-65.0f,0.0f,-80.0f);
//--------------------------------------------

		m_transComp->SetPosition(pos);

		m_transComp->SetScale(Vec3(m_scale));
		m_transComp->SetRotation(rot);
	}

	//入力された移動操作のベクトルを返す関数
	Vec3 Player::InputVec()
	{
		if (!m_isControl)
		{
			return Vec3(0);
		}
		//各種入力機器と経過時間の取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];
		auto keyState = device.GetKeyState();
		float delta = app->GetElapsedTime();

		Vec3 v = Vec3(0);
		//X方向の操作
		v.x = pad.fThumbLX;
		if (keyState.m_bPushKeyTbl['A'])
		{
			v.x = -1.0f;
		}
		if(keyState.m_bPushKeyTbl['D'])
		{
			v.x = 1.0f;
		}
		//Z方向の操作
		v.z = pad.fThumbLY;
		if (keyState.m_bPushKeyTbl['W'])
		{
			v.z = 1.0f;
		}
		if (keyState.m_bPushKeyTbl['S'])
		{
			v.z = -1.0f;
		}
		//大きさの調整
		if (v.length() > 1.0f)
		{
			v = v.normalize();
		}
		////ジャンプの確認
		//if ((pad.wPressedButtons & XINPUT_GAMEPAD_A) || keyState.m_bPressedKeyTbl[VK_SPACE])
		//{
		//	v.y = 1.0f;
		//}
		return v;
	}

	// m_velocityXZの更新
	void Player::VelocityXZUpdate(const Vec3& input)
	{
		float delta = App::GetApp()->GetElapsedTime();
		//入力がないときにVelocityを減少させる
		if (input.length() < 0.1f)
		{
			m_velocityXZ.x *= 0.9f;
			m_velocityXZ.z *= 0.9f;
		}
		else
		{
			float Acceleration = 10.0f;//加速度(最高速に達するまでの時間(秒)の逆数)
			//入力をもとに速度を加算
			m_velocityXZ.x += (input.x * cosf(m_cameraAngleY) - input.z * sinf(m_cameraAngleY)) * delta * Acceleration * m_speed;
			m_velocityXZ.z += (input.x * sinf(m_cameraAngleY) + input.z * cosf(m_cameraAngleY)) * delta * Acceleration * m_speed;
			//指定の速度と入力をもとに最大速度を設定
			if (m_velocityXZ.length() > m_speed * input.length())
			{
				m_velocityXZ = m_velocityXZ.normalize() * m_speed * input.length();
			}
		}
	}

	// m_velocityYの更新
	void Player::VelocityYUpdate(bool isJump)
	{
		auto delta = App::GetApp()->GetElapsedTime();
		//常に重力加速度がかかっている
		m_velocityY += -9.8f * delta;
		//ジャンプの処理
		if (isJump && m_statusFlags & PlayerStatus::isGround)
		{
			m_velocityY = 5.0f;
			m_statusFlags -= PlayerStatus::isGround;
		}
		//一応-1000以下に行かないようにする
		Vec3 pos = m_transComp->GetPosition();
		if (m_velocityY * delta + pos.y < -10.0f)
		{
			m_velocityY = 0.0f;
			pos.y = 0;
			if (!(m_statusFlags & PlayerStatus::isGround))
			{
				m_statusFlags += PlayerStatus::isGround;

			}
			//OnGameOver(1.5f, true);
			//OnDestory1();
			PostEvent(0.0, GetThis<ObjectInterface>(), GetThis<Player>(), L"GameOver0");

			//auto stage = GetStage();
			////auto soundMgr = stage->GetSharedGameObject<SoundMgr>(L"SoundMgr");
			////soundMgr->StopStageBGM();
			//App::GetApp()->GetScene<Scene>()->BGMStop();

			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");

		}

	}

	//特定のオブジェクトとの接触を確認する
	void Player::HitCheck(const Vec3& pos, Vec3& nextPos)
	{
		//各ステータスをfalseにする
		SetStatusFlag(PlayerStatus::isGround,false);
		SetStatusFlag(PlayerStatus::isGettingOnLift, false);

		//ステージからオブジェクトの配列を取得
		auto lifts = GetStage()->GetSharedObjectGroup<GameObjectGroup>(L"Lifts");
		auto stageObjs = GetStage()->GetSharedObjectGroup<GameObjectGroup>(L"StageObjects");

		for (const auto& obj : lifts->GetGroupVector())
		{
			//リフトとの判定をとる
			auto lock = obj.lock();
			if (!lock)return;
			auto lift = dynamic_pointer_cast<Lift>(lock);
			if (lift)
			{
				LiftHitCheck(lift, pos, nextPos);
			}

		}
		// リフトに乗っていないときにm_hitLiftPosのy座標をありえない値に帰る
		// リフトとの当たり判定がないときにリフトへの追従の処理を飛ばすため
		if (!GetStatusFlag(PlayerStatus::isGettingOnLift))
		{
			m_hitLifhPos.y = -100;
		}

		for (const auto& obj : stageObjs->GetGroupVector())
		{
			// ステージオブジェクトとの判定をとる
			auto lock = obj.lock();
			if (lock)
			{
				CubeHitCheck(lock, pos, nextPos);
			}

		}

	}


	// リフトとの当たり判定
	void Player::LiftHitCheck(const shared_ptr<GameObject>& lift, const Vec3& pos, Vec3& nextPos)
	{
		//リフトの判定
		auto liftTrans = lift->GetComponent<Transform>();
		Vec3 liftPos = liftTrans->GetPosition(); //リフトの位置
		Vec3 liftScale = liftTrans->GetScale() * 8.0f; // リフトの大きさ
		liftScale.y /= 20.0f;
		//Vec3 pos = m_transComp->GetPosition(); //プレイヤーの位置
		Vec3 scale = m_transComp->GetScale() / m_scale; // プレイヤーのスケール
		Vec3 distance = nextPos - liftPos; // リフトとプレイヤーの距離
		Vec3 scaleSum = (liftScale + scale) / 2.0f; // 大きさの合計
		auto delta = App::GetApp()->GetElapsedTime();
		//x座標とz座標の距離がサイズの合計より小さい、つまりリフトの上か下にいるとき
		if (abs(distance.x) < scaleSum.x && abs(distance.z) < scaleSum.z )
		{
			//リフトの上におり、リフトフレームに床に接触、埋まるとき
			if ( m_hitLifhPos.y >= 0.0f && Vec3(liftPos - m_hitLifhPos).length() < 1.0f)
			{
				m_velocityY = 0.0f;
				nextPos.y = liftPos.y + liftScale.y / 2.0f;

				nextPos = nextPos + (liftPos - m_hitLifhPos);
				SetStatusFlag(PlayerStatus::isGettingOnLift, true);
				SetStatusFlag(PlayerStatus::isGround, true);
				m_hitLifhPos = liftPos;

			}
			else if(distance.y >= -0.5f && distance.y + m_velocityY * delta < liftScale.y / 2.0f)
			{

				m_velocityY = 0.0f;
				nextPos.y = liftPos.y + liftScale.y / 2.0f;
				// m_hitLifhPos.yが-1より小さい時、つまり前フレームでリフトに接触していない時
				if (!m_hitLifhPos.y < -1.0f)
				{
					nextPos = pos + (liftPos - m_hitLifhPos);
				}
				SetStatusFlag(PlayerStatus::isGettingOnLift, true);
				SetStatusFlag(PlayerStatus::isGround, true);
				m_hitLifhPos = liftPos;

			}
		}

	}

	void Player::CubeHitCheck(const shared_ptr<GameObject>& obj, const Vec3& pos, Vec3& nextPos)
	{
		//オブジェクトとの当たり判定
		auto objTrans = obj->GetComponent<Transform>();
		Vec3 objPos = objTrans->GetPosition(); // 壁の座標
		Vec3 objScale = objTrans->GetScale(); // 壁のサイズ
		//Vec3 playerPos = m_transComp->GetPosition(); // プレイヤーの座標
		Vec3 playerScale = m_transComp->GetScale() / m_scale; // プレイヤーのスケール
		Vec3 distance = objPos - pos; // 壁とプレイヤーの距離
		Vec3 scaleSum = (objScale + playerScale) / 2.0f; // 壁とプレイヤーのサイズの合計（密着した時のx,y,zの距離）
		//auto delta = App::GetApp()->GetElapsedTime();

		bool inYRange = (objPos.y - objScale.y / 2.0f <= pos.y + playerScale.y) && (objPos.y + objScale.y / 2.0f >= pos.y + playerScale.y);
		bool inXRange = (objPos.x - objScale.x / 2.0f < pos.x + playerScale.x / 2.0f) && (objPos.x + objScale.x / 2.0f > pos.x - playerScale.x / 2.0f);
		bool inZRange = (objPos.z - objScale.z / 2.0f < pos.z + playerScale.z / 2.0f) && (objPos.z + objScale.z / 2.0f > pos.z - playerScale.z / 2.0f);
		if (inYRange && inXRange)
		{
			//z座標上で重なっていることを確認
			bool minusOver = (objPos.z + objScale.z / 2.0f > nextPos.z - playerScale.z / 2.0f) && (objPos.z + objScale.z / 2.0f <= pos.z - playerScale.z / 2.0f);
			bool plusOver = (objPos.z - objScale.z / 2.0f < nextPos.z + playerScale.z / 2.0f) && (objPos.z - objScale.z / 2.0f >= pos.z + playerScale.z / 2.0f);
			bool inObj = (objPos.z - objScale.z / 2.0f < pos.z + playerScale.z / 2.0f) && (objPos.z + objScale.z / 2.0f > pos.z - playerScale.z / 2.0f);
			if (plusOver || minusOver)
			{
				m_velocityXZ.z = 0.0f;
				if (minusOver)
				{
					nextPos.z = objPos.z + (objScale.z + playerScale.z) / 2.0f;
				}
				else
				{
					nextPos.z = objPos.z + -1 * (objScale.z + playerScale.z) / 2.0f;

				}
			}
			if (inObj)
			{
				nextPos.z = objPos.z + (distance.z < 0 ? 1 : -1) * (objScale.z + playerScale.z) / 2.0f;
			}
		}
		if (inYRange && inZRange)
		{
			bool minusOver = (objPos.x + objScale.x / 2.0f > nextPos.x - playerScale.x / 2.0f) && (objPos.x + objScale.x / 2.0f <= pos.x - playerScale.x / 2.0f);
			bool plusOver = (objPos.x - objScale.x / 2.0f < nextPos.x + playerScale.x / 2.0f) && (objPos.x - objScale.x / 2.0f >= pos.x + playerScale.x / 2.0f);
			bool inObj = (objPos.x - objScale.x / 2.0f < pos.x + playerScale.x / 2.0f) && (objPos.x + objScale.x / 2.0f > pos.x - playerScale.x / 2.0f);

			if (plusOver || minusOver)
			{
				m_velocityXZ.x = 0.0f;
				if (minusOver)
				{
					nextPos.x = objPos.x + (objScale.x + playerScale.x) / 2.0f;
				}
				else
				{
					nextPos.x = objPos.x + -1 * (objScale.x + playerScale.x) / 2.0f;

				}
			}
			if (inObj)
			{
				nextPos.x = objPos.x + (distance.x < 0 ? 1 : -1) * (objScale.x + playerScale.x) / 2.0f;
			}

		}
		if (inZRange && inXRange)
		{
			//y座標上で重なっていることを確認
			bool bottom = objPos.y - objScale.y / 2.0f < nextPos.y + playerScale.y;
			bool top = objPos.y + objScale.y / 2.0f > nextPos.y;
			if ( top && bottom)
			{
				m_velocityY = 0.0f;
				if (distance.y < 0)
				{
					nextPos.y = objPos.y + objScale.y / 2.0f;
					SetStatusFlag(PlayerStatus::isGround, true);
				}
			}
		}


	}

	void Player::InputTriggerCheck(bool LR)
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());
		auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		bool mouseUp = false;
		bool mouseDown = false;
		int n;
		BYTE trigger;
		PlayerStatus status;
		if (LR)
		{
			n = 0;
			trigger = pad.bRightTrigger;
			status = PlayerStatus::isRightPlugIn;
			mouseUp = App::GetApp()->GetInputDevice().GetKeyState().m_bUpKeyTbl[VK_RBUTTON];
			mouseDown = App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl[VK_RBUTTON];

		}
		else
		{
			n = 1;
			trigger = pad.bLeftTrigger;
			status = PlayerStatus::isLeftPlugIn;

			mouseUp = App::GetApp()->GetInputDevice().GetKeyState().m_bUpKeyTbl[VK_LBUTTON];
			mouseDown = App::GetApp()->GetInputDevice().GetKeyState().m_bPushKeyTbl[VK_LBUTTON];
		}
		//トリガーが今押されたかどうか
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		if (trigger >= 128 && m_pastTrigger[n] < 128 || mouseDown)
		{
			if (camera && !(m_statusFlags & status))
			{
				camera->GetStateMachine()->ChangeState(CameraCloserState::Instance());
				m_isAiming = true;
			}
		}

		//トリガーが今離されたかどうかを判定する
		if (trigger <= 128 && m_pastTrigger[n] > 128 || mouseUp)
		{
			auto st = CameraCloserState::Instance();

			if (camera->GetStateMachine()->IsInState(st))
			{
				camera->GetStateMachine()->ChangeState(CameraLeaveState::Instance());
				m_isAiming = false;
			}

			//すでにケーブルがコンセントに入っている場合コンセントから抜く
			if (m_statusFlags & status)
			{
				m_cable[n]->GetStateMachine()->ChangeState(CableBackMoveState::Instance());
				SetStatusFlag(status, false);

			}
			else if (m_cable[n]->OnThrow(m_transComp->GetPosition() + m_armPos[n])) // コンセントに入っておらず、コンセントにあたるときケーブルをつなぐ
			{
				SetStatusFlag(status, true);
			}
		}
		//トリガーの値の保存
		m_pastTrigger[n] = trigger;

	}


	void Player::InitVelocity()
	{
		m_velocityXZ = Vec3(0);
		m_velocityY = 0;
	}


	bool Player::NormalMove()
	{
		if (GetStatusFlag(PlayerStatus::isDead))
		{
			return false;
		}
		float delta = App::GetApp()->GetElapsedTime();
		//移動の処理
		auto inputVec = InputVec();
		VelocityXZUpdate(inputVec);

		//Y軸方向の処理
		//bool isJump = inputVec.y != 0;
		//if (isJump && (m_statusFlags & PlayerStatus::isPlugIn))
		//{
		//	return true;
		//}
		VelocityYUpdate(false);
		Vec3 pos = m_transComp->GetPosition();
		CableLengthCheck();
		auto nextPos = pos + (m_velocityXZ + m_cableTension ) * delta;
		nextPos.y += m_velocityY * delta;
		HitCheck(pos, nextPos);


		// プレイヤーの方向
		float playerAngle = m_transComp->GetQuaternion().toRotVec().y;
		if(inputVec.length() > 0.1f)playerAngle = atan2f(-(inputVec.x * sinf(m_cameraAngleY) + inputVec.z * cosf(m_cameraAngleY)), (inputVec.x * cosf(m_cameraAngleY) - inputVec.z * sinf(m_cameraAngleY))) - XM_PIDIV2;
		// 照準状態のときはカメラに合わせる
		if(m_isAiming)playerAngle = -m_cameraAngleY + XM_PI;

		//プレイヤーの向きを変更
		m_transComp->SetRotation(Vec3(0.0f, playerAngle, 0.0f));

		//腕の位置を計算
		float armAngle = -playerAngle + XM_PI;
		auto scale = m_transComp->GetScale();
		m_armPos[1].x = -cosf(armAngle) * m_armDis * scale.x;
		m_armPos[1].y = 0.5f * scale.y;
		m_armPos[1].z = -sinf(armAngle) * m_armDis * scale.x;
		m_armPos[0].x = cosf(armAngle) * m_armDis * scale.x;
		m_armPos[0].y = 0.5f * scale.y;
		m_armPos[0].z = sinf(armAngle) * m_armDis * scale.x;

		// アニメーションの変更
		if (inputVec.length() < 0.1f)
		{
			auto ann = m_drawComp->GetCurrentAnimation();
			if (ann != L"ANN_IDLE")
			{
				m_drawComp->ChangeCurrentAnimation(L"ANN_IDLE");
			}
		}
		else
		{
			auto ann = m_drawComp->GetCurrentAnimation();
			if (ann != L"ANN_WALK")
			{
				m_drawComp->ChangeCurrentAnimation(L"ANN_WALK");

			}
		}

		m_transComp->SetPosition(nextPos);
		return false;
	}


	bool Player::GetStatusFlag(PlayerStatus status)
	{
		return m_statusFlags & status;
	}

	void Player::SetStatusFlag(PlayerStatus status, bool b)
	{
		if (b && !(m_statusFlags & status))
		{
			m_statusFlags += status;
		}
		else if (!b && (m_statusFlags & status))
		{
			m_statusFlags -= status;
		}
	}

	void Player::PlagInCheck()
	{
		auto hitObj1 = m_cable[0]->GetHitObject();
		auto hitObj2 = m_cable[1]->GetHitObject();
		auto consent1 = dynamic_pointer_cast<Consent>(hitObj1);
		auto consent2 = dynamic_pointer_cast<Consent>(hitObj2);
		auto consent3 = dynamic_pointer_cast<Lift>(hitObj1);
		auto consent4 = dynamic_pointer_cast<Lift>(hitObj2);

		if (consent1 || consent2||consent3||consent4)
		{
			SetStatusFlag(PlayerStatus::isCharging, true);
			//auto ptrXA = App::GetApp()->GetXAudio2Manager();
			//ptrXA->Start(L"ARMARRIVE", XAUDIO2_NO_LOOP_REGION, 0.5f);
			App::GetApp()->GetScene<Scene>()->SEStart(L"ARMARRIVE");
			m_effectEl->SetDrawActive(true);
			//OnDestory1();
			//PlayerBGM2();

		}
		else
		{
			SetStatusFlag(PlayerStatus::isCharging, false);
			m_effectEl->SetDrawActive(false);
			//OnDestory2();
			//PlayerBGM1();
		}
	}
	void Player::PlayerBGM1() {
		//auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//XAPtr->Stop(m_BGM);
		//m_BGM = XAPtr->Start(L"STAGE", XAUDIO2_LOOP_INFINITE, 1.0f);
		App::GetApp()->GetScene<Scene>()->BGMStart(L"STAGE");

	}
	void Player::PlayerBGM2() {
		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();
		//m_BGM1 = XAPtr1->Start(L"CHANGE", XAUDIO2_LOOP_INFINITE, 1.0f);
		App::GetApp()->GetScene<Scene>()->BGMStart(L"CHANGE");

	}

	void Player::OnDestory1() {
		//BGMのストップ
		//auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//XAPtr->Stop(m_BGM);
		App::GetApp()->GetScene<Scene>()->BGMStop();

	}
	void Player::OnDestory2() {
		//BGMのストップ
		//auto XAPtr1 = App::GetApp()->GetXAudio2Manager();
		//XAPtr1->Stop(m_BGM1);
		App::GetApp()->GetScene<Scene>()->BGMStop();

	}

	void Player::CableLengthCheck()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		auto velocity = m_velocityXZ + Vec3(0.0f, m_velocityY, 0.0f);
		auto nextPos = m_transComp->GetPosition() + velocity * delta;
		Vec3 tensionR = Vec3(0.0f);
		Vec3 tensionL = Vec3(0.0f);
		bool RLimit = (m_cable[0]->ChackLength(nextPos) && GetStatusFlag(PlayerStatus::isRightPlugIn));
		bool LLimit = (m_cable[1]->ChackLength(nextPos) && GetStatusFlag(PlayerStatus::isLeftPlugIn));
		if (RLimit)
		{
			auto dir = -m_cable[0]->GetCableDirection();
			//if (velocity.length() < 0.01f)
			//{
			//	velocity = dir * 0.01f;
			//}
			velocity = dir * velocity.length();
			velocity += dir * (-m_cable[0]->GetRemainingLength(nextPos) + 1.0f);
			tensionR = -Vec3(velocity.x, 0.0f, velocity.z);
		}
		if (LLimit)
		{
			auto dir = -m_cable[1]->GetCableDirection();
			//if (velocity.length() < 0.01f)
			//{
			//	velocity = dir * 0.01f;
			//}
			velocity = dir * velocity.length();
			velocity += dir * (-m_cable[1]->GetRemainingLength(nextPos) + 1.0f);
			tensionL = -Vec3(velocity.x, 0.0f, velocity.z);
		}
		if (RLimit && LLimit)
		{
			m_cableTension = (tensionR + tensionL) / 2.0f;
			//m_cableTension = Vec3(tensionR + tensionL).normalize() * m_velocityXZ.length();
		}
		else
		{
			m_cableTension = (tensionR + tensionL);
		}
	}

	void Player::AnimationUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		float animeSpeed = delta;
		if (m_drawComp->GetCurrentAnimation() == L"ANN_WALK")
		{
			animeSpeed = delta * m_velocityXZ.length() / m_speed;
			float f = m_drawComp->GetCurrentAnimationTime();
			if ((int)(f * 8.0f) % 2 == 1)
			{
				if (!m_Steps && GetStatusFlag(PlayerStatus::isGround))
				{
					App::GetApp()->GetScene<Scene>()->SEStart(L"Walk");
					m_Steps = true;
				}
			}
			else
			{
				m_Steps = false;
			}
		}
		m_drawComp->UpdateAnimation(animeSpeed);
	}

	void Player::ChangePlayerModel(const wstring& string)
	{
		m_drawComp->SetMultiMeshResource(string);
	}

	void Player::CablesStateCheck()
	{
		auto st = CableStayState::Instance();
		bool isRight = m_cable[0]->GetStateMachine()->IsInState(st);
		bool isLeft = m_cable[1]->GetStateMachine()->IsInState(st);
		if (isLeft && isRight)
		{
			ChangePlayerModel(L"MODEL_PLAYER_DX_NORMAL");
		}
		else if(!isRight && !isLeft)
		{
			ChangePlayerModel(L"MODEL_PLAYER_DX_NO_ARM");
		}
		else if (!isLeft)
		{
			ChangePlayerModel(L"MODEL_PLAYER_DX_NO_LEFT");
		}
		else if (!isRight)
		{
			ChangePlayerModel(L"MODEL_PLAYER_DX_NO_RIGHT");
		}


		
	}

	void Player::OnGameOver(float delay, bool isPause)
	{
		if (isPause)
		{
			auto gameObjects = GetStage()->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				gameObject->SetUpdateActive(false);
				auto lift = dynamic_pointer_cast<Lift>(gameObject);
				if (lift)
				{
					lift->SEStop();
				}
			}
			GetThis<GameObject>()->SetUpdateActive(true);
		}
		if (m_drawComp->GetCurrentAnimation() != L"ANN_DEAD")
		{
			m_drawComp->ChangeCurrentAnimation(L"ANN_DEAD");
		}
		SetStatusFlag(PlayerStatus::isDead, true);
		OnDestory1();
		App::GetApp()->GetScene<Scene>()->BGMStop();

		PostEvent(delay, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");

	}

	void Player::OnEvent(const shared_ptr<Event>& event)
	{
		if (event->m_MsgStr == L"GameOver0")
		{
			OnGameOver(0.0f, false);
		}
		if (event->m_MsgStr == L"GameOver1")
		{
			OnGameOver(1.0f, true);
		}

	}
}
//end basecross

