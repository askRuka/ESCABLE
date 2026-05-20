/*!
@file Cable.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	// ケーブルを投げた時のステートの処理
	shared_ptr<CableThrowMoveState> CableThrowMoveState::Instance()
	{
		static shared_ptr<CableThrowMoveState> instance(new CableThrowMoveState);
		return instance;
	}

	void CableThrowMoveState::Enter(const shared_ptr<Cable>& obj)
	{
		obj->SetDrawActive(true);
		obj->SEStart(L"CableThrow");
	}

	void CableThrowMoveState::Execute(const shared_ptr<Cable>& obj)
	{
		//obj->TipMove();
		// 投げ終わったらif文の中身を実行
		if (obj->ThrowMove())
		{
			// ケーブルがつながることができるものにあたっていたらPlugInへ、違かったらBackMoveへ
			if (obj->GetIsHit())
			{
				obj->GetStateMachine()->ChangeState(CablePlugInState::Instance());
			}
			else
			{
				obj->GetStateMachine()->ChangeState(CableBackMoveState::Instance());
			}
		}
	}
	void CableThrowMoveState::Exit(const shared_ptr<Cable>& obj)
	{
		obj->SEStop();
	}

	// ケーブルが戻るときのステートの処理
	shared_ptr<CableBackMoveState> CableBackMoveState::Instance()
	{
		static shared_ptr<CableBackMoveState> instance(new CableBackMoveState);
		return instance;
	}

	void CableBackMoveState::Enter(const shared_ptr<Cable>& obj)
	{
		// 描画しつつ、必要な項目を初期化
		obj->SetDrawActive(true);
		obj->BackMoveInit();
		//obj->SEStart(L"CableBack");
	}
	void CableBackMoveState::Execute(const shared_ptr<Cable>& obj)
	{
		//obj->TipMove();

		//戻る動きが終わったらStayステートに移行
		if (obj->BackMove())
		{
			obj->GetStateMachine()->ChangeState(CableStayState::Instance());
		}
	}
	void CableBackMoveState::Exit(const shared_ptr<Cable>& obj)
	{
		// 描画しないようにする
		obj->SetDrawActive(false);
		//obj->SEStop();
	}

	// ケーブルが特に何もしていないときのステートの処理（特に何もなし）
	shared_ptr<CableStayState> CableStayState::Instance()
	{
		static shared_ptr<CableStayState> instance(new CableStayState);
		return instance;
	}

	void CableStayState::Enter(const shared_ptr<Cable>& obj)
	{
		obj->SetDrawActive(false);
	}
	void CableStayState::Execute(const shared_ptr<Cable>& obj)
	{
	}
	void CableStayState::Exit(const shared_ptr<Cable>& obj)
	{
	}

	// ケーブルが何かに刺さっているときのステートの処理
	shared_ptr<CablePlugInState> CablePlugInState::Instance()
	{
		static shared_ptr<CablePlugInState> instance(new CablePlugInState);
		return instance;
	}

	void CablePlugInState::Enter(const shared_ptr<Cable>& obj)
	{
		//obj->TipState();
		// 描画するように設定しプレイヤー側で現在の状態を確認してもらう
		obj->SetDrawActive(true);
		obj->PlayerCheckStatus();
	}
	void CablePlugInState::Execute(const shared_ptr<Cable>& obj)
	{
		// 電気のトリガーに状態を送る
		obj->StateSendToTrigger();
		// ケーブルの当たり判定を取り回り込みをする
		obj->CheckCollide();
	}
	void CablePlugInState::Exit(const shared_ptr<Cable>& obj)
	{
		// 当たったオブジェクトをリセットしてプレイヤーの状態を確認
		obj->ResetHitObj();
		obj->PlayerCheckStatus();

	}

}
//end basecross
