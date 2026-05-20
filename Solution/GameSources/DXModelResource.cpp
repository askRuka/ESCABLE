#include "stdafx.h"
#include "DXModelResource.h"
#include <windows.h>
#include <string>
#include <memory>

using namespace dxm;

namespace
{
	// UTF-8 → std::wstring 変換（既存と同様）
	std::wstring Utf8ToWide(const std::string& utf8)
	{
		if (utf8.empty()) return {};

		const int len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(), (int)utf8.size(), nullptr, 0);
		if (len <= 0) return {};

		std::wstring w(len, L'\0');
		MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(), (int)utf8.size(), &w[0], len);
		return w;
	}

	// パスユーティリティ（簡易）
	std::wstring CombinePath(const std::wstring& baseDir, const std::wstring& filename)
	{
		if (baseDir.empty()) return filename;
		if (filename.empty()) return baseDir;
		const wchar_t last = baseDir.back();
		if (last == L'\\' || last == L'/') return baseDir + filename;
		return baseDir + L'\\' + filename;
	}

	std::wstring GetParentPath(const std::wstring& path)
	{
		if (path.empty()) return {};
		auto pos1 = path.find_last_of(L"\\/");
		if (pos1 == std::wstring::npos) return {};
		if (pos1 == 2 && path.size() > 2 && path[1] == L':') return path.substr(0, 3);
		return path.substr(0, pos1);
	}

	std::wstring GetFileNameFromPath(const std::wstring& path)
	{
		if (path.empty()) return {};
		auto pos = path.find_last_of(L"\\/");
		if (pos == std::wstring::npos) return path;
		return path.substr(pos + 1);
	}

	bool PathExists(const std::wstring& path)
	{
		if (path.empty()) return false;
		DWORD attrs = GetFileAttributesW(path.c_str());
		return (attrs != INVALID_FILE_ATTRIBUTES);
	}

	// 単純なフォールバック探索
	std::wstring FindTexturePathFallback(const std::wstring& baseDir, const std::wstring& filename)
	{
		if (filename.empty()) return {};

		// direct
		{
			const std::wstring direct = CombinePath(baseDir, filename);
			if (PathExists(direct)) return direct;
		}

		std::wstring search = baseDir;
		if (search.empty()) search = L".";
		if (search.back() != L'\\' && search.back() != L'/') search.push_back(L'\\');
		search.push_back(L'*');

		WIN32_FIND_DATAW fd;
		HANDLE hFind = FindFirstFileW(search.c_str(), &fd);
		if (hFind == INVALID_HANDLE_VALUE) return {};

		std::wstring result;
		do
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
			std::wstring cand = fd.cFileName;
			if (cand == filename)
			{
				result = CombinePath(GetParentPath(search), cand);
				break;
			}
		} while (FindNextFileW(hFind, &fd) != 0);

		FindClose(hFind);
		return result;
	}
}

namespace basecross
{
	DXModelResource::DXModelResource()
		: MultiMeshResource()
		, m_dxModel()
	{
	}

	DXModelResource::~DXModelResource()
	{
	}

	void DXModelResource::SetDXModel(const shared_ptr<DXModel>& model)
	{
		m_dxModel = model;
	}

	shared_ptr<DXModel> DXModelResource::GetDXModel() const
	{
		return m_dxModel;
	}

	shared_ptr<DXModelResource> DXModelResource::RegisterFromFile(
		const wstring& key,
		const wstring& modelPath,
		bool accessWrite)
	{
		// 今は未実装。必要なら AssimpLoader と CreateDXModelFromScene を使って実装してください。
		return nullptr;
	}

