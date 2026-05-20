#include "stdafx.h"
#include "Project.h"

//-----------------------------------
///ボタンスプライト
//-----------------------------------

namespace basecross
{
	//デストラクタ
	Sprite::~Sprite() {}

	//初期化処理
	void Sprite::OnCreate()
	{
		float HalfSize = 0.5f;	//スプライトの半サイズ
		float HalfSizeX = 2.0f;	//スプライトの半サイズ(X)
		Col4 col = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点配列(短形)
		vector<VertexPositionColorTexture> vertex =
		{
			{VertexPositionColorTexture(Vec3(-HalfSize,HalfSizeX,0),Col4(m_startColor),Vec2(0.0f,0.0f))	},
			{VertexPositionColorTexture(Vec3(HalfSize,HalfSizeX,0),Col4(m_endColor),Vec2(1.0f,0.0f))	},
			{VertexPositionColorTexture(Vec3(-HalfSize,-HalfSizeX,0),Col4(m_startColor),Vec2(0.0f,1.0f))	},
			{VertexPositionColorTexture(Vec3(HalfSize,-HalfSizeX,0),Col4(m_endColor),Vec2(1.0f,1.0f))	},
		};

		vector<uint16_t> indices = { 0,1,2,1,3,2 };

		//アルファブレンド有効化
		SetAlphaActive(m_trace);

		//SetDrawActive(true);

		//トランスフォームコンポーネント
		auto transform = GetComponent<Transform>();
		transform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		transform->SetRotation(0, 0, 0);
		transform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);

		//描画コンポーネント
		auto drawcomp = AddComponent<PCTSpriteDraw>(vertex, indices);
		drawcomp->SetSamplerState(SamplerState::LinearWrap);
		drawcomp->SetTextureResource(m_texture);
	}

	void Sprite::OnUpdate()
	{
		if (m_isSelect)
		{
			SetColor(Col4(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//void Sprite::GuideActiveTrigger(bool LR)
	//{
	//	auto& app = App::GetApp();
	//	auto pad = app->GetInputDevice().GetControlerVec()[0];

	//	int n;
	//	BYTE trigger;
	//	if (LR)
	//	{
	//		n = 0;
	//		trigger = pad.bLeftTrigger;
	//	}
	//	else
	//	{
	//		n = 1;
	//		trigger = pad.bRightTrigger;
	//	}

	//	if (trigger >= 128 && m_pastTrigger[n] < 128)
	//	{
	//		SetColor(m_guideColorActive);
	//	}

	//	if (trigger <= 128 && m_pastTrigger[n] > 128)
	//	{
	//		SetColor(m_guideColor);
	//	}

	//	m_pastTrigger[n] = trigger;
	//}

	void Sprite::OnDestroy()
	{

	}
}