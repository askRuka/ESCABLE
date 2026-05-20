/*!
@file Cable.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	// 通常時のカメラのステート-------------------------------------------------------------------------
	shared_ptr<CameraNormalMoveState> CameraNormalMoveState::Instance()
	{
		static shared_ptr<CameraNormalMoveState> instance(new CameraNormalMoveState);
		return instance;
	}

	void CameraNormalMoveState::Enter(const shared_ptr<MainCamera>& obj)
	{
		obj->InitParameter();
	}
	void CameraNormalMoveState::Execute(const shared_ptr<MainCamera>& obj)
	{
		obj->NormalMove(false);
	}
	void CameraNormalMoveState::Exit(const shared_ptr<MainCamera>& obj)
	{

	}

	// カメラが寄っていく時のステート-------------------------------------------------------------------
	shared_ptr<CameraCloserState> CameraCloserState::Instance()
	{
		static shared_ptr<CameraCloserState> instance(new CameraCloserState);
		return instance;
	}

	void CameraCloserState::Enter(const shared_ptr<MainCamera>& obj)
	{
	}
	void CameraCloserState::Execute(const shared_ptr<MainCamera>& obj)
	{
		obj->NormalMove(false);
		obj->CloserMove();
	}
	void CameraCloserState::Exit(const shared_ptr<MainCamera>& obj)
	{

	}

	// カメラが離れる時のステート-----------------------------------------------------------------------
	shared_ptr<CameraLeaveState> CameraLeaveState::Instance()
	{
		static shared_ptr<CameraLeaveState> instance(new CameraLeaveState);
		return instance;
	}

	void CameraLeaveState::Enter(const shared_ptr<MainCamera>& obj)
	{
	}
	void CameraLeaveState::Execute(const shared_ptr<MainCamera>& obj)
	{
		obj->NormalMove(false);
		if (obj->LeaveMove())
		{
			obj->GetStateMachine()->ChangeState(CameraNormalMoveState::Instance());
		}
	}
	void CameraLeaveState::Exit(const shared_ptr<MainCamera>& obj)
	{

	}

	// エディターモード時のカメラのステート-----------------------------------------------------------------
	shared_ptr<EditorCameraState> EditorCameraState::Instance()
	{
		static shared_ptr<EditorCameraState> instance(new EditorCameraState);
		return instance;
	}

	void EditorCameraState::Enter(const shared_ptr<MainCamera>& obj)
	{
	}
	void EditorCameraState::Execute(const shared_ptr<MainCamera>& obj)
	{
		obj->NormalMove(true);
	}
	void EditorCameraState::Exit(const shared_ptr<MainCamera>& obj)
	{

	}

	// 敵がやられるときのカメラのステート-----------------------------------------------------------------
	shared_ptr<TargetEnemyCameraState> TargetEnemyCameraState::Instance()
	{
		static shared_ptr<TargetEnemyCameraState> instance(new TargetEnemyCameraState);
		return instance;
	}

	void TargetEnemyCameraState::Enter(const shared_ptr<MainCamera>& obj)
	{
	}
	void TargetEnemyCameraState::Execute(const shared_ptr<MainCamera>& obj)
	{
		if (obj->TargetEnemyMove())
		{
			obj->GetStateMachine()->ChangeState(CameraNormalMoveState::Instance());
		}
	}
	void TargetEnemyCameraState::Exit(const shared_ptr<MainCamera>& obj)
	{

	}

}
//end basecross
