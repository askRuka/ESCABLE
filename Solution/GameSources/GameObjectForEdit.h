/*!
@file Foo.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameObjectForEdit : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameObjectForEdit : public GameObject
	{
	protected:
		Vec3 m_rot;
	public:
		// 構築と破棄
		GameObjectForEdit(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~GameObjectForEdit()
		{
		}

		//virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		void SetMenberRotation(const Vec3& rotation) { m_rot = rotation; }
		Vec3 GetMenberRotation() { return m_rot; }
	};

}
//end basecross
