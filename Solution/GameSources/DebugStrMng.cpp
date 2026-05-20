/*!
@file Foo.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "DebugStrMng.h"

namespace basecross {

	//更新
	void DebugStrMng::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		wstringstream ss;
		ss << scene->GetDebugString();
		ss << m_ss;
		scene->SetDebugString(ss.str());
		m_ss = L"";
	}

	void DebugStrMng::AddDebugString(const wstring& ss)
	{
		m_ss += ss;
	}

}
//end basecross
