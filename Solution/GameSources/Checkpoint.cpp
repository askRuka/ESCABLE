/*!
@file Checkpoint.cpp
@brief チェックポイントなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Checkpoint::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		//transComp->SetRotation(m_rotation);
		transComp->SetScale(m_scale);

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		SetDrawActive(false);

		vector<uint16_t> indices;
		vector<VertexPositionNormalTexture> vertices;
		MeshUtill::CreateCube(1.0f, vertices, indices);

		for (auto& v : vertices)
		{
			v.position.z += -1.0f;
		}

		m_rotObj = ObjectFactory::Create<GameObject>(GetStage());
		auto rotDraw = m_rotObj->AddComponent<PNTStaticDraw>();
		rotDraw->CreateOriginalMesh(vertices, indices);
		rotDraw->SetOriginalMeshUse(true);
		auto rotTrans = m_rotObj->GetComponent<Transform>();
		rotTrans->SetPosition(m_position);
		rotTrans->SetRotation(m_rotation);
	}

	//更新
	void Checkpoint::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		if (player)
		{
			auto playerPos = player->GetComponent<Transform>()->GetPosition();
			auto pos = GetComponent<Transform>()->GetPosition();
			auto scale = GetComponent<Transform>()->GetScale();
			auto distance = Vec3(playerPos - pos);
			bool isCheck = abs(distance.x) < scale.x && abs(distance.y) < scale.y && abs(distance.z) < scale.z;
			if (isCheck && !m_isPass)
			{
				GetComponent<PNTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
				App::GetApp()->GetScene<Scene>()->SetCheckpointPos(pos);
				App::GetApp()->GetScene<Scene>()->SetCheckpointRotation(m_rotation);
				m_isPass = true;
			}
		}

	}

	void Checkpoint::OnDraw()
	{
		GameObject::OnDraw();
		m_rotObj->OnDraw();
	}

	void Checkpoint::SetParameter(const Vec3& pos, const Vec3& scale, const Vec3& rot)
	{
		m_position = pos;
		m_scale = scale;
		m_rotation = rot;

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetRotation(Vec3(0));
		transComp->SetScale(m_scale);

		auto rotTrans = m_rotObj->GetComponent<Transform>();
		rotTrans->SetPosition(m_position);
		rotTrans->SetRotation(m_rotation);


	}
}
//end basecross
