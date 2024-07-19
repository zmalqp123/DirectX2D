#include "pch.h"
#include "ResourceManager.h"
#include "SpriteAnimationAsset.h"
#include "Texture.h"
#include "Sprite.h"
#include "D2DRenderer.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto& m : m_TextureMap) {
		m.second->Release();
	}
	for (auto& m : m_AnimationAssetMap) {
		m.second->Release();
	}

	m_TextureMap.clear();
	m_AnimationAssetMap.clear();

	assert(m_BitmapMap.empty());
	assert(m_TextureMap.empty());	// map�ȿ� ���� release���ؼ� �׷��� ���߿� �ذ��ؾ���.
	assert(m_SpriteMap.empty());
	assert(m_AnimationAssetMap.empty());
}

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end())
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// ������ ���� ��������. D2D1Bitmap �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.

	D2DRenderer::getIncetance().CreateD2DBitmapFromFile(strFilePath.c_str(), bitmap);

	// ������ ��Ʈ���� �ʿ� �����Ѵ�.
	m_BitmapMap[strFilePath] = *bitmap;
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� ��Ʈ���� �����Ѵ�.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateTextureFromFile(std::wstring strFilePath, Texture** texture)
{
	if (m_TextureMap.find(strFilePath) != m_TextureMap.end())
	{
		*texture = m_TextureMap[strFilePath];
		(*texture)->AddRef();
		return true;
	}

	ID2D1Bitmap* temp = nullptr;
	auto hr = D2DRenderer::getIncetance().CreateD2DBitmapFromFile(strFilePath.c_str(), &temp);
	if (FAILED(hr)) 
		return false;
	else
		*texture = new Texture(strFilePath, temp);

	m_TextureMap[strFilePath] = *texture;
	return true;
}

void ResourceManager::ReleaseTexture(std::wstring strFilePath)
{
	std::map<std::wstring, Texture*>::iterator iter = m_TextureMap.find(strFilePath);
	assert(iter != m_TextureMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_TextureMap.end())
	{
		Texture* texture = m_TextureMap[strFilePath];
		if (texture->Release() == 0)
		{
			m_TextureMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateSpriteFromFile(std::wstring strFilePath, Sprite** sprite)
{
	return false;
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, SpriteAnimationAsset** asset)
{
	if (m_AnimationAssetMap.find(strFilePath) != m_AnimationAssetMap.end())
	{
		*asset = m_AnimationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// ������ ���� ��������. AnimationAsset �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.

	SpriteAnimationAsset* pTemp = new SpriteAnimationAsset;
	// ������ �ִϸ��̼� ���¿� �ִϸ��̼� �����͸� �ε��Ѵ�.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// ������ �ִϸ��̼� ������ �ʿ� �����Ѵ�.
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� �ִϸ��̼� ������ �����Ѵ�.
	std::map<std::wstring, SpriteAnimationAsset*>::iterator iter = m_AnimationAssetMap.find(strFilePath);
	assert(iter != m_AnimationAssetMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_AnimationAssetMap.end())
	{
		SpriteAnimationAsset* asset = m_AnimationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			m_AnimationAssetMap.erase(iter);
		}
	}
}
