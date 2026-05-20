/*!
@file Door.cpp
@brief ドア実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Door::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TEX_Door02");


	}

	void Door::OnMove()
	{
		//アクションの登録
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddMoveBy(5.0f, Vec3(0.0f, 20.0f, 0));

		//アクション開始
		PtrAction->Run();

	}

	void Door::SwitchSetter(shared_ptr<GameObject> set)
	{
		m_Switch = set;
	}

	void Door::OnUpdate()
	{	
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();


		auto Switch = dynamic_pointer_cast<ElectricTrigger>(m_Switch);
		if (Switch->GetTrigger() || m_OnDoor)
		{
			m_DeleteTime -= delta;
			m_OnDoor = true;

			OnMove();
			if (m_DeleteTime <= 0.0f)
			{
				GetStage()->RemoveGameObject<Door>(GetThis<Door>());
			}
		}
	}

	shared_ptr<GameObject> Door::GetSwitchObject()
	{
		return m_Switch;
	}

}
//end basecross
