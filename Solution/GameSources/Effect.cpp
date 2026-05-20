#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//-------------------------
	// エフェクトクラス
	//-------------------------
	void Effect::OnCreate()
	{

	}

	void Effect::OnUpdate()
	{

	}

//-------------------------
// エフェクトスプライトクラス
//-------------------------
	void EffectExplosion::OnCreate()
	{
		float texW = 256.0f / 1024.0f;
		float texH = 256.0f / 256.0f;
		float left = texW * m_number;
		float right = left + texW;
		float top = 0.0f;
		float bottom = top + texH;

		float halfSides = 256.0f;

		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(-halfSides, +halfSides, 1.0f), color, Vec2(left, top) },		//1
			{Vec3(+halfSides, +halfSides, 1.0f), color, Vec2(right, top) },		//2
			{Vec3(-halfSides, -halfSides, 1.0f), color, Vec2(left, bottom) },		//3
			{Vec3(+halfSides, -halfSides, 1.0f), color, Vec2(right, bottom) },		//4
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		m_drawComp = AddComponent<PCTSpriteDraw>();
		//m_drawComp->CreateOriginalMesh(m_vertices, m_indices);
		//m_drawComp->SetOriginalMeshUse(true);
		m_drawComp->SetTextureResource(L"TEX_EF_Explosion"); // 使用するテクスチャを設定する

		m_drawComp->SetRasterizerState(RasterizerState::DoubleDraw);
		m_drawComp->SetDepthStencilState(DepthStencilState::None);

		SetNumber(0);
		SetAlphaActive(true);

		//m_drawComp->SetDiffuse(m_col);
		//m_drawComp->SetEmissive(Col4(1.0f, 1.0f, 1.0f, 1.0f));

		Vec3 ownerPos(0.0f);
		auto owner = m_owner.lock();
		if (owner)
		{
			ownerPos = owner->GetComponent<Transform>()->GetPosition();
		}

		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(0, 0, 0);
		m_transComp->SetScale(Vec3(1, 1, 1));
	}

	void EffectExplosion::OnUpdate()
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//Billboard();
		// uv座標における、数字1桁の幅と高さ
		//float w = 256.0f / 256.0f;
		//float left = w * m_number; // 引数で指定した数字の左側を表す座標

		//数値を更新する
		if (m_waitTime <= 0.15f)
		{
			m_waitTime += delta;
		}
		else if (m_time <= 4)
		{
			m_time += 12.5f * delta;
			SetNumber(m_time);
		}
		//m_vertices[0].textureCoordinate.x = left;
	}

	//ビルボードメソッド
	void EffectExplosion::Billboard()
	{
		auto stage = GetStage();
		auto camera = stage->GetView()->GetTargetCamera();
		auto viewMatrix = camera->GetViewMatrix();
		Quat viewQuat(viewMatrix);
		viewQuat.x *= -1.0f;
		viewQuat.y *= -1.0f;
		viewQuat.z *= -1.0f;
		m_transComp->SetQuaternion(viewQuat);
	}

	void EffectExplosion::SetNumber(int number) // 0 - 9
	{
		//エラーチェック(条件が失敗したらプログラムを止める)
		assert(number >= 0 && number <= 4);

		//管理している「数値」を更新する
		m_number = number;

		//uv座標における、数字1桁の幅と高さ
		float w = 256.0f / 1024.0f;
		float left = w * m_number; // 引数で指定した数字の左側を表す座標

		//新しい数値に合わせて、頂点データを変更する
		m_vertices[0].textureCoordinate.x = left;
		m_vertices[1].textureCoordinate.x = left + w;
		m_vertices[2].textureCoordinate.x = left;
		m_vertices[3].textureCoordinate.x = left + w;
		m_drawComp->UpdateVertices(m_vertices);
	}

	//-------------------------
	// 帯電エフェクトクラス
	//-------------------------

	void EffectElec::OnCreate()
	{
		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		m_drawComp->SetTextureResource(m_texture);

		m_drawComp->SetDiffuse(m_col);
		//m_drawComp->SetEmissive(Col4(1.0f, 0.80f, 0.0f, 1.0f));
		m_drawComp->SetEmissive(m_emissive);
		//m_drawComp->SetBlendState(BlendState::Additive);
		m_drawComp->SetRasterizerState(RasterizerState::DoubleDraw);
		m_drawComp->SetDepthStencilState(DepthStencilState::None);

		SetAlphaActive(true);

		m_transComp = AddComponent<Transform>();
		m_transComp->SetPosition(m_pos);
		m_transComp->SetScale(m_scale);
	}

	void EffectElec::OnUpdate()
	{
		FollowOwner();
		Animation();

		//(途中)ある程度距離が離れたらエフェクトを見えなくする
		//auto playerPos = m_player->GetComponent<Transform>()->GetPosition();
		//auto effectPos = GetComponent<Transform>()->GetPosition();

		//auto posAbsX = std::abs(playerPos.x - effectPos.x);
		//auto posAbsY = std::abs(playerPos.y - effectPos.y);
		//auto posAbsZ = std::abs(playerPos.z - effectPos.z);

		//Vec3 pos = Vec3(posAbsX, posAbsY, posAbsZ);

		//if (pos.x >= 5 || pos.y >= 5 || pos.z >= 5)
		//{
		//	SetDrawActive(false);
		//}

		
	}

	//オーナーオブジェクト追従処理
	void EffectElec::FollowOwner()
	{
		//移動(オーナー追従)
		auto owner = dynamic_pointer_cast<GameObject>(m_owner.lock());
		if (owner)
		{
			m_pos = owner->GetComponent<Transform>()->GetPosition() + Vec3(0.0f, 0.5f, 0.0f);
		}
		else
		{
			m_pos = Vec3(0.0f, 1.0f, 0.0f);
		}

		m_transComp->SetPosition(m_pos);

	}

	//エフェクトアニメーション
	void EffectElec::Animation()
	{
		auto& app = App::GetApp();
		auto elapsed = app->GetElapsedTime();

		//回転と表示切り替え
		m_count += 4 * elapsed;

		if (m_count <= 0.20f)
		{
			//SetDrawActive(false);
			m_col.w = 0.0f;
			m_emissive.w = 0.0f;

			m_rotX += 25.0f * elapsed;
			m_rotY += 35.0f * elapsed;
			m_rotZ += 30.0f * elapsed;
		}
		else if (m_count <= 0.30f)
		{
			//SetDrawActive(true);
			m_col.w = 1.0f;
			m_emissive.w = 1.0f;
		}
		else
		{
			m_count = 0;
		}

		m_transComp->SetRotation(m_rotX, m_rotY, m_rotZ);
		m_transComp->SetScale(m_scale);

		m_drawComp->SetDiffuse(m_col);
		m_drawComp->SetEmissive(m_emissive);
	}

	void EffectElec::SetOwner(const shared_ptr<GameObject>& owner)
	{
		m_owner = owner;
	}


