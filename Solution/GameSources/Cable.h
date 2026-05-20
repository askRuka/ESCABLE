/*!
@file Cable.h
@brief ケーブルなど
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "PNTDXModelDraw.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Cable : public GameObject;
	//--------------------------------------------------------------------------------------
	class Cable : public GameObject
	{
		std::shared_ptr<PCTStaticDraw> m_draw;

		Vec3 m_startPosition; // 線分の始点且つ、このオブジェクトの原点
		Vec3 m_endPosition; // 線分の終点

		Col4 m_startColor; // 始点の色
		//Col4 m_endColor; // 終点の色

		// 線分用のメッシュデータ
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		std::weak_ptr<GameObject> m_player; // 発射元のプレイヤー
		std::weak_ptr<PNTDXModelDraw> m_playerDraw; // プレイヤーのDrawコンポーネント
		std::wstring m_armBoneName; // 腕のボーンの名前

		std::weak_ptr<GameObject> m_hitObj; //当たったオブジェクト
		std::unique_ptr<StateMachine<Cable>> m_stateMachine; // ケーブルのステートマシン
		Vec3 m_hitPosition;	//当たった座標
		Vec3 m_moveVelocity; // 移動時の動きのベクトル
		static const int m_cablePosNum = 10;
		Vec3 m_cablePositions[m_cablePosNum]; // ケーブルの各座標の配列(0がスタート近くでそこからエンドに近くなっていく)
		bool m_isCollide[m_cablePosNum]; // ケーブルがほかのオブジェクトに接触しているかどうかのフラグ
		std::weak_ptr<GameObject> m_collisionObject[m_cablePosNum]; // 接触しているオブジェクトのポインタ（オブジェクトが移動しているときに使う）
		Vec3 m_collisionObjPos[m_cablePosNum];
		bool m_isHit; //コンセントに当たったかどうかのフラグ
		bool m_LR; // LRのフラグ(trueで右、falseで左)
		float m_length; // ケーブルの長さ
		float m_throwLength; // 投げた時の射程距離
		float m_size; // ケーブルの太さ
		float m_upAttenuation; // ケーブルを投げた時の上方向への減衰
		std::shared_ptr<GameObject> m_cableTip; // ケーブルの先端
		std::shared_ptr<SoundItem> m_SE; // ケーブル用ののSE
		void AdjustCablePosition();
		void MoveCollidePosition();
		Vec3 CalcHitPosition(); // コンセントなどに当たった時のヒットポジションを計算する関数
	public:
		// 構築と破棄
		Cable(const shared_ptr<Stage>& stage, bool LR) :
			GameObject(stage),
			m_startPosition(Vec3(0)),
			m_endPosition(Vec3(0)),
			m_startColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
			//m_endColor(Col4(0.0f, 0.0f, 0.0f, 1.0f)),
			m_hitPosition(Vec3(0)),
			//m_isCollide(false),
			m_isHit(false),
			m_LR(LR),
			m_length(40),
			m_throwLength(35),
			m_size(0.1f),
			m_upAttenuation(0.0f)
		{
		}
		virtual ~Cable()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		//プレイヤーの設定
		void SetPlayer(const shared_ptr<GameObject>& player);
		//ケーブルのポジション設定
		void SetCablePosition()
		{
			m_vertices.clear();
			// ケーブルの頂点データの作成
			auto endPos = m_endPosition; // 計算部分の終点座標
			auto adjustPos = endPos;
			float texLength = 0;
			float length = m_length - GetRemainingLength(m_startPosition);
			for (auto& pos : m_cablePositions)
			{
				auto camera = GetStage()->GetView()->GetTargetCamera();
				auto gaze = camera->GetAt() - camera->GetEye();
				auto dis = endPos - pos;
				if (dis.length() < 0.05f)
				{
					dis = adjustPos - pos;
				}
				else
				{
					adjustPos = endPos;
				}
				auto cross = Vec3(gaze.y * dis.z - gaze.z * dis.y, gaze.z * dis.x - gaze.x * dis.z, gaze.x * dis.y - gaze.y * dis.x);
				cross = cross.normalize() * m_size;
				VertexPositionColorTexture vertice = { endPos - cross, m_startColor, Vec2(texLength / m_length,1) };
				m_vertices.push_back(vertice);
				vertice = { endPos + cross, m_startColor, Vec2(texLength / m_length, 0) };
				m_vertices.push_back(vertice);
				texLength += Vec3(endPos - pos).length();
				endPos = pos;
			}
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto gaze = camera->GetAt() - camera->GetEye();
			auto dis = endPos - m_startPosition;
			auto cross = Vec3(gaze.y * dis.z - gaze.z * dis.y, gaze.z * dis.x - gaze.x * dis.z, gaze.x * dis.y - gaze.y * dis.x);
			cross = cross.normalize() * m_size;
			VertexPositionColorTexture vertice = { endPos - cross, m_startColor, Vec2(texLength / m_length,1) };
			m_vertices.push_back(vertice);
			vertice = { endPos + cross, m_startColor, Vec2(texLength / m_length, 0) };
			m_vertices.push_back(vertice);
			texLength += Vec3(endPos - m_startPosition).length();

			vertice = { m_startPosition - cross,m_startColor, Vec2(texLength / m_length,1) };
			m_vertices.push_back(vertice);
			vertice = { m_startPosition + cross,m_startColor, Vec2(texLength / m_length, 0) };
			m_vertices.push_back(vertice);

			m_draw->UpdateVertices(m_vertices);
		}
		//ケーブルのヒット判定を確認する
		bool HitCheck();
		//ケーブルが投げられた時の関数
		bool OnThrow(const Vec3& throwPos);
		//投げられた時の動きの関数
		bool ThrowMove();
		//Hitせずに戻ったときの動き
		bool BackMove();
		//戻るときの初期化
		void BackMoveInit();
		//ステートマシンのゲッター
		const unique_ptr<StateMachine<Cable>>& GetStateMachine() {
			return m_stateMachine;
		}
		//m_isHitのゲッター
		bool GetIsHit() { return m_isHit; }
		//hitObjを返すゲッター
		shared_ptr<GameObject> GetHitObject();
		//ステートマシンからhitObjを初期化するための関数
		void ResetHitObj();
		//Playerのステータスの変更をする関数
		void ChangePlayerStatus(int status, bool b);
		//Player側へ現在のステータスの状況を確認してもらう関数
		void PlayerCheckStatus();
		//ケーブルのほかのオブジェクトとの接触を確認する関数
		void CheckCollide();
		//ケーブルの長さがm_lengthを超えているかどうかを確認する関数
		bool ChackLength(const Vec3& pos);
		//プラグイン状態のときにElectrincTriggerに状態を送る関数
		void StateSendToTrigger();
		//残りの距離を返す関数
		float GetRemainingLength(const Vec3& pos);
		//ケーブルの方向ベクトルを返す関数
		Vec3 GetCableDirection();
		// プレイヤーのDrawコンポーネントを設定する関数
		void SetPlayerDraw(const shared_ptr<GameObject>& target)
		{
			m_playerDraw = target->GetComponent<PNTDXModelDraw>();
		}
		// 腕のボーンの名前を設定する関数
		void SetArmBoneName(const std::wstring& boneName)
		{
			m_armBoneName = boneName;
		}
		void TipMove();
		void TipState();
		void SEStart(const wstring& name);
		void SEStop();
		// 当たるかどうかで照準を状態を変える関数
		void GuideCheck();
	};

}
//end basecross
