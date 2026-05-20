/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "MainCamera.h"
#include "SoundMgr.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		std::shared_ptr<SoundMgr> m_SoundMgr;
		//void CreateViewLight(); //�r���[�̍쐬
		void CreateViewLight(); //ビューの作成
		std::shared_ptr<MainCamera> m_camera;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(){}
		virtual ~GameStage() {}
		
		virtual void OnCreate()override; //������

		void CreateStage();
		void CreateTestStage();

		void PlayBGM();
		void StopBGM();
	};

}
//end basecross