//-------------------------
// プラグインエフェクトクラス
//-------------------------
	void EffectPlugIn::OnCreate()
	{
		float texW = 256.0f;
		float texH = 256.0f;
		float left = texW;
		float right = left + texW;
		float top = texH;
		float bottom = top + texH;

		float halfSides = 0.5f;

		Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(-halfSides, +halfSides, 0.0f), color, Vec2(0.0f, 0.0f) },		//1
			{Vec3(+halfSides, +halfSides, 0.0f), color, Vec2(1.0f, 0.0f) },		//2
			{Vec3(-halfSides, -halfSides, 0.0f), color, Vec2(0.0f, 1.0f) },		//3
			{Vec3(+halfSides, -halfSides, 0.0f), color, Vec2(1.0f, 1.0f) },		//4
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3,
		};

		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_drawComp->SetOriginalMeshUse(true);

		if (m_texture != L"")
		{
			m_drawComp->SetTextureResource(m_texture); // 使用するテクスチャを設定する
		}

		//m_drawComp->SetDepthStencilState(DepthStencilState::Read);
		SetAlphaActive(true);

		//m_drawComp->SetDiffuse(m_col);
		//m_drawComp->SetEmissive(Col4(1.0f, 1.0f, 1.0f, 1.0f));

		Vec3 ownerPos(0.0f);
		auto owner = m_owner.lock();
		if (owner)
		{
			ownerPos = owner->GetComponent<Transform>()->GetPosition() + Vec3(0.0f, 1.5f, 0.0f);
		}

		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(ownerPos);
	}

	void EffectPlugIn::OnUpdate()
	{
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		Billboard();
		//OnAnimation();

		m_efTime += delta;

		if (m_efTime >= m_efMaxTime)
		{
			GetStage()->RemoveGameObject<EffectPlugIn>(GetThis<EffectPlugIn>());
		}
	}

	//ビルボードメソッド
	void EffectPlugIn::Billboard()
	{
		auto stage = GetStage();
		auto camera = stage->GetView()->GetTargetCamera();
		auto viewMatrix = camera->GetViewMatrix();
		Quat viewQuat(viewMatrix);
		viewQuat.x *= -1.0f;
		viewQuat.y *= -1.0f;
		viewQuat.z *= -1.0f;
		m_transComp->SetQuaternion(viewQuat);
	}

	//エフェクトアニメーション
	void EffectPlugIn::OnAnimation()
	{
		auto& app = App::GetApp();
		auto delta = App::GetApp()->GetElapsedTime();

		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += delta * m_uvOffsetSpeed;
		}

		m_drawComp->UpdateVertices(m_vertices);
	}

	void EffectPlugIn::SetUV(int number)
	{
		// 管理している「数値」を更新する
		m_number = number;

		//uv座標における、1枚絵の幅と高さ
		float w = 256.0f / 256.0f;
		float left = w * m_number; // 引数で指定した数字の左側を表す座標

		//新しい数値に合わせて、頂点データを変更する
		m_vertices[0].textureCoordinate.x = left;
		m_vertices[1].textureCoordinate.x = left + w;
		m_vertices[2].textureCoordinate.x = left;
		m_vertices[3].textureCoordinate.x = left + w;
		m_drawComp->UpdateVertices(m_vertices);
	}
}