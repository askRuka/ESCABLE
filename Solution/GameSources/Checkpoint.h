/*!
@file Checkpoint.h
@brief チェックポイントなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Checkpoint : public GameObject;
	//--------------------------------------------------------------------------------------
	class Checkpoint : public GameObjectForEdit
	{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		bool m_isPass;
		std::shared_ptr<GameObject> m_rotObj;
	public:
		// 構築と破棄
		Checkpoint(const shared_ptr<Stage>& stage, const Vec3& scale, const Vec3& rotation, const Vec3& position) :
			GameObjectForEdit(stage),
			m_scale(scale),
			m_rotation(rotation),
			m_position(position),
			m_isPass(false)
		{
		}
		virtual ~Checkpoint()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		virtual void OnDraw() override; // 描画
		void SetParameter(const Vec3& pos, const Vec3& scale, const Vec3& rot);
	};

}
//end basecross
