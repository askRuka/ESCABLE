/*!
@file Piller.cpp
@brief ’ŒÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//‰Šú‰»
	void Piller::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TEX_Piller");
		//ptrDraw->SetTextureResource(L"TEX_Piller01");

	}

}
//end basecross
