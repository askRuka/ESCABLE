#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Frame::Frame(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Lift(true)
	{
	}
	Frame::~Frame() {}

	//‰Šú‰»
	void Frame::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale );
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//‰e‚ğ‚Â‚¯‚é
		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//•`‰æˆ—

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_FRAME");

	}
	void Frame::SetLift(bool b) { m_Lift = b; }


}

