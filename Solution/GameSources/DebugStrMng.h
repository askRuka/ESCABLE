/*!
@file DebugStrMng.h
@brief デバッグ用の文字列を管理するクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class DebugStrMng : public GameObject;
	//--------------------------------------------------------------------------------------
	class DebugStrMng : public GameObject
	{
		wstring m_ss;
	public:
		// 構築と破棄
		DebugStrMng(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~DebugStrMng()
		{
		}

		//virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		wstring GetDebugString() { return m_ss; }
		void SetDebugString(const wstring& ss) { m_ss = ss; }
		void AddDebugString(const wstring& ss);
	};

}
//end basecross
