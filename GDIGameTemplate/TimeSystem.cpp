#include "stdafx.h"
#include "TimeSystem.h"
#include <cmath>

namespace Time
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	float deltaTime;

	void InitTime()
	{
		QueryPerformanceFrequency(&frequency);	// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
		QueryPerformanceCounter(&prevCounter);  // �ʱ� TickCount ��
	}

	void UpdateTime()
	{
		QueryPerformanceCounter(&currentCounter); // ���� TickCount ��
		deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) /
			static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

		prevCounter = currentCounter;
	}	

	float GetDeltaTime() 
	{ 
		return deltaTime; 
	}

}