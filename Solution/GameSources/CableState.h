/*!
@file CableState.h
@brief ケーブルのステートなど
*/

#pragma once
#include "stdafx.h"
#include "Cable.h"

namespace basecross {

	// ケーブルを投げた時のステート
	class CableThrowMoveState : public ObjState<Cable>
	{
		CableThrowMoveState() {}
	public:
		static shared_ptr<CableThrowMoveState> Instance();
		virtual void Enter (const shared_ptr<Cable>& obj) override;
		virtual void Execute (const shared_ptr<Cable>& obj) override;
		virtual void Exit (const shared_ptr<Cable>& obj) override;
	};

	// ケーブルが戻ってくるときのステート
	class CableBackMoveState : public ObjState<Cable>
	{
		CableBackMoveState() {}
	public:
		static shared_ptr<CableBackMoveState> Instance();
		virtual void Enter(const shared_ptr<Cable>& obj) override;
		virtual void Execute(const shared_ptr<Cable>& obj) override;
		virtual void Exit(const shared_ptr<Cable>& obj) override;
	};

	// ケーブルを投げずに何もしていないときのステート
	class CableStayState : public ObjState<Cable>
	{
		CableStayState() {}
	public:
		static shared_ptr<CableStayState> Instance();
		virtual void Enter(const shared_ptr<Cable>& obj) override;
		virtual void Execute(const shared_ptr<Cable>& obj) override;
		virtual void Exit(const shared_ptr<Cable>& obj) override;
	};

	// ケーブルが何かに刺さっているときのステート
	class CablePlugInState : public ObjState<Cable>
	{
		CablePlugInState() {}
	public:
		static shared_ptr<CablePlugInState> Instance();
		virtual void Enter(const shared_ptr<Cable>& obj) override;
		virtual void Execute(const shared_ptr<Cable>& obj) override;
		virtual void Exit(const shared_ptr<Cable>& obj) override;
	};


}
//end basecross

