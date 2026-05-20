/*!
@file ObstacleForCamera.cpp
@brief ’ŒÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//‰Šú‰»
	void ObstacleForCamera::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);
		transComp->SetPosition(m_position);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		//drawComp->SetRasterizerState(RasterizerState::Wireframe);
		drawComp->SetBlendState(BlendState::AlphaBlend);
		SetDrawActive(false);

	}

}
//end basecross
