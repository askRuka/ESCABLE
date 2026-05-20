#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Lift::Lift(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const Vec3& Velocity
	) :
		GameObjectForEdit(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Velocity(Velocity),
		m_Lift(true),
		m_backDelay(5.0f),
		m_delayTime(5.0f)
	{
	}
	Lift::~Lift() {}

	//‰Šú‰»
	void Lift::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBBÕ“Ëj”»’è‚ğ•t‚¯‚é
		//ƒAƒNƒVƒ‡ƒ“‚Ì“o˜^
		//‰e‚ğ‚Â‚¯‚é
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"MODEL_FLOOR");
		//•`‰æˆ—
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_FLOOR");

		m_Frame = GetStage()->AddGameObject<Frame>(m_Scale, m_Rotation, m_Position);
	}
	void Lift::SetLift(bool b) { m_Lift = b; }

	void Lift::OnUpdate(){
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		//if (player->GetStatusFlag(PlayerStatus::isCharging))
		//{
			auto targetPtr = GetComponent<Transform>()->GetPosition();
			auto Pos = player->GetComponent<Transform>()->GetPosition();;
			//auto XAPtr = App::GetApp()->GetXAudio2Manager();
			//m_drawComp->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
			//m_Frame->GetComponent<Transform>()->SetPosition(m_Position);
			//GetComponent<Transform>()->SetPosition(m_Position);
			auto Distance = targetPtr - Pos;
			if (player->GetStatusFlag(PlayerStatus::isCharging) && Pos.y > targetPtr.y && abs(Distance.x) < 8.0f && abs(Distance.z) < 8.0f) {
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_backDelay = m_delayTime;
				auto Velocity = m_Velocity;
				targetPtr += elapsedTime *Velocity.normalize()*4.0f;
				GetComponent<Transform>()->SetPosition(targetPtr);
				GetComponent<PNTStaticModelDraw >()->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
				m_Frame->GetComponent<Transform>()->SetPosition(targetPtr);
				if (!m_SE)
				{
					auto XAMng = App::GetApp()->GetXAudio2Manager();
					m_SE = XAMng->Start(L"LiftMove", XAUDIO2_LOOP_INFINITE, App::GetApp()->GetScene<Scene>()->m_volumeSE);
				}
				if (Vec3 (targetPtr-m_Position).length() >= m_Velocity.length()) {
					targetPtr = m_Position+m_Velocity;
					GetComponent<Transform>()->SetPosition(targetPtr);
					m_Frame->GetComponent<Transform>()->SetPosition(targetPtr);
					auto XAMng = App::GetApp()->GetXAudio2Manager();
					XAMng->Stop(m_SE);
					m_SE.reset();
				}
			}
		//}
		else 
{
	////auto targetPtr = GetComponent<Transform>()->GetPosition();
	//auto Pos = player->GetComponent<Transform>()->GetPosition();;
	//auto XAPtr = App::GetApp()->GetXAudio2Manager();
	//m_drawComp->SetDiffuse(Col4(1.0f, 1.0f, 0.0f, 1.0f));
	//if (m_statusFlags && Pos.y > 20)
	//{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_backDelay -= elapsedTime;
		auto targetPtr = GetComponent<Transform>()->GetPosition();
		GetComponent<PNTStaticModelDraw >()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		XAMng->Stop(m_SE);
		m_SE.reset();

		if (Vec3(targetPtr-m_Position).length() <= 0.3f)
		{
			targetPtr = m_Position;
			GetComponent<Transform>()->SetPosition(targetPtr);
			m_Frame->GetComponent<Transform>()->SetPosition(targetPtr);

		}
		else if(m_backDelay < 0.0f)
		{
			auto Velocity = m_Velocity;
			targetPtr -= elapsedTime * Velocity.normalize()*4.0f;
			GetComponent<Transform>()->SetPosition(targetPtr);
			m_Frame->GetComponent<Transform>()->SetPosition(targetPtr);
		}
	//}
}
			m_Frame->GetComponent<Transform>()->SetScale(m_Scale);
			m_Frame->GetComponent<Transform>()->SetRotation(m_Rotation);
	}

	void Lift::SEStop()
	{
		auto XAMng = App::GetApp()->GetXAudio2Manager();
		XAMng->Stop(m_SE);
		m_SE.reset();

	}
}

