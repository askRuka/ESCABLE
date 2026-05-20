#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Aura::OnCreate()
	{
		// 頂点データの作成する
		for (int i = 0; i < params.sides + 1; i++) // 1周して戻ってきて、出発点にも頂点が必要なため、分割数より1回多くループする
		{
			float fSides = static_cast<float>(params.sides); // 円の分割数をfloat型に変換する
			float radian = XMConvertToRadians(i * 360.0f / fSides); // 頂点を配置する角度を算出する
			vertices.push_back({ Vec3(params.topRadius * cosf(radian), params.height, params.topRadius * sinf(radian)), params.topColor, Vec2(i / fSides, 0.0f) }); // 上の頂点
			vertices.push_back({ Vec3(params.bottomRadius * cosf(radian), 0.0f, params.bottomRadius * sinf(radian)), params.bottomColor, Vec2(i / fSides, params.textureLoops) }); // 下の頂点
		}

		// ループ処理のベースにするインデックス
		uint16_t baseIndices[] = {
			1, 0, 2,
			1, 2, 3,
		};

		// ベースインデックスをもとに頂点インデックスを作成する
		std::vector<uint16_t> indices;
		//面の数だけループ
		for (int i = 0; i < params.sides; i++)
		{
			//一枚の板ポリを形成
			for (auto baseIndex : baseIndices)
			{
				indices.push_back(baseIndex + 2 * i); // ベースインデックスを２ずつずらして設定していく
			}
		}

		// ドローコンポーネントを追加する
		auto drawComp = AddComponent<BcPCTStaticDraw>(); // Bc系のコンポーネントだと、頂点の色でアルファブレンドしてくれる
		drawComp->CreateOriginalMesh(vertices, indices); // 上記の設定をもとにメッシュを生成する
		drawComp->SetOriginalMeshUse(true); // 独自メッシュ(プログラム内で作成)を使用することを宣言する
		if (params.textureKey != L"") // テクスチャを使用する場合の設定
		{
			drawComp->SetTextureResource(params.textureKey); // 使用するテクスチャを設定する
		}
		drawComp->SetBlendState(BlendState::Additive); // 加算合成されるように設定する
		drawComp->SetDepthStencilState(DepthStencilState::Read); // 他の板ポリと干渉しないようにする]
		if (params.textureLoops > 1.0f || params.uvOffsetSpeed.length() != 0.0f) // ループアニメーションや拡大UVを使用する場合はテクスチャが繰り返しに対応できるように設定する
		{
			drawComp->SetSamplerState(SamplerState::AnisotropicWrap); // テクスチャアニメーション用にループ貼り付けできるようにする
		}

		SetAlphaActive(true); // 透過処理を有効にする
	}

	void Aura::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		for (auto& vertex : vertices) // テクスチャアニメーションさせる
		{
			vertex.textureCoordinate += delta * params.uvOffsetSpeed * 4; // すべての頂点のUVを秒速でずらす
		}

		auto drawComp = GetComponent<BcPCTStaticDraw>();
		drawComp->UpdateVertices(vertices); // 更新された頂点データを再適用する

		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");

		if (player)
		{
			auto playerPos = player->GetComponent<Transform>()->GetPosition();
			auto playerPo = player->GetComponent<Transform>();
			auto pos = GetComponent<Transform>()->GetPosition();
			auto po = GetComponent<Transform>();
			auto distance = Vec3(playerPos - pos);
			auto scale = GetComponent<Transform>()->GetScale();
			bool isCheck = abs(distance.x) < scale.x && abs(distance.y) < scale.y && abs(distance.z) < scale.z;
			if (isCheck)
			{
				GetStage()->RemoveGameObject<Aura>(GetThis<Aura>());
			}
		}
	}
}