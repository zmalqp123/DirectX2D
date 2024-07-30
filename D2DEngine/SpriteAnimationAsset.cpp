#include "pch.h"
#include "SpriteAnimationAsset.h"

bool SpriteAnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//�ؽ�Ʈ ������ ��� csv���� ����� �о�´�.
	// �Ʒ� �Լ��� csv������ ó���Ѵ�.
	if (FilePath == std::wstring(L"../Resource/background.txt"))
	{
		return LoadAnimationFromCSV(0, FilePath.c_str());
	}
	if (FilePath == std::wstring(L"../Resource/midnight.txt"))
	{
		return LoadAnimationFromCSV(1, FilePath.c_str());
	}
	if (FilePath == std::wstring(L"Ken")) 
	{
		LoadAnimationFromCSV(0, L"../Resource/KenIdle.csv");
		LoadAnimationFromCSV(1, L"../Resource/KenMove.csv");
		LoadAnimationFromCSV(2, L"../Resource/KenAttack.csv");
	}
	if (FilePath == std::wstring(L"TheBullet")) {
		LoadAnimationFromCSV(0, L"../Resource/Animations/IdleDown.txt");
		LoadAnimationFromCSV(1, L"../Resource/Animations/IdleRight.txt");
		LoadAnimationFromCSV(2, L"../Resource/Animations/IdleRightUp.txt");
		LoadAnimationFromCSV(3, L"../Resource/Animations/IdleUp.txt");
		LoadAnimationFromCSV(4, L"../Resource/Animations/WalkDown.txt");
		LoadAnimationFromCSV(5, L"../Resource/Animations/WalkRight.txt");
		LoadAnimationFromCSV(6, L"../Resource/Animations/WalkRightUp.txt");
		LoadAnimationFromCSV(7, L"../Resource/Animations/WalkUp.txt");
		LoadAnimationFromCSV(8, L"../Resource/Animations/DodgeRollDown.txt");
		LoadAnimationFromCSV(9, L"../Resource/Animations/DodgeRollRight.txt");
		LoadAnimationFromCSV(10, L"../Resource/Animations/DodgeRollRightUp.txt");
		LoadAnimationFromCSV(11, L"../Resource/Animations/DodgeRollUp.txt");
	}
	return true;
}

bool SpriteAnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		std::wcout << fileName << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	int FrameCount = 0;			// �������� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_Animations[index].Frames.resize(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			m_Animations[index].Frames[j].Source.left = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.top = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.right = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.bottom = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Duration = (float)_wtof(token.c_str());
		}
	}

	return true;
}
