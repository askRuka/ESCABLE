#pragma once
#include "stdafx.h"
#include "DXModel.h"
#include <unordered_map>

namespace basecross
{
	class PNTDXModelDraw : public SmBaseDraw
	{
	public:
		using SmBaseDraw::SetMultiMeshResource;

		explicit PNTDXModelDraw(const shared_ptr<GameObject>& gameObjectPtr);
		virtual ~PNTDXModelDraw();

		void SetAnimationIndex(size_t index);
		void SetCurrentAnimationTime(float time);
		void SetLoop(bool loop);
		void SetSpeed(float speed);

		void AddAnimation(const wstring& name, int startSample, int sampleLength, bool loop = true, float samplesParSecond = 30.0f);
		void AddAnimation(
			size_t animationIndex,
			const wstring& clipName,
			int startSample,
			int sampleLength,
			bool loop = true,
			float samplesParSecond = 30.0f);
		void AddAnimation(
			const wstring& animationName,
			const wstring& clipName,
			int startSample,
			int sampleLength,
			bool loop = true,
			float samplesParSecond = 30.0f);
		void ChangeCurrentAnimation(const wstring& animationName, float startTime = 0.0f);
		const wstring& GetCurrentAnimation() const;
		float GetCurrentAnimationTime() const;
		void UpdateAnimation(float elapsedTime);

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		const vector<bsm::Mat4x4>* GetVecLocalBonesPtr() const override;
		const vector<bsm::Mat4x4>* GetVecMultiLocalBonesPtr(size_t index) const override;

		void SetMultiMeshResource(const shared_ptr<MultiMeshResource>& meshResourcePtr) override;

		bsm::Mat4x4 GetBoneWorldMatrix(const wstring& boneName) const;
		bsm::Mat4x4 GetBoneWorldMatrix(size_t boneIndex) const;

	private:
		void UpdatePose();
		void BuildChannelBoneMap();
		void BuildBoneIndexMap();

		static int FindBoneIndexByName(const vector<dxm::RuntimeBone>& bones, const wstring& name);
		static float WrapTimeTicks(float timeTicks, float durationTicks, bool loop);
		static XMMATRIX EvaluateChannelLocalMatrix(const dxm::RuntimeAnimationChannel& channel, float timeTicks);
		static XMFLOAT3 SampleVector(const vector<dxm::RuntimeKeyVector>& keys, float timeTicks);
		static XMFLOAT4 SampleQuaternion(const vector<dxm::RuntimeKeyQuaternion>& keys, float timeTicks);

		int FindBoneIndexByNameFast(const wstring& name) const;

	private:
		struct AnimationClip
		{
			wstring name;
			int startSample;
			int sampleLength;
			bool loop;
			float samplesParSecond;
			size_t animationIndex; // ’Ç‰Á
		};

	private:
		size_t m_animationIndex;
		bool m_loop;
		float m_speed;
		vector<int> m_boneIndexByChannel;

		vector<bsm::Mat4x4> m_finalBoneMatrices;
		vector<bsm::Mat4x4> m_boneGlobalMatrices;
		std::unordered_map<wstring, int> m_boneIndexByName;

		vector<AnimationClip> m_clips;
		int m_currentClipIndex;
		wstring m_currentAnimeName;
		float m_currentAnimeTime;
	};
}