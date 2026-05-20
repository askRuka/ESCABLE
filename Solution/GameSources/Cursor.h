/*!
@file Cursor.h
@brief カーソルなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Cursor : public GameObject;
	//--------------------------------------------------------------------------------------
	class Cursor : public GameObject
	{
	public:
		// 構築と破棄
		Cursor(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Cursor()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
