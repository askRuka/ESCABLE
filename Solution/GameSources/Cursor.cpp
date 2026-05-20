/*!
@file Cursor.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Cursor::OnCreate()
	{
		Col4 col = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		vector<VertexPositionColorTexture> vertex =
		{
			{Vec3( 0,   0, 0), col, Vec2(0.0f, 0.0f)},
			{Vec3(50,   0, 0), col, Vec2(1.0f, 0.0f)},
			{Vec3( 0, -50, 0), col, Vec2(0.0f, 1.0f)},
			{Vec3(50, -50, 0), col, Vec2(1.0f, 1.0f)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			1,3,2
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertex, indices);
		//drawComp->SetDiffuse(col);
		//drawComp->SetEmissive(col);
		drawComp->SetTextureResource(L"TEX_CURSOR");
		SetAlphaActive(true);
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(0.5f));
		SetDrawLayer(10);
	}

	// 更新
	void Cursor::OnUpdate()
	{
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto point = keyState.m_MouseClientPoint;

		auto transComp = GetComponent<Transform>();
		point.x *= (2.0f / 3.0f);
		point.y *= (2.0f / 3.0f);
		transComp->SetPosition(Vec3(point.x - 640, -point.y + 360, 0));
	}
}
//end basecross
