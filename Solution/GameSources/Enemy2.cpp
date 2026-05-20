/*!
@file Enemy2.cpp
@brief エネミー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Enemy2::OnCreate()
	{
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(m_Scale);
		m_transComp->SetRotation(m_Rotation);
		m_transComp->SetPosition(m_Position);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		SetUpdateActive(false);
		SetDrawActive(false);

		// 仮の座標入力
		for (int i = 0; i < 5; i++)
		{
			AddMovePosition(Vec3((float)i));
		}
		BootUP(Vec3(-1.0f));
	}

	void Enemy2::OnUpdate()
	{
		if (m_movePositions.size() < 2) return;

		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = m_transComp->GetPosition();
		auto dir = m_movePositions[m_posNum] - pos;
		pos += dir.normalize() * delta;
		m_transComp->SetPosition(pos);
		int num = AdjustPositionNum(m_posNum - 1);
		auto dis1 = m_movePositions[num] - pos;
		auto dis2 = m_movePositions[num] - m_movePositions[m_posNum];
		if (dis1.length() > dis2.length())
		{
			int nextNum = AdjustPositionNum(m_posNum + 1);
			if (m_posNum == nextNum)
			{
				SetUpdateActive(false);
			}
			m_posNum = nextNum;
		}
	}

	void Enemy2::BootUP(const Vec3& pos)
	{
		m_transComp->SetPosition(pos);
		SetUpdateActive(true);
		SetDrawActive(true);
	}
	void Enemy2::AddMovePosition(const Vec3& pos)
	{
		m_movePositions.push_back(pos);
	}
	void Enemy2::SetMovePosition(int num, const Vec3& pos)
	{
		if (num < m_movePositions.size())
		{
			m_movePositions[num] = pos;
		}
	}
	Vec3 Enemy2::GetMovePosition(int num)
	{
		if (num < m_movePositions.size())
		{
			return m_movePositions[num];
		}
		return Vec3(0);
	}
	vector<Vec3> Enemy2::GetMovePositionVector()
	{
		return m_movePositions;
	}

	int Enemy2::AdjustPositionNum(int num)
	{
		if (num < 0)
		{
			num = 0;
		}
		if (num >= m_movePositions.size())
		{
			num = m_movePositions.size() - 1;
		}
		return num;
	}

}
//end basecross
