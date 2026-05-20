/*!
@file CameraState.h
@brief カメラのステートなど
*/

#pragma once
#include "stdafx.h"
#include "MainCamera.h"

namespace basecross {

	// 通常時のカメラのステート
	class CameraNormalMoveState : public ObjState<MainCamera>
	{
		CameraNormalMoveState() {}
	public:
		static shared_ptr<CameraNormalMoveState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& obj) override;
		virtual void Execute(const shared_ptr<MainCamera>& obj) override;
		virtual void Exit(const shared_ptr<MainCamera>& obj) override;
	};

	// カメラが寄っていく時のステート
	class CameraCloserState : public ObjState<MainCamera>
	{
		CameraCloserState() {}
	public:
		static shared_ptr<CameraCloserState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& obj) override;
		virtual void Execute(const shared_ptr<MainCamera>& obj) override;
		virtual void Exit(const shared_ptr<MainCamera>& obj) override;
	};

	// カメラが離れる時のステート
	class CameraLeaveState : public ObjState<MainCamera>
	{
		CameraLeaveState() {}
	public:
		static shared_ptr<CameraLeaveState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& obj) override;
		virtual void Execute(const shared_ptr<MainCamera>& obj) override;
		virtual void Exit(const shared_ptr<MainCamera>& obj) override;
	};

	// エディターモード時のカメラのステート
	class EditorCameraState : public ObjState<MainCamera>
	{
		EditorCameraState() {}
	public:
		static shared_ptr<EditorCameraState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& obj) override;
		virtual void Execute(const shared_ptr<MainCamera>& obj) override;
		virtual void Exit(const shared_ptr<MainCamera>& obj) override;
	};


	// 敵がやられるときのカメラのステート
	class TargetEnemyCameraState : public ObjState<MainCamera>
	{
		TargetEnemyCameraState() {}
	public:
		static shared_ptr<TargetEnemyCameraState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& obj) override;
		virtual void Execute(const shared_ptr<MainCamera>& obj) override;
		virtual void Exit(const shared_ptr<MainCamera>& obj) override;
	};

}
//end basecross

