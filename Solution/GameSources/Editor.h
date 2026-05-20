/*!
@file Editor.h
@brief ステージのエディター
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Editor : public GameObject;
	//--------------------------------------------------------------------------------------
	class Editor : public GameObject
	{
		weak_ptr<GameObject> m_pickObj;
		Col4 m_picObjCol;
		bool m_isEditorMode;
		int m_changeTransform; // ０が座標、１がサイズ、２が回転、３が移動ベクトル
		Vec3 m_pastMauseRay[2]; // ０がスタート（近いほう）、１がエンド（遠いほう）
		Vec3 m_objPos;
		Vec3 m_objScale;
		Vec3 m_objRot;
		Vec3 m_objRotBase;
		Vec3 m_objVel;
		int m_addObjNum;
		float m_snapSize;
		int m_stageNum;
		weak_ptr<GameObject> m_arrow;
		weak_ptr<GameObject> m_mark;
		weak_ptr<GameObject> m_cursor;
		shared_ptr<GameObject> PickUpGameObject();
		// 入力の取得
		Vec3 GetInputVec();
		void ResetPickUpObject(); // 選択しているオブジェクトのリセット
		void MovePickUpObject(wstringstream& ss);
		void CopyObject();
		int CheckObjectID(const shared_ptr<GameObject> obj);
	public:
		// 構築と破棄
		Editor(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_isEditorMode(false),
			m_changeTransform(0),
			m_addObjNum(0),
			m_snapSize(1.0f)
		{
		}
		virtual ~Editor()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		//ステージのデータをバイナリファイルで保存する
		void SaveBinaryFile(const wstring& filename);
		void SetObjectEmissive(const shared_ptr<GameObject>& obj,const Col4& col, bool b);
		void GetMouseRay(Vec3& start, Vec3& end);

		void AddNewObject();
	};

}
//end basecross
