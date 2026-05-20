/*!
@file Consent.cpp
@brief コンセント実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Consent::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		Mat4x4 span; // モデルとトランスフォームの間の差分行列
		span.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		 auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		 ptrDraw->SetMeshResource(L"MODEL_CONSENT");
		 ptrDraw->SetMeshToTransformMatrix(span);


	}
}
//end basecross
