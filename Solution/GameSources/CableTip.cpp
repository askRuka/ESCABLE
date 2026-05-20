/*!
@file CableTip.cpp
@brief 第2ステージ用のエネミーの経路を指定するエディター用オブジェクト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void CableTip::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		drawComp->SetEmissive(Col4(0.5f, 0.5f, 0.0f, 1.0f));

		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(Vec3(0.5f, 0.5f, 0.5f));
	}

	void CableTip::OnUpdate()
	{

	}

	void CableTip::SetTipRotation(const Vec3& rot)
	{
		m_transComp->SetRotation(rot);
		m_behind = Vec3(-sinf(rot.y) * m_length, 0.0f, -cosf(rot.y) * m_length);
	}

	void CableTip::SetTipPosition(const Vec3& pos)
	{
		m_transComp->SetPosition(pos);
	}

}
//end basecross
