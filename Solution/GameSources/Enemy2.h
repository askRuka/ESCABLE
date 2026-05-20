/*!
@file Enemy2.h
@brief エネミー
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Enemy2 : public GameObjectForEdit;
	//--------------------------------------------------------------------------------------
	class Enemy2 : public GameObjectForEdit
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		vector<Vec3> m_movePositions;
		int m_posNum; // 今現在向かっている座標の番号

		std::shared_ptr<Transform> m_transComp;
	public:
		// 構築と破棄
		Enemy2(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObjectForEdit(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_posNum(0)
		{
		}
		virtual ~Enemy2()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		// オブジェクトを起動する関数
		void BootUP(const Vec3& pos);
		// 動きに関する座標を追加する関数
		void AddMovePosition(const Vec3& pos);
		// 動きに関する座標を変更する関数
		void SetMovePosition(int num, const Vec3& pos);
		// 動きに関する座標を取得する関数
		Vec3 GetMovePosition(int num);
		// 動きに関する座標の配列を取得する関数
		vector<Vec3> GetMovePositionVector();
		// m_posNumを使える範囲にとどめるための調整用の関数
		int AdjustPositionNum(int num);
		// m_movePositionsの要素数を返す関数
		int GetMovePositionsNum() { return m_movePositions.size(); }

	};

}
//end basecross
