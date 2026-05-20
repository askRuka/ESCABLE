#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject
	{
		wstring m_texture;
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;

		//BYTE m_pastTrigger[2];

		Col4 m_startColor = Col4(0, 0, 0, 1.0f);
		Col4 m_endColor = Col4(0, 0, 0, 1.0f);

		Col4 m_neutralColor = Col4(0.75f, 0.75f, 0.75f, 1.0f);
		Col4 m_selectColor = Col4(1.0f, 1.0f, 0.0f, 1.0f);

		Col4 m_guideColor = Col4(1.0f, 1.0f, 1.0f, 0.15f);
		Col4 m_guideColorActive = Col4(1.0f, 1.0f, 1.0f, 0.45f);

		bool m_isSelect;

	public:
		Sprite::Sprite(const shared_ptr<Stage>&
			Stage, const wstring& Texture, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos,
			const Col4 StartColor,const Col4 EndColor) :
			GameObject(Stage),
			m_texture(Texture),
			m_trace(Trace),
			m_startScale(StartScale),
			m_startPos(StartPos),
			m_startColor(StartColor),
			m_endColor(EndColor),
			m_isSelect(false)
		{
		}

		//デストラクタ
		virtual ~Sprite();

		//初期化処理
		virtual void OnCreate()override;
		//更新処理
		virtual void OnUpdate()override;

		void SetColor(Col4 color)
		{
			GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
		}

		void SetSelected(bool select)
		{
			m_isSelect = select;
		}

		//void GuideActiveTrigger(bool LR);

		//削除処理
		virtual void OnDestroy()override;
	};
}
