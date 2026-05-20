#pragma once
#include "stdafx.h"

namespace basecross {
	class Aura : public GameObject
	{
	public:
		struct InitParams
		{
			std::wstring textureKey; // テクスチャリソースのキー
			int sides; // 円形の分割数
			float height; // オーラの高さ
			float topRadius; // 上部円の半径
			float bottomRadius; // 下部円の半径
			Col4 topColor; // 上部の色
			Col4 bottomColor; // 下部の色
			Vec2 uvOffsetSpeed; // UVアニメーションの秒速
			float textureLoops; // テクスチャの「u座標」

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius, const Col4& topColor, const Col4& bottomColor, const Vec2& speed, float textureLoops)
				: textureKey(textureKey), sides(sides), height(height), topRadius(topRadius), bottomRadius(bottomRadius), topColor(topColor), bottomColor(bottomColor), uvOffsetSpeed(speed), textureLoops(textureLoops)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius, const Col4& topColor, const Col4& bottomColor, const Vec2& speed)
				: InitParams(textureKey, sides, height, topRadius, bottomRadius, topColor, bottomColor, speed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius)
				: InitParams(textureKey, sides, height, radius, radius, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& color)
				: InitParams(textureKey, sides, height, radius, radius, color, color, Vec2(0.0f), 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& color, const Vec2& uvOffsetSpeed)
				: InitParams(textureKey, sides, height, radius, radius, color, color, uvOffsetSpeed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float radius, const Col4& topColor, const Col4& bottomColor, const Vec2& uvOffsetSpeed)
				: InitParams(textureKey, sides, height, radius, radius, topColor, bottomColor, uvOffsetSpeed, 1.0f)
			{
			}

			InitParams(const wstring& textureKey, int sides, float height, float topRadius, float bottomRadius)
				: InitParams(textureKey, sides, height, topRadius, bottomRadius, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

			InitParams()
				: InitParams(L"", 30, 1.0f, 1.0f, 1.0f, Col4(1.0f), Col4(1.0f), Vec2(0.0f), 1.0f)
			{
			}

		};

	private:
		std::vector<VertexPositionColorTexture> vertices;

		InitParams params;

	public:
		Aura(const std::shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		Aura(const std::shared_ptr<Stage>& stage, const Aura::InitParams& initParams)
			: GameObject(stage), params(initParams)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;
	};
}