/*!
@file StageLoader.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void StageLoader::LoadStageFile(const wstring& filename)
	{
		ifstream ifs(filename, std::ios::binary);
		if (ifs.fail()) {
			MessageBox(0, L"ステージファイルを開けませんでした", L"failed", 0);
			return;
		}

		// オブジェクトの数を書き込む
		uint32_t num;
		ifs.read((char*)&num, sizeof(num)); // はじめの4バイトとして、オブジェクト数を書き込む

		// 処理のためのオブジェクトグループの作成
		auto lifts = GetStage()->CreateSharedObjectGroup(L"Lifts");
		auto stageObj = GetStage()->CreateSharedObjectGroup(L"StageObjects");

		for (int i = 0; i < num; i++)
		{
			// 必要になる変数の初期化（switvh文内で宣言できなかったので）
			uint16_t id = 0;
			Vec3 objScale;
			Vec3 objRot;
			Vec3 objPos;
			Vec3 velocity;
			Vec3 switchScale;
			Vec3 switchRot;
			Vec3 switchPos;
			float fire;
			float fade;
			float delay;
			shared_ptr<Door> door;
			shared_ptr<ElectricTrigger> trigger;
			shared_ptr<GameObjectForEdit> object;


			// データを書き込む
			ifs.read((char*)&id, sizeof(id)); // オブジェクトID
			ifs.read((char*)&objScale, sizeof(objScale)); // スケール
			ifs.read((char*)&objRot, sizeof(objRot)); // 回転
			ifs.read((char*)&objPos, sizeof(objPos)); // 座標
			switch (id)
			{
			case 1:
				object = GetStage()->AddGameObject<Wall>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				stageObj->IntoGroup(object);
				break;
			case 2:
				object = GetStage()->AddGameObject<Floor>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				stageObj->IntoGroup(object);
				break;
			case 3:
				object = GetStage()->AddGameObject<Consent>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				break;
			case 4:
				ifs.read((char*)&velocity, sizeof(velocity)); // 座標
				object = GetStage()->AddGameObject<Lift>(objScale, objRot, objPos, velocity);
				object->SetMenberRotation(objRot);
				lifts->IntoGroup(object);
				break;
			case 5:
				object = GetStage()->AddGameObject<Piller>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				stageObj->IntoGroup(object);
				break;

			case 6:
				object = GetStage()->AddGameObject<Roof>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				stageObj->IntoGroup(object);
				break;

			case 7:
				ifs.read((char*)&switchScale, sizeof(switchScale)); // スケール
				ifs.read((char*)&switchRot, sizeof(switchRot)); // 回転
				ifs.read((char*)&switchPos, sizeof(switchPos)); // 座標
				door = GetStage()->AddGameObject<Door>(objScale, objRot, objPos);
				door->SetMenberRotation(objRot);
				stageObj->IntoGroup(door);
				trigger = GetStage()->AddGameObject<ElectricTrigger>(switchScale, switchRot, switchPos);
				trigger->SetMenberRotation(objRot);
				door->SwitchSetter(trigger);
				break;
			case 8:
				ifs.read((char*)&velocity, sizeof(velocity)); // 移動量
				ifs.read((char*)&fire, sizeof(fire));
				ifs.read((char*)&fade, sizeof(fade));
				ifs.read((char*)&delay, sizeof(delay));
				object = GetStage()->AddGameObject<Luncher>(objScale, objRot, objPos, velocity, fire, fade, delay);
				object->SetMenberRotation(objRot);
				break;
			case 9:
				object = GetStage()->AddGameObject<Checkpoint>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				break;
			case 10:
				object = GetStage()->AddGameObject<Enemy>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				break;
			case 11:
				object = GetStage()->AddGameObject<ClearObject>(objScale, objRot, objPos);
				object->SetMenberRotation(objRot);
				break;
			case 12:
				object = GetStage()->AddGameObject<ObstacleForCamera>(objScale, objRot, objPos);
				break;
			default:
				break;
			}
		}

		// ファイルを閉じる
		ifs.close();

	}


}
//end basecross
