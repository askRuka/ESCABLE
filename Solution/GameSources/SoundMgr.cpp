#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void SoundMgr::OnCreate()
	{

	}

	void SoundMgr::OnUpdate()
	{

	}

	//再生処理
	//BGM再生(BGMキー, ループON/OFF)
	void SoundMgr::PlayBGM(const std::wstring &bgm, bool isLoop)
	{
		auto& app = App::GetApp();
		auto m_XAMgr = app->GetXAudio2Manager();

		//m_XAMgr->Stop(m_BGM);
		auto BGM = m_XAMgr->Start(bgm, XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void SoundMgr::PlayStageBGM()
	{
		auto& app = App::GetApp();
		auto XAMgr = app->GetXAudio2Manager();

		m_BGM_Stage = XAMgr->Start(L"STAGE", XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	//SE再生(SEキー)
	void SoundMgr::PlaySE(const std::wstring& se)
	{
		auto& app = App::GetApp();
		auto XAMgr = app->GetXAudio2Manager();
		//m_SE == m_XAMgr->Start(se);
		auto SE = XAMgr->Start(se);
	}

	//停止処理
	//BGM停止
	void SoundMgr::StopBGM(const std::wstring &bgm)
	{
		auto& app = App::GetApp();
		auto XAMgr = app->GetXAudio2Manager();
		XAMgr->Stop(m_BGM);
	}
	
	//ゲームステージBGM停止
	void SoundMgr::StopStageBGM()
	{
		if (m_BGM_Stage && m_BGM_Stage->m_SourceVoice)
		{
			m_BGM_Stage->m_SourceVoice->Stop();
		}
	}

	//SE停止
	void SoundMgr::StopSE(const std::wstring& se)
	{
		auto& app = App::GetApp();
		auto XAMgr = app->GetXAudio2Manager();
		XAMgr->Stop(m_SE);
	}
}
