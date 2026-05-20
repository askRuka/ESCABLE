#pragma once
#include "stdafx.h"

namespace basecross
{
	class Cannon :public GameObject
	{
		shared_ptr<PNTStaticDraw> m_drawComp;	//描画コンポーネント
		shared_ptr<Transform> m_transComp;		//トランスコンポーネント

		std::vector<VertexPositionColor> m_vertices;
		std::vector<uint16_t> m_indices;

		std::unique_ptr<StateMachine<Cannon>> m_stateMachine; // ステートマシン

	private:
		wstring m_texture;

		//Vec3 m_pos;		//位置を表すベクトル
		Vec3 m_startPos;	//開始位置
		Vec3 m_endPos;		//終了位置

		//Vec3 m_difference;	//始点と終点の差異
		//Vec3 m_direction;	//線分の向き

		Vec3 m_forward;	//前方向を現すベクトル


	public:
		float m_time;
		Cannon(const shared_ptr<Stage>& stage,
			const Vec3 startPos, const Vec3 endPos) :
			GameObject(stage),
			m_startPos(startPos),
			m_endPos(endPos),
			//m_difference(0),
			//m_direction(0),
			m_forward(Vec3(0, 0, -1)),	//前方向に合わせておく
			m_time(0)
		{
		}

		virtual ~Cannon() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnBillboard();

		void SetLaserActive(bool active);
		void ActiveTimer();

		void SetTime(float time) { m_time = time; }
		float GetTime() { return m_time; }

		void LaserOn();
		void LaserOff();

	private:
		void InitDrawComp();
		void InitTransComp();
	};
}