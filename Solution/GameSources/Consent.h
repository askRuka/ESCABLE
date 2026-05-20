/*!
@file Consent.h
@brief コンセント
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Consent : public GameObject;
	//--------------------------------------------------------------------------------------
	class Consent : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<PNTStaticModelDraw> m_drawComp;

	public:
		// 構築と破棄
		Consent(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position)
		{
		}
		virtual ~Consent()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		void InitDrawComp();

	};

}
//end basecross
