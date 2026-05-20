/*!
@file MainCamera.cpp
@brief カメラなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MainCamera::OnCreate()
	{
		m_stateMachine.reset(new StateMachine<MainCamera>(GetThis<MainCamera>()));
		m_stateMachine->ChangeState(CameraNormalMoveState::Instance());

		if (!App::GetApp()->GetScene<Scene>()->GetIsFirstStart())
		{
			float rotY = App::GetApp()->GetScene<Scene>()->GetCheckpointRotation().y;
			m_angleY -= rotY;
		}
		SetCursorPos(m_basePoint.x, m_basePoint.y);
	}

	void MainCamera::OnUpdate()
	{
		//注視しているオブジェクトのポインタの確認
		if (m_targetObj.expired())
		{
			return;
		}
		auto targetObj = m_targetObj.lock();
		if (!targetObj)
		{
			return;
		}
		m_stateMachine->Update();
		//NormalMove(true);
		//auto st = CameraNormalMoveState::Instance();
		//if (m_stateMachine->IsInState(st))
		//{
		//	m_distance = m_maxDis;
		//	m_closerdelta = 0;
		//}
		auto player = dynamic_pointer_cast<Player>(targetObj);
		if (player)
		{
			player->SetCameraAngleY(m_angleY + XM_PIDIV2);
		}
	}

	void MainCamera::NormalMove(bool isEditor)
	{
		//注視しているオブジェクトのポインタの確認
		if (m_targetObj.expired())
		{
			return;
		}
		auto targetObj = m_targetObj.lock();
		if (!targetObj)
		{
			return;
		}

		auto& app = App::GetApp();
		auto& device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		float delta = app->GetElapsedTime();

		auto trans = targetObj->GetComponent<Transform>();
		auto targetPos = trans->GetPosition();
		auto point = device.GetKeyState().m_MouseClientPoint;

		if (!device.GetKeyState().m_bPushKeyTbl[VK_CONTROL] && m_isMousePlay && !isEditor)
		{
			m_angleY -= XMConvertToRadians(point.x - m_basePoint.x) / 6.0f;
			m_angleX -= XMConvertToRadians(point.y - m_basePoint.y) / 9.0f;
			SetCursorPos(m_basePoint.x, m_basePoint.y);
		}

		if (isEditor)
		{
			if (device.GetKeyState().m_bPushKeyTbl[VK_RBUTTON])
			{
				m_angleY -= XMConvertToRadians(point.x - m_pastPoint.x) / 6.0f;
				m_angleX -= XMConvertToRadians(point.y - m_pastPoint.y) / 9.0f;
			}
			m_pastPoint = point;
		}

		m_angleY -= XMConvertToRadians(135.0f) * delta * pad.fThumbRX;
		m_angleX += XMConvertToRadians(90.0f) * delta * pad.fThumbRY;
		if (m_angleX >= XM_PI - m_lowerLimit)
		{
			m_angleX = XM_PI - m_lowerLimit;
		}
		if (m_angleX <= m_upperLimit)
		{
			m_angleX = m_upperLimit;
		}
		Vec3 eye = targetPos + Vec3(cosf(m_angleY) * m_distance * sinf(m_angleX), m_distance * cosf(m_angleX), sinf(m_angleY) * m_distance * sinf(m_angleX));
		Vec3 upperVec = Vec3(0.0f, 1.0f, 0.0f);
		auto gaze = targetPos - eye;
		auto cross = Vec3(gaze.y * upperVec.z - gaze.z * upperVec.y, gaze.z * upperVec.x - gaze.x * upperVec.z, gaze.x * upperVec.y - gaze.y * upperVec.x) * -0.1f;
		auto adjustVec = Vec3(0.0f, 1.5f, 0.0f);
		eye += adjustVec + cross;
		auto at = targetPos + adjustVec + cross;
		//eyeとatが重なってしまった時に使う調整用のベクトル
		Vec3 dis = at - eye;
		if (!isEditor)
		{
			CheckAtOverlap(at);
			CheckOverlap(at, eye);
			auto dis = eye - targetPos;
			if (dis.length() < 1.0f)
			{
				targetObj->SetDrawActive(false);
			}
			else
			{
				targetObj->SetDrawActive(true);

			}
		}
		if (eye == at)
		{
			eye = at - (dis * 0.1f);
		}
		SetEye(eye);
		SetAt(at);
	}

	void MainCamera::CloserMove()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		m_distance -= m_closerdelta * delta;
		m_closerdelta += 2 * delta;
		if (m_distance < m_minDis)
		{
			m_distance = m_minDis;
		}
	}

	bool MainCamera::LeaveMove()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		m_distance += m_leavedelta * delta * 10;
		if (m_distance > m_maxDis)
		{
			m_distance = m_maxDis;
			return true;
		}
		return false;
	}

	void MainCamera::InitParameter()
	{
		m_closerdelta = 0;

	}

	void MainCamera::CheckOverlap(Vec3& at, Vec3& eye)
	{
		//カメラがオブジェクトに重ならないようにする
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		Vec3 hitPos; // 当たった時の座標を受け取る用の変数
		//vector<shared_ptr<GameObject>> hitObj; // Hitしたオブジェクトを保存しておく配列
		vector<Vec3> hitPositions; // 当たった座標を保存しておく配列
		for (auto& v : stage->GetGameObjectVec())
		{
			// 無視するオブジェクトかどうかの確認
			auto cannon = dynamic_pointer_cast<Cannon>(v);
			auto player = dynamic_pointer_cast<Player>(v);
			auto sprite = dynamic_pointer_cast<Sprite>(v);
			auto cable = dynamic_pointer_cast<Cable>(v);
			auto enemy = dynamic_pointer_cast<Enemy>(v);
			auto lift = dynamic_pointer_cast<Lift>(v);
			auto frame = dynamic_pointer_cast<Frame>(v);
			auto tip = dynamic_pointer_cast<CableTip>(v);
			auto checkpoint = dynamic_pointer_cast<Checkpoint>(v);
			auto laser = dynamic_pointer_cast<Laser>(v);

			// 着地時のちらつき防止のため
			auto effect = dynamic_pointer_cast<Effect>(v);
			if (cannon || player || sprite || cable || enemy || frame || effect || tip || checkpoint || laser)
			{
				continue;
			}
			//ヒット判定用の終点ベクトルを作る
			Vec3 endPos = eye + (eye - at) * 2.0f;

			// 当たり判定の確認
			bool isLift = lift == nullptr;
			bool isHit = RayHitCheck::HitTest(v, at, endPos, hitPos, isLift);

			//当たっていたら配列に保存
			if (isHit)
			{
				//hitObj.push_back(v);
				hitPositions.push_back(hitPos);
			}
		}
		if (hitPositions.size() > 0)
		{
			auto p = hitPositions[0];
			for (auto& pos : hitPositions)
			{
				auto newDis = at - pos;
				auto nowDis = at - p;
				if (newDis.length() <= nowDis.length())
				{
					p = pos;
					//newDis *= 1.0f / 3.0f;
					eye = at - newDis / 3.0f;
				}
			}
		}
	}

	void MainCamera::CheckAtOverlap(Vec3& at)
	{
		//注視しているオブジェクトのポインタの確認
		if (m_targetObj.expired())
		{
			return;
		}
		auto targetObj = m_targetObj.lock();
		if (!targetObj)
		{
			return;
		}

		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();

		//カメラがオブジェクトに重ならないようにする
		Vec3 hitPosAt;
		vector<Vec3> hitPositionsAt; // 当たった座標を保存しておく配列
		auto targetPos = targetObj->GetComponent<Transform>()->GetPosition();
		targetPos.y += 0.1f;
		Vec3 atEnd = at + (at - targetPos) * 2.0f;
		for (auto& v : stage->GetGameObjectVec())
		{
			// 無視するオブジェクトかどうかの確認
			auto cannon = dynamic_pointer_cast<Cannon>(v);
			auto player = dynamic_pointer_cast<Player>(v);
			auto sprite = dynamic_pointer_cast<Sprite>(v);
			auto cable = dynamic_pointer_cast<Cable>(v);
			auto enemy = dynamic_pointer_cast<Enemy>(v);
			auto lift = dynamic_pointer_cast<Lift>(v);
			auto frame = dynamic_pointer_cast<Frame>(v);
			auto tip = dynamic_pointer_cast<CableTip>(v);
			auto checkpoint = dynamic_pointer_cast<Checkpoint>(v);
			auto laser = dynamic_pointer_cast<Laser>(v);
			// 着地時のちらつき防止のため
			auto effect = dynamic_pointer_cast<Effect>(v);
			if (cannon || player || sprite || cable || enemy || lift || frame || effect || tip || checkpoint || laser)
			{
				continue;
			}

			// 当たり判定の確認
			bool isLift = lift == nullptr;
			bool isHitAt = RayHitCheck::HitTest(v, targetPos, atEnd, hitPosAt, isLift);

			//当たっていたら配列に保存
			if (isHitAt)
			{
				//hitObj.push_back(v);
				hitPositionsAt.push_back(hitPosAt);
			}

		}
		if (hitPositionsAt.size() > 0)
		{
			auto p = hitPositionsAt[0];
			for (auto& pos : hitPositionsAt)
			{
				auto newDis = targetPos - pos;
				auto nowDis = targetPos - p;
				if (newDis.length() <= nowDis.length())
				{
					p = pos;
					//newDis *= 1.0f / 3.0f;
					at = targetPos - newDis / 3.0f;

				}
			}

		}
	}

	bool MainCamera::TargetEnemyMove()
	{
		auto obj = m_targetObj.lock();
		if (!obj)return true;
		auto objTrans = obj->GetComponent<Transform>();
		auto objPos = objTrans->GetPosition();
		auto at = objPos + Vec3(0.0f, 10.0f, 0.0f);
		SetAt(at);
		auto eye = at + Vec3(-20.0f, 0.0f,0.0f);
		SetEye(eye);
		return false;
	}

	void MainCamera::OnEvent(const shared_ptr<Event>& event)
	{
		if (event->m_MsgStr == L"TargetEnemy")
		{
			GetStateMachine()->ChangeState(TargetEnemyCameraState::Instance());
			auto sender = event->m_Sender.lock();
			if (sender)
			{
				auto enemy = dynamic_pointer_cast<GameObject>(sender);
				if (enemy)
				{
					m_targetObj = enemy;
				}
			}
		}
		if (event->m_MsgStr == L"TargetPlayer")
		{
			auto st = TargetEnemyCameraState::Instance();

			if (GetStateMachine()->IsInState(st))
			{
				GetStateMachine()->ChangeState(CameraNormalMoveState::Instance());
				auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");
				SetTargetObject(player);
			}
		}

	}
}
//end basecross

