/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//--------------------------------------------------------------------------------------
		/*!
		@brief リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();
		int m_SrageNum;
		int m_loadStageNumber; // 読み込むステージの番号
		bool m_isStartFirst;
		Vec3 m_checkpointPos;
		Vec3 m_checkpointRot;
	public:
		std::shared_ptr<SoundItem> m_BGM;

		float m_volumeBGM;
		float m_volumeSE;

		float m_volumeBGMpos;
		float m_volumeSEpos;

		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :
			SceneBase(),
			m_SrageNum(1),
			m_isStartFirst(true),
			m_volumeBGM(1.0f),
			m_volumeSE(1.0f),
			m_volumeBGMpos(200.0f),
			m_volumeSEpos(200.0f),
			m_loadStageNumber(1)
		{
		}
		int GetStageNum() const {
			return m_SrageNum;
		}
		void SetStageNum(int i) {
			m_SrageNum = i;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;


		virtual void OnUpdate() override;

		void SetIsFirstStart(bool b) { m_isStartFirst = b; }
		bool GetIsFirstStart() { return m_isStartFirst; }
		void SetCheckpointPos(const Vec3& pos) { m_checkpointPos = pos; }
		Vec3 GetCheckpointPos() { return m_checkpointPos; }
		void SetCheckpointRotation(const Vec3& rot) { m_checkpointRot = rot; }
		Vec3 GetCheckpointRotation() { return m_checkpointRot; }
		int GetLoadStageNumber() { return m_loadStageNumber; }
		void SetLoadStageNumber(int num) { m_loadStageNumber = num; }
		void ChangeBGMVolume();
		void BGMStart(const wstring& name);
		void BGMStop();
		void SEStart(const wstring& name);
	};

}

//end basecross
