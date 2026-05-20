/*!
@file Floor.cpp
@brief 床実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Floor::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"TEX_Floor");
		//ptrDraw->SetOwnShadowActive(true);

        // タイリングの設定
        vector<uint16_t> indices;
        MeshUtill::CreateCube(1.0f, m_vertices, indices);

        for (int i = 0; i < m_vertices.size(); i += 4)
        {
            int s = i / 4;
            float xScale = (s >= 2 ? (s < 4 ? m_Scale.z : m_Scale.x) : m_Scale.x) / 4;
            float yscale = (s >= 2 ? (s >= 4 ? m_Scale.z : m_Scale.y) : m_Scale.y) / 4;
            m_vertices[i].textureCoordinate = Vec2(0, 0);
            m_vertices[i + 1].textureCoordinate = Vec2(0, yscale);
            m_vertices[i + 2].textureCoordinate = Vec2(xScale, yscale);
            m_vertices[i + 3].textureCoordinate = Vec2(xScale, 0);

        }
        //描画コンポーネントの追加
        auto PtrDraw = AddComponent<PNTStaticDraw>();
        //描画コンポーネントに形状（メッシュ）を設定
        PtrDraw->CreateOriginalMesh(m_vertices, indices);
        PtrDraw->SetOriginalMeshUse(true);
        //PtrDraw->SetFogEnabled(true);
        //自分に影が映りこむようにする
        PtrDraw->SetOwnShadowActive(true);
        //描画コンポーネントテクスチャの設定
        PtrDraw->SetTextureResource(L"TEX_Floor");
        //タイリング設定
        PtrDraw->SetSamplerState(SamplerState::LinearWrap);
    }

    void Floor::SetParameret(const Vec3& Scale, const Vec3& Rotation, const Vec3& Position)
    {
        m_Scale = Scale;
        m_Rotation = Rotation;
        m_Position = Position;

        for (int i = 0; i < m_vertices.size(); i += 4)
        {
            int s = i / 4;
            float xScale = (s >= 2 ? (s < 4 ? m_Scale.z : m_Scale.x) : m_Scale.x) / 2;
            float yscale = (s >= 2 ? (s >= 4 ? m_Scale.z : m_Scale.y) : m_Scale.y) / 2;
            m_vertices[i].textureCoordinate = Vec2(0, 0);
            m_vertices[i + 1].textureCoordinate = Vec2(0, yscale);
            m_vertices[i + 2].textureCoordinate = Vec2(xScale, yscale);
            m_vertices[i + 3].textureCoordinate = Vec2(xScale, 0);

        }

        auto drawComp = GetComponent<PNTStaticDraw>();
        drawComp->UpdateVertices(m_vertices);
    }

}
//end basecross
