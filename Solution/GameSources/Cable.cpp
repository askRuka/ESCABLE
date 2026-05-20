/*!
@file Cable.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Cable::OnCreate()
	{
		// 線分を構成する2頂点を設定
			// ケーブルの頂点データの作成
		auto endPos = m_endPosition; // 計算部分の終点座標
		auto adjustPos = endPos;
		float texLength = 0;
		float length = m_length - GetRemainingLength(m_startPosition);
		for (auto& pos : m_cablePositions)
		{
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto gaze = camera->GetAt() - camera->GetEye();
			auto dis = endPos - pos;
			if (dis.length() < 0.05f)
			{
				dis = adjustPos - pos;
			}
			else
			{
				adjustPos = endPos;
			}
			auto cross = Vec3(gaze.y * dis.z - gaze.z * dis.y, gaze.z * dis.x - gaze.x * dis.z, gaze.x * dis.y - gaze.y * dis.x);
			cross = cross.normalize() * m_size;
			VertexPositionColorTexture vertice = { endPos - cross, m_startColor, Vec2(texLength / length,1) };
			m_vertices.push_back(vertice);
			vertice = { endPos + cross, m_startColor, Vec2(texLength / length, 0) };
			m_vertices.push_back(vertice);
			endPos = pos;
			texLength += Vec3(endPos - pos).length();
		}
		auto camera = GetStage()->GetView()->GetTargetCamera();
		auto gaze = camera->GetAt() - camera->GetEye();
		auto dis = endPos - m_startPosition;
		auto cross = Vec3(gaze.y * dis.z - gaze.z * dis.y, gaze.z * dis.x - gaze.x * dis.z, gaze.x * dis.y - gaze.y * dis.x);
		cross = cross.normalize() * m_size;
		VertexPositionColorTexture vertice = { endPos - cross, m_startColor, Vec2(texLength / length,1) };
		m_vertices.push_back(vertice);
		vertice = { endPos + cross, m_startColor, Vec2(texLength / length ,0) };
		m_vertices.push_back(vertice);
		texLength += dis.length();

		vertice = { m_startPosition - cross,m_startColor, Vec2(texLength / length ,1) };
		m_vertices.push_back(vertice);
		vertice = { m_startPosition + cross,m_startColor, Vec2(texLength / length,0) };
		m_vertices.push_back(vertice);


		//m_vertices = {
		//	{m_startPosition + a, m_startColor, Vec2(0,0)}, {m_startPosition + b, m_startColor, Vec2(0,0)},
		//	{m_cablePositions[9] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[9]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[8] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[8]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[7] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[7]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[6] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[6]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[5] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[5]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[4] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[4]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[3] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[3]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[2] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[2]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[1] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[1]+ b, m_endColor, Vec2(0.0)},
		//	{m_cablePositions[0] + a, m_endColor, Vec2(0.0)}, {m_cablePositions[0]+ b, m_endColor, Vec2(0.0)},
		//	{m_endPosition + a, m_endColor, Vec2(0.0)}, {m_endPosition + b, m_endColor, Vec2(0.0)},

		//};

		// 始点と終点をつなぐようにインデックスを設定
		m_indices = {
			0, 2, 1,
			1, 2, 3,
			2, 4, 3,
			3, 4, 5,
			4, 6, 5,
			5, 6, 7,
			6, 8, 7,
			7, 8, 9,
			8, 10,9,
			9, 10,11,
			10,12,11,
			11,12,13,
			12,14,13,
			13,14,15,
			14,16,15,
			15,16,17,
			16,18,17,
			17,18,19,
			18,20,19,
			19,20,21,
			20,22,21,
			21,22,23,
		};

		// ドローコンポーネントを設定
		m_draw = AddComponent<PCTStaticDraw>(); // 位置と色のみを持つ頂点からなるドローコンポーネント（テクスチャは貼らない）
		m_draw->SetOriginalMeshUse(true); // プログラム内で自作したメッシュを使用する
		m_draw->CreateOriginalMesh(m_vertices, m_indices); // 頂点データとインデックスデータを元にメッシュを自作する
		m_draw->SetTextureResource(L"TEX_Cabel");
		m_draw->SetSamplerState(SamplerState::LinearWrap);//テクスチャを繰り返す設定
		SetAlphaActive(true);
		m_draw->SetDepthStencilState(DepthStencilState::Read);
		m_draw->SetRasterizerState(RasterizerState::DoubleDraw);
		//auto meshResource = m_draw->GetMeshResource(); // メッシュリソースを取得し、プリミティブトポロジー(頂点の利用方法)を変更する
		//meshResource->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); // ポリゴンではなく稜線を表示する設定
		
		//ステートマシンの構築
		m_stateMachine.reset(new StateMachine<Cable>(GetThis<Cable>()));
		m_stateMachine->ChangeState(CableStayState::Instance());

		// ケーブルの先端部分のオブジェクトの作成
		//m_cableTip = GetStage()->AddGameObject<CableTip>();

	}

	void Cable::OnUpdate()
	{
		//ステートマシンの更新
		m_stateMachine->Update();
		//現在のプレイヤーの位置からケーブルの開始座標を更新
		//auto player = dynamic_pointer_cast<Player>(m_player.lock());
		//if (player)
		//{
		//	m_startPosition = player->GetComponent<Transform>()->GetPosition() + player->GetArmPos(m_LR);
		//}

		// プレイヤーの腕の位置を調べる
		auto playerDraw = m_playerDraw.lock();
		if (playerDraw)
		{
			auto matrix = playerDraw->GetBoneWorldMatrix(m_armBoneName);
			Mat4x4 offsetMatrix;
			//offsetMatrix.affineTransformation(
			//	Vec3(0.2f), // スケール
			//	Vec3(0.0f), // 回転の中心
			//	Vec3(0.0f), // XYZ軸回転
			//	Vec3(0.0f)); // 平行移動
			//
			//matrix = offsetMatrix * matrix; // どうしても必要な場合のみオフセット行列を掛ける

			m_startPosition = matrix.transInMatrix();
		}
		AdjustCablePosition();
		MoveCollidePosition();
		SetCablePosition();
		GuideCheck();
		//m_cableTip->GetComponent<Transform>()->SetPosition(m_endPosition);
		//m_cableTip->SetDrawActive(GetDrawActive());

	}

	void Cable::SetPlayer(const shared_ptr<GameObject>& player)
	{
		m_player = player;
	}


	bool Cable::HitCheck()
	{
		//カメラの向いている方向と開始地点から判定を確認
		auto camera = GetStage()->GetView()->GetTargetCamera();
		Vec3 eye = camera->GetEye();
		Vec3 startPos = eye;
		Vec3 distance = Vec3(camera->GetAt() - eye).normalize();
		float per = 1.0f / (1.0f + abs(distance.y * m_upAttenuation));
		Vec3 endPos = eye + (distance * m_throwLength * per);
		Vec3 hitPos; // 当たった時の座標を受け取る用の変数
		vector<shared_ptr<GameObject>> hitObj; // Hitしたオブジェクトを保存しておく配列
		vector<Vec3> hitPositions; // 当たった座標を保存しておく配列
		for (auto& v : GetStage()->GetGameObjectVec())
		{
			auto player = dynamic_pointer_cast<Player>(v);
			auto cable = dynamic_pointer_cast<Cable>(v);
			auto enemy = dynamic_pointer_cast<Enemy>(v);
			auto effect = dynamic_pointer_cast<Effect>(v);
			auto cannon = dynamic_pointer_cast<Cannon>(v);
			auto laser = dynamic_pointer_cast<Laser>(v);
			auto obstacle = dynamic_pointer_cast<ObstacleForCamera>(v);

			if (player || cable || enemy || effect || cannon || laser || obstacle)
			{
				continue;
			}

			// 当たり判定の確認
			bool isHit = RayHitCheck::HitTest(v, startPos, endPos, hitPos);

			//当たっていたら配列に保存
			if (isHit)
			{
				hitObj.push_back(v);
				hitPositions.push_back(hitPos);
			}


		}
		//判定がとられた座標から最も開始地点から近い場所をHitPositionにする
		if (hitPositions.size() > 0)
		{
			m_hitPosition = hitPositions[0];
			shared_ptr<GameObject> selectObj = hitObj[0];

			for (int i = 0; i < hitPositions.size(); i++)
			{
				auto newDis = startPos - hitPositions[i];
				auto nowDis = startPos - m_hitPosition;
				if (newDis.length() < nowDis.length())
				{
					m_hitPosition = hitPositions[i];
					selectObj = hitObj[i];
				}
			}

			if (selectObj)
			{
				auto consent = dynamic_pointer_cast<Consent>(selectObj);
				auto trigger = dynamic_pointer_cast<ElectricTrigger>(selectObj);
				if (consent || trigger)
				{
					m_hitObj = selectObj;
					m_hitPosition = selectObj->GetComponent<Transform>()->GetPosition();
					//m_hitPosition = CalcHitPosition();
					return true;
				}
			}

		}
		else // 当たってなかったら判定の端を取る
		{
			m_hitPosition = endPos;
		}

		return false;
	}

	bool Cable::OnThrow(const Vec3& throwPos)
	{
		m_isHit = HitCheck();
		auto distance = m_hitPosition - throwPos;
		m_moveVelocity = distance.normalize();
		for (auto& cablePos : m_cablePositions)
		{
			cablePos = throwPos;
		}
		m_startPosition = throwPos;
		m_endPosition = throwPos;
		SetCablePosition();
		m_stateMachine->ChangeState(CableThrowMoveState::Instance());
		return m_isHit;
	}

	bool Cable::ThrowMove()
	{
		//m_cablePositions[0] = m_startPosition;
		auto delta = App::GetApp()->GetElapsedTime();
		m_endPosition += m_moveVelocity * delta * 100;
		SetCablePosition();
		auto seDis = m_endPosition - m_startPosition; // スタート座標からエンド座標の距離
		auto shDis = m_hitPosition - m_startPosition; // スタート座標からヒット座標の距離
		AdjustCablePosition();
		if (seDis.length() >= shDis.length())
		{
			m_endPosition = m_hitPosition;
			return true;
		}
		return false;
	}

	bool Cable::BackMove()
	{
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				if (Vec3(m_endPosition - m_cablePositions[i]).length() < 1.0f)
				{
					m_endPosition = m_cablePositions[i];
					m_isCollide[i] = false;
				}
				BackMoveInit();

				break;

			}
			for (int j = 0; j < i - 1; j++)
			{
				m_cablePositions[j] = m_endPosition;
			}

		}

		//m_cablePositions[0] = m_startPosition;
		//for (auto& b : m_isCollide)
		//{
		//	b = false;
		//}
		auto delta = App::GetApp()->GetElapsedTime();
		m_endPosition += m_moveVelocity * delta * 100;
		SetCablePosition();
		bool isCollide = false;
		for (auto& b : m_isCollide)
		{
			isCollide = b || isCollide;
		}
		auto heDis = m_endPosition - m_hitPosition; // ヒット座標からエンド座標の距離
		auto shDis = m_hitPosition - m_startPosition; // スタート座標からエンド座標の距離
		AdjustCablePosition();
		if (heDis.length() >= shDis.length() && !isCollide)
		{
			return true;
		}
		return false;
	}
	void Cable::BackMoveInit()
	{
		auto endPos = m_endPosition;
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				auto distanse = m_cablePositions[i] - endPos;
				m_moveVelocity = distanse.normalize();
				return;
			}
			else
			{
				endPos = m_cablePositions[i];
				m_cablePositions[i] = m_endPosition;
			}
		}

		auto player = dynamic_pointer_cast<Player>(m_player.lock());
		if (player)
		{
			auto distanse = player->GetComponent<Transform>()->GetPosition() + player->GetArmPos(m_LR) - m_endPosition;
			m_moveVelocity = distanse.normalize();
		}
	}

	shared_ptr<GameObject> Cable::GetHitObject()
	{
		auto hitObj = m_hitObj.lock();
		if (hitObj)return hitObj;
		return nullptr;
	}

	void Cable::ResetHitObj()
	{
		auto hitObj = m_hitObj.lock();
		if (hitObj)
		{
			auto trigger = dynamic_pointer_cast<ElectricTrigger>(hitObj);
			if (trigger)
			{
				trigger->SetIsCharging(false);
			}
		}
		m_hitObj.reset();
	}

	void Cable::ChangePlayerStatus(int status, bool b)
	{
		auto player = dynamic_pointer_cast<Player>(m_player.lock());
		if (player)
		{
			auto s = (PlayerStatus)(status);
			player->SetStatusFlag(s, b);
		}
	}

	void Cable::PlayerCheckStatus()
	{
		auto player = dynamic_pointer_cast<Player>(m_player.lock());
		if (player)
		{
			player->PlagInCheck();
		}

	}

	void Cable::CheckCollide()
	{
		auto startPos = m_startPosition;
		auto endPos = m_endPosition;

		//開始地点から終了地点の判定を確認
		for (int i = 0; i < m_cablePosNum; i++)
		{
			Vec3 hitPos; // 当たった時の座標を受け取る用の変数
			vector<shared_ptr<GameObject>> hitObj; // Hitしたオブジェクトを保存しておく配列
			vector<Vec3> hitPositions; // 当たった座標を保存しておく配列
			if (i < m_cablePosNum - 1)
			{
				if (m_isCollide[i + 1])
				{
					endPos = m_cablePositions[i];
					continue;
				}
			}
			for (auto& v : GetStage()->GetGameObjectVec())
			{
				//ステージからオブジェクトの配列を受け取りそれぞれの判定をする
				TRIANGLE triangle;
				size_t triangleIndex;
				//ヒット判定をとらないオブジェクトを除外する
				auto player = dynamic_pointer_cast<Player>(v);
				auto consent = dynamic_pointer_cast<Consent>(v);
				auto cable = dynamic_pointer_cast<Cable>(v);
				auto frame = dynamic_pointer_cast<Frame>(v);
				auto trigger = dynamic_pointer_cast<ElectricTrigger>(v);
				auto laser = dynamic_pointer_cast<Laser>(v);
				auto enemy = dynamic_pointer_cast<Enemy>(v);
				auto effect = dynamic_pointer_cast<Effect>(v);
				auto cannon = dynamic_pointer_cast<Cannon>(v);
				auto tip = dynamic_pointer_cast<CableTip>(v);
				auto lift = dynamic_pointer_cast<Lift>(v);
				auto obstacle = dynamic_pointer_cast<ObstacleForCamera>(v);

				if (player || consent || cable || trigger || laser || enemy || effect || cannon || tip || obstacle)
				{
					continue;
				}

				// 当たり判定の確認
				bool isLift = lift == nullptr && frame == nullptr;
				bool isHit = RayHitCheck::HitTest(v, startPos, endPos, hitPos, isLift);

				//当たっていたら配列に保存
				if (isHit)
				{
					if (Vec3(hitPos - endPos).length() > 1.0f && Vec3(hitPos - startPos).length() > 0.5f)
					{
						hitObj.push_back(v);
						auto adjustVec = hitPos - v->GetComponent<Transform>()->GetPosition();
						hitPositions.push_back(hitPos + (adjustVec.normalize() * m_size));
					}
				}

			}

			//判定がとられた座標から最も開始地点から近い場所をHitPositionにする
			if (hitPositions.size() > 0)
			{
				if (m_isCollide[i])
				{
					endPos = m_cablePositions[i];
					continue;
				}
				m_cablePositions[i] = hitPositions[0];
				for (int j = 0; j < hitPositions.size(); j++)
				{
					auto newDis = startPos - hitPositions[j];
					auto nowDis = startPos - m_cablePositions[i];
					if (newDis.length() <= nowDis.length())
					{
						m_cablePositions[i] = hitPositions[j];
						m_isCollide[i] = true;
						m_collisionObject[i] = hitObj[j];
						m_collisionObjPos[i] = hitObj[j]->GetComponent<Transform>()->GetPosition();
					}
					auto a = Vec3(m_hitPosition - m_cablePositions[i]).length();
					if (Vec3(endPos - m_cablePositions[i]).length() < 1.0f)
					{
						m_cablePositions[i] = startPos;
						m_isCollide[i] = false;

					}
				}
				if (m_isCollide[i])
				{
					endPos = m_cablePositions[i];
				}
			}
			else // 当たってなかったら判定の端を取る
			{
				if (m_isCollide[i])
				{
					auto colObj = m_collisionObject[i].lock();
					if (colObj)
					{
						//Vec3 middlePos = (endPos - startPos) / 2.0f + startPos;

						Vec3 cableVec = m_endPosition - m_startPosition;
						Vec3 partVec = m_startPosition - m_cablePositions[i];
						Vec3 checkPos;

						float t = -((cableVec.x * partVec.x) + (cableVec.y * partVec.y) + (cableVec.z * partVec.z));
						if (t < 0)
						{
							checkPos = m_startPosition;
						}
						else if (t > cableVec.length() * cableVec.length())
						{
							checkPos = m_endPosition;
						}
						else
						{
							checkPos = m_startPosition + (cableVec * (t / (cableVec.length() * cableVec.length())));
						}

						Vec3 objPos = colObj->GetComponent<Transform>()->GetPosition();

						//float dis1 = Vec3(checkPos - objPos).length();
						//float dis2 = Vec3(checkPos - m_cablePositions[i]).length();
						Vec3 hit;
						bool isHit = RayHitCheck::HitTest(colObj, m_cablePositions[i], checkPos, hit, false);

						if (isHit)
						{
							continue;
						}
					}
				}
				m_cablePositions[i] = startPos;
				m_isCollide[i] = false;
			}
			SetCablePosition();
			if (!m_isCollide[i])
			{
				break;
			}
		}
	}

	void Cable::AdjustCablePosition()
	{
		Vec3 adjustPos = m_endPosition;
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (!m_isCollide[i])
			{
				m_cablePositions[i] = adjustPos;
			}
			else
			{
				adjustPos = m_cablePositions[i];
			}
		}
	}

	bool Cable::ChackLength(const Vec3& pos)
	{
		auto startPos = pos;
		auto endPos = m_endPosition;
		float lengthSum = 0;
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				lengthSum += Vec3(endPos - m_cablePositions[i]).length();
				endPos = m_cablePositions[i];
			}
			else
			{
				lengthSum += Vec3(endPos - startPos).length();
				break;
			}
		}
		if (lengthSum >= m_length)
		{
			return true;
		}
		return false;
	}

	void Cable::StateSendToTrigger()
	{
		auto hitObj = m_hitObj.lock();
		auto lockObj = m_player.lock();
		if (hitObj && lockObj)
		{
			auto trigger = dynamic_pointer_cast<ElectricTrigger>(hitObj);
			auto player = dynamic_pointer_cast<Player>(lockObj);
			if (trigger && player)
			{
				//trigger->SetTrigger(player->GetStatusFlag(PlayerStatus::isCharging));
				trigger->SetIsCharging(player->GetStatusFlag(PlayerStatus::isCharging));
			}
		}
	}

	float Cable::GetRemainingLength(const Vec3& pos)
	{
		auto startPos = pos;
		auto endPos = m_endPosition;
		float lengthSum = 0;
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				lengthSum += Vec3(endPos - m_cablePositions[i]).length();
				endPos = m_cablePositions[i];
			}
			else
			{
				lengthSum += Vec3(endPos - startPos).length();
				break;
			}
		}
		return m_length - lengthSum;
	}

	Vec3 Cable::GetCableDirection()
	{
		Vec3 endPos = m_endPosition;
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				endPos = m_cablePositions[i];
			}
			else
			{
				break;
			}
		}
		return Vec3(endPos - m_startPosition).normalize();
	}

	void Cable::MoveCollidePosition()
	{
		for (int i = 0; i < m_cablePosNum; i++)
		{
			if (m_isCollide[i])
			{
				auto colObj = m_collisionObject[i].lock();
				if (colObj)
				{
					auto colPos = colObj->GetComponent<Transform>()->GetPosition();
					auto moveVec = colPos - m_collisionObjPos[i];
						m_cablePositions[i] += moveVec;
					m_collisionObjPos[i] = colPos;
				}
			}
			else
			{
				m_collisionObject[i].reset();
			}

		}
	}

	Vec3 Cable::CalcHitPosition()
	{
		if (m_hitObj.expired()) return Vec3(0);
		auto hitObj = m_hitObj.lock();
		if (!hitObj) return Vec3(0);
		auto consent = dynamic_pointer_cast<Consent>(hitObj);
		auto trigger = dynamic_pointer_cast<ElectricTrigger>(hitObj);
		//if (!consent && !trigger) return Vec3(0);
		
		if (consent)
		{
			auto consentTrans = consent->GetComponent<Transform>();
			auto consentPos = consentTrans->GetPosition();
			auto consentRot = consent->GetMenberRotation();
			float length = 0.5f;
			consentPos += Vec3(-sinf(consentRot.y) * length, 0.0f, -cosf(consentRot.y) * length);
			return consentPos;
		}

		if (trigger)
		{
			auto triggerTrans = trigger->GetComponent<Transform>();
			auto triggerPos = triggerTrans->GetPosition();
			auto triggerRot = trigger->GetMenberRotation();
			float length = 2.0f;
			triggerPos += Vec3(-sinf(triggerRot.y) * length, 0.0f, -cosf(triggerRot.y) * length);
			return triggerPos;
		}

	}

	void Cable::TipMove()
	{
		m_cableTip->GetComponent<Transform>()->SetPosition(m_endPosition);
		auto dis = m_endPosition - m_startPosition;
		dis.normalize();
		Vec3 rot = Vec3(0.0f, atan2f(dis.x, dis.z), 0.0f);
		auto cableTip = dynamic_pointer_cast<CableTip>(m_cableTip);
		cableTip->SetTipRotation(rot);
	}
	void Cable::TipState()
	{
		if (m_hitObj.expired()) return;
		auto hitObj = m_hitObj.lock();
		if (!hitObj) return;
		auto consent = dynamic_pointer_cast<Consent>(hitObj);
		auto trigger = dynamic_pointer_cast<ElectricTrigger>(hitObj);
		//if (!consent && !trigger) return Vec3(0);

		if (consent)
		{
			auto consentTrans = consent->GetComponent<Transform>();
			auto consentPos = consentTrans->GetPosition();
			auto consentRot = consent->GetMenberRotation();
			float length = 1.0f;
			consentPos += Vec3(-sinf(consentRot.y) * length, 0.0f, -cosf(consentRot.y) * length);
			auto cableTip = dynamic_pointer_cast<CableTip>(m_cableTip);
			cableTip->SetTipPosition(consentPos);
			cableTip->SetTipRotation(-consentRot);
		}

		if (trigger)
		{
			auto triggerTrans = trigger->GetComponent<Transform>();
			auto triggerPos = triggerTrans->GetPosition();
			auto triggerRot = trigger->GetMenberRotation();
			float length = 2.0f;
			triggerPos += Vec3(-sinf(triggerRot.y) * length, 0.0f, -cosf(triggerRot.y) * length);
			auto cableTip = dynamic_pointer_cast<CableTip>(m_cableTip);
			cableTip->SetTipPosition(triggerPos);
			cableTip->SetTipRotation(-triggerRot);

		}
	}

	void Cable::SEStart(const wstring& name)
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		m_SE = XAMng->Start(name, 0, App::GetApp()->GetScene<Scene>()->m_volumeSE);
	}
	void Cable::SEStop()
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		XAMng->Stop(m_SE);
	}

	void Cable::GuideCheck()
	{
		// 照準の獲得
		auto guide = GetStage()->GetSharedGameObject<Sprite>(L"Guide");
		guide->SetUpdateActive(false);

		//カメラの向いている方向と開始地点から判定を確認
		auto camera = GetStage()->GetView()->GetTargetCamera();
		Vec3 eye = camera->GetEye();
		Vec3 startPos = eye;
		Vec3 distance = Vec3(camera->GetAt() - eye).normalize();
		float per = 1.0f / (1.0f + abs(distance.y * m_upAttenuation));
		Vec3 endPos = eye + (distance * m_throwLength * per);
		Vec3 hitPos; // 当たった時の座標を受け取る用の変数
		vector<Vec3> hitPositions; // 当たった座標を保存しておく配列
		for (auto& v : GetStage()->GetGameObjectVec())
		{

			auto consent = dynamic_pointer_cast<Consent>(v);
			auto trigger = dynamic_pointer_cast<ElectricTrigger>(v);

			// 当たり判定の確認
			bool isHit = false;
			if (consent || trigger)
			{
				isHit = RayHitCheck::HitTest(v, startPos, endPos, hitPos);
			}
			//当たっていたら配列に保存
			if (isHit)
			{
				//hitObj.push_back(v);
				hitPositions.push_back(hitPos);
			}


		}
		//判定がとられた座標から最も開始地点から近い場所をHitPositionにする
		if (hitPositions.size() > 0)
		{
			guide->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			//Vec3 hitPosition;
			//hitPosition = hitPositions[0];

			//for (int i = 0; i < hitPositions.size(); i++)
			//{
			//	auto newDis = startPos - hitPositions[i];
			//	auto nowDis = startPos - hitPosition;
			//	if (newDis.length() < nowDis.length())
			//	{
			//		hitPosition = hitPositions[i];
			//	}
			//}
		}
		else
		{
			guide->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.3f));
		}

	}
}
//end basecross
