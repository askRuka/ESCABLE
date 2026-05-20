#pragma once
#include "stdafx.h"

namespace basecross {

	class GameOverSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		wstring m_TextureKey;
		//トータル時間
		float m_TotalTime;
		//選択されているかどうか
		bool m_Selected;
	public:
		GameOverSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos);
		//破棄
		virtual ~GameOverSprite();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;
		//アクセサ
		bool IsSelect() const {
			return m_Selected;
		}
		void SetSelect(bool b) {
			m_Selected = b;
			m_TotalTime = 0.0f;
		}
	};
}