	std::shared_ptr<DXModelResource> DXModelResource::RegisterDXModel(
		const wstring& key,
		const shared_ptr<DXModel>& model,
		bool accessWrite
	)
	{
		if (!model)
		{
			throw BaseException(
				L"DXModel が null です",
				L"if (!model)",
				L"DXModelResource::RegisterDXModel()"
			);
		}

		auto res = ObjectFactory::Create<DXModelResource>();
		res->SetDXModel(model);

		const std::wstring baseDir = model->m_filePath; // 基本ディレクトリ/パス

		for (size_t mi = 0; mi < model->meshes.size(); ++mi)
		{
			const auto& mesh = model->meshes[mi];

			vector<VertexPositionNormalTextureSkinning> vertices;
			vertices.resize(mesh.vertices.size());
			for (size_t vi = 0; vi < mesh.vertices.size(); ++vi)
			{
				const auto& v = mesh.vertices[vi];

				VertexPositionNormalTextureSkinning out{};
				out.position = bsm::Vec3(v.pos.x, v.pos.y, v.pos.z);
				out.normal = bsm::Vec3(v.normal.x, v.normal.y, v.normal.z);
				out.textureCoordinate = bsm::Vec2(v.uv.x, v.uv.y);

				out.indices[0] = static_cast<uint32_t>(v.boneIndices.x);
				out.indices[1] = static_cast<uint32_t>(v.boneIndices.y);
				out.indices[2] = static_cast<uint32_t>(v.boneIndices.z);
				out.indices[3] = static_cast<uint32_t>(v.boneIndices.w);

				out.weights[0] = v.weights.x;
				out.weights[1] = v.weights.y;
				out.weights[2] = v.weights.z;
				out.weights[3] = v.weights.w;

				vertices[vi] = out;
			}

			vector<uint16_t> indices;
			indices.resize(mesh.indices.size());
			for (size_t ii = 0; ii < mesh.indices.size(); ++ii)
			{
				if (mesh.indices[ii] > 0xFFFFu)
				{
					indices[ii] = 0;
					continue;
				}
				indices[ii] = static_cast<uint16_t>(mesh.indices[ii]);
			}

			auto meshRes = MeshResource::CreateMeshResource<VertexPositionNormalTextureSkinning>(vertices, indices, accessWrite);

			auto data = meshRes->GetMashData();
			data.m_IsSkining = true;
			data.m_BoneCount = static_cast<UINT>(model->bones.size());
			data.m_SampleCount = 1;
			data.m_MultiMeshIndex = static_cast<UINT>(mi);

			data.m_SampleMatrixVec.clear();
			data.m_SampleMatrixVec.resize(static_cast<size_t>(data.m_BoneCount));
			for (auto& m : data.m_SampleMatrixVec)
			{
				m.identity();
			}

			data.m_MaterialExVec.clear();

			MaterialEx mat{};
			mat.m_StartIndex = 0;
			mat.m_IndexCount = static_cast<UINT>(indices.size());
			mat.m_Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
			mat.m_Specular = bsm::Col4(0.0f, 0.0f, 0.0f, 1.0f);
			mat.m_Ambient = bsm::Col4(0.0f, 0.0f, 0.0f, 1.0f);
			mat.m_Emissive = bsm::Col4(0.0f, 0.0f, 0.0f, 1.0f);

			if (mesh.materialIndex < model->materials.size())
			{
				const auto& srcMat = model->materials[mesh.materialIndex];

				mat.m_Diffuse = bsm::Col4(srcMat.diffuseColor.x, srcMat.diffuseColor.y, srcMat.diffuseColor.z, srcMat.diffuseColor.w);
				mat.m_Specular = bsm::Col4(srcMat.specularColor.x, srcMat.specularColor.y, srcMat.specularColor.z, srcMat.specularColor.w);
				mat.m_Ambient = bsm::Col4(srcMat.ambientColor.x, srcMat.ambientColor.y, srcMat.ambientColor.z, srcMat.ambientColor.w);
				mat.m_Emissive = bsm::Col4(srcMat.emissiveColor.x, srcMat.emissiveColor.y, srcMat.emissiveColor.z, srcMat.emissiveColor.w);

				if (!srcMat.textureFilename.empty())
				{
					std::wstring texFullPath = CombinePath(baseDir, srcMat.textureFilename);

					if (!PathExists(texFullPath))
					{
						const std::wstring parent = GetParentPath(baseDir);
						if (!parent.empty())
						{
							std::wstring fallback = FindTexturePathFallback(parent, srcMat.textureFilename);
							if (!fallback.empty())
							{
								texFullPath = fallback;
							}
						}
					}

					if (PathExists(texFullPath))
					{
						const wstring texKey = key + L":tex:" + GetFileNameFromPath(texFullPath);
						auto texRes = App::GetApp()->RegisterTexture(texKey, texFullPath, L"WIC");
						mat.m_TextureResource = texRes;
					}
				}
			}

			data.m_MaterialExVec.push_back(std::move(mat));

			meshRes->SetMashData(data);
			res->AddMesh(meshRes);
		}

		App::GetApp()->RegisterResource(key, res);
		return res;
	}
}