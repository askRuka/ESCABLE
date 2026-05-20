#pragma once
#include "stdafx.h"

namespace basecross
{
	//エフェクトクラス
	class Effect:virtual public GameObject
	{
		std::shared_ptr<PNTStaticDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;

		wstring m_texture;
		Vec3 m_pos = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 m_scale = Vec3(0.0f, 0.0f, 0.0f);

		Col4 m_col = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		Col4 m_emissive = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	public:
		Effect(const std::shared_ptr<Stage>& stage = nullptr):
			GameObject(stage)
		{
		}

		virtual ~Effect()
		{
		}

		void OnCreate()override;
		void OnUpdate()override;

	};

	//エフェクトスプライトクラス
	class EffectExplosion :public GameObject
	{
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;
		std::weak_ptr<GameObject> m_owner;

		Col4 m_color;

		float m_rotate;

		int m_number;
		float m_time = 0.0f;
		float m_waitTime = 0.0f;

	public:
		// 構築と破棄
		EffectExplosion(const shared_ptr<Stage>& stage,const shared_ptr<GameObject>& owner) :
			GameObject(stage),
			m_owner(owner),
			m_color(1, 1, 1, 1),
			m_rotate(0.0f),
			m_number(0)
		{
		}

		virtual ~EffectExplosion()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		void Billboard();

		// 表示する「数値」を設定する
		void SetNumber(int number);

		// 現在管理している「数値」を返す(0 - 9)
		int GetNumber() const
		{
		}
	};

	//帯電エフェクトクラス
	class EffectElec :virtual public Effect
	{
		std::shared_ptr<PNTStaticDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;

		std::weak_ptr<GameObject> m_owner;
		std::shared_ptr<GameObject> m_player;

		wstring m_texture;
		Vec3 m_pos = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 m_scale = Vec3(0.0f, 0.0f, 0.0f);

		float m_rotX = 0.0f;
		float m_rotY = 0.0f;
		float m_rotZ = 0.0f;

		float m_count = 0.0f;

		Col4 m_col = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		Col4 m_emissive = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	public:
		EffectElec(const std::shared_ptr<Stage>& stage, const wstring& texture,
			const Vec3& scale, const Col4& col,const Col4& emmisive) :
			GameObject(stage),
			m_texture(texture),
			m_pos(Vec3(0, 0, 0)),
			m_scale(scale),
			m_col(col),
			m_emissive(emmisive)
		{
		}

		virtual ~EffectElec()
		{
		}

		void OnCreate()override;
		void OnUpdate()override;

		void FollowOwner();
		void Animation();
		void SetOwner(const shared_ptr<GameObject>& owner);
	};


	//プラグインエフェクトクラス
	class EffectPlugIn :virtual public Effect
	{
		std::shared_ptr<PNTStaticDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;

		std::weak_ptr<GameObject> m_owner;
		std::vector<std::shared_ptr<EffectExplosion>> m_sprites;

		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		std::weak_ptr<GameObject> m_pluginObj;

		wstring m_texture;
		Vec3 m_pos = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 m_scale = Vec3(0.0f, 0.0f, 0.0f);

		float m_uvOffsetSpeed;
		float m_efFrameTime;	//エフェクトの1画像が何フレーム表示されるか
		float m_efTime;
		float m_efMaxTime;

		//float m_rotX = 0.0f;
		//float m_rotY = 0.0f;
		//float m_rotZ = 0.0f;

		float m_count = 0.0f;

		int m_number;

		Col4 m_col = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		Col4 m_emissive = Col4(1.0f, 1.0f, 1.0f, 1.0f);
	public:
		EffectPlugIn(const std::shared_ptr<Stage>& stage, const wstring& texture, shared_ptr<GameObject>& owner,
			float speed, float frame, const Vec3& scale, const Col4& col, const Col4& emmisive) :
			GameObject(stage),
			m_texture(texture),
			m_owner(owner),
			m_pos(Vec3(0, 0, 0)),
			m_scale(scale),
			m_col(col),
			m_emissive(emmisive),
			m_uvOffsetSpeed(speed),
			m_efFrameTime(frame),
			m_efTime(0.0f),
			m_efMaxTime(0.50f),
			m_number(1)
		{
		}

		virtual ~EffectPlugIn()
		{
		}

		void OnCreate()override;
		void OnUpdate()override;
		//void OnDraw()override;
		void Billboard();
		void OnAnimation();
		void SetUV(int number);
	};
}