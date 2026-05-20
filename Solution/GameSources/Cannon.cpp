/*!
@file Floor.cpp
@brief ポーズ画面制御
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Cannon::OnCreate()
	{
		InitDrawComp();
		InitTransComp();

		//ステートマシンの構築
		m_stateMachine.reset(new StateMachine<Cannon>(GetThis<Cannon>()));
		m_stateMachine->ChangeState(LaserOnState::Instance());
	}

	void Cannon::OnUpdate()
	{
		m_stateMachine->Update();
	}

	void Cannon::OnBillboard()
	{
		auto stage = GetStage();
		auto camera = stage->GetView()->GetTargetCamera();
		auto viewMatrix = camera->GetViewMatrix();
		Quat viewQuat(viewMatrix);
		viewQuat.x *= -1.0f;
		viewQuat.y *= -1.0f;
		viewQuat.z *= -1.0f;
		m_transComp->SetQuaternion(viewQuat);
	}

	void Cannon::SetLaserActive(bool active)
	{
		SetDrawActive(active);
	}

	void Cannon::ActiveTimer()
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_time += delta;
	}

	void Cannon::LaserOn()
	{

		m_stateMachine->ChangeState(LaserOnState::Instance());
	}

	void Cannon::LaserOff()
	{
		m_stateMachine->ChangeState(LaserOffState::Instance());
	}

	void Cannon::InitDrawComp()
	{
		//m_difference = m_endPos - m_startPos;
		//m_direction = m_difference.normalize();

		Col4 col = Col4(1.0f, 0.0f, 0.0f, 1.0f);

		m_vertices = {
			{m_startPos,col},
			{m_endPos,col}
		};

		m_indices = {
			0, 1
		};

		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->SetOriginalMeshUse(true);

		m_drawComp->CreateOriginalMesh(m_vertices, m_indices);

		auto meshResource = m_drawComp->GetMeshResource();
		meshResource->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		m_drawComp->SetDiffuse(col);
		m_drawComp->SetEmissive(col);

		m_drawComp->UpdateVertices(m_vertices);
	}

	void Cannon::InitTransComp()
	{
		m_transComp = GetComponent<Transform>();

		m_transComp->SetPosition(0, 0, 0);
			//(m_startPos.x, m_startPos.y, m_startPos.z);
		m_transComp->SetRotation(0, 0, 0);
		m_transComp->SetScale(Vec3(1.0f, 1.0f, 1.0f));
	}
}