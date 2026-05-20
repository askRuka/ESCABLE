/*!
@file Player.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "Cable.h"
#include "Consent.h"
#include "Effect.h"
#include "PNTDXModelDraw.h"

namespace basecross {
	enum PlayerStatus
	{
		isGround = 1,
		isRightPlugIn = 2,
		isLeftPlugIn = 4,
		isCharging = 8,
		isGettingOnLift = 16,
		isDead = 32,

	};
	class Player : public GameObjectForEdit
	{
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_BGM1;
		shared_ptr<SoundItem> m_SE;
		std::shared_ptr<Transform> m_transComp; // 描画用コンポーネント
		std::shared_ptr<PNTDXModelDraw> m_drawComp; // Transformコンポーネント
		std::shared_ptr<Cable> m_cable[2]; // ケーブルクラスのポインター(0が右、1は左)
		std::shared_ptr<EffectElec> m_effectEl;
		std::shared_ptr<EffectPlugIn> m_effectPlugIn;

		float m_speed; // 移動の速さ
		Vec3 m_velocityXZ; // XZ平面の移動速度
		float m_velocityY; // Y軸方向の移動速度
		float m_cameraAngleY; // カメラのY軸方向の回転の向き
		BYTE m_pastTrigger[2]; //LRの前フレームのトリガーを保存しておく(0が右、1は左)
		Vec3 m_armPos[2]; // 各腕のプレイヤーからの座標(0が右、1は左)
		float m_armDis; // キャラクターの中心から腕までの距離
		Vec3 m_hitLifhPos; // 接触したリフトの座標を保管しておく変数
		bool m_isAiming; // 照準状態かどうか
		Vec3 m_cableTension; // ケーブルからの張力
		float m_scale = 0.1f; // プレイヤーのスケール
		bool m_isControl; // プレイヤーの操作可能かどうか
		bool m_Steps; // 足音を制御するためのブール
		void InitDrawComp(); // Drawコンポーネントの初期化
		void InitTransComp(); // Transformコンポーネントの初期化
		Vec3 InputVec(); //入力された移動操作のベクトルを返す関数
		void VelocityXZUpdate(const Vec3& input); // m_velocityXZの更新
		void VelocityYUpdate(bool isJump); // m_velocityYの更新
		void HitCheck(const Vec3& pos, Vec3& nextPos); //特定のオブジェクトとの接触を確認する

		void LiftHitCheck(const shared_ptr<GameObject>& lift, const Vec3& pos, Vec3& nextPos); // リフトとの当たり判定
		void CubeHitCheck(const shared_ptr<GameObject>& obj, const Vec3& pos, Vec3& nextPos); // 直方体との当たり判定
		void InputTriggerCheck(bool LR); // (trueで右、falseで左)
		void CableLengthCheck(); // ケーブルの長さを確認
		void AnimationUpdate(); // アニメーションの更新
		void CablesStateCheck(); // 両方のケーブルの状態を確認してモデルを変更する
		UINT m_statusFlags; // プレイヤーの状態
	public:
		Player(const shared_ptr<Stage>& stage) :
			GameObjectForEdit(stage),
			//m_speed(3.0f),
			m_speed(10.0f),
			m_velocityXZ(Vec3(0)),
			m_velocityY(0),
			m_cameraAngleY(0),
			m_statusFlags(0),
			m_pastTrigger(),
			m_armPos(),
			m_armDis(0.2f),
			m_isControl(true)
		{
		}
		virtual ~Player()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		//カメラの回転方向を取得する
		void SetCameraAngleY(float cameraAngleY)
		{
			m_cameraAngleY = cameraAngleY;
		}
		//各種Velocityを初期化する
		void InitVelocity();
		//通常時の移動処理をまとめた関数
		bool NormalMove();
		//現在のm_statusFlagsの状態を確認する関数
		bool GetStatusFlag(PlayerStatus status);
		//m_statusFlagsのセッター
		void SetStatusFlag(PlayerStatus status, bool b);
		//腕の位置を返す関数(trueで右、falseで左)
		Vec3 GetArmPos(bool LR)
		{
			if (LR)
			{
				return m_armPos[0];
			}
			return m_armPos[1];
		}
		//ケーブルがコンセントに刺さっているかどうかを確認する関数
		void PlagInCheck();
		// プレイヤーのモデルを変更する関数
		void ChangePlayerModel(const wstring& string);
		// プレイヤーが操作可能かどうかを変更する関数
		void SetIsControl(bool isControl) { m_isControl = isControl; }
		void OnDestory2();
		void OnDestory1();
		void PlayerBGM1();
		void PlayerBGM2();

		// ゲームオーバーになったときに呼び出す関数
		void OnGameOver(float delay, bool isPause);

	};


}
//end basecross

