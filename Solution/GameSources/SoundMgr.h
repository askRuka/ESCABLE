#pragma once
#include "stdafx.h"

namespace basecross
{
	class SoundMgr :public GameObject
	{
	private:
		//std::shared_ptr<XAudio2Manager> m_XAMgr;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_BGM_Stage;
		const std::shared_ptr<SoundItem> m_SE;

	public:
		SoundMgr(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~SoundMgr()
		{
		}

		virtual void OnCreate();
		virtual void OnUpdate();

		void PlayBGM(const std::wstring &bgm, bool isLoop);
		void PlayStageBGM();
		void PlaySE(const std::wstring& bgm);

		void StopStageBGM();
		void StopBGM(const std::wstring& bgm);
		void StopSE(const std::wstring& bgm);
	};
}