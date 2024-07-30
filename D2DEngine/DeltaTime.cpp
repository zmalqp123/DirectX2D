#include "pch.h"
#include "DeltaTime.h"
#include "cmath"
#include <iostream>
void DeltaTime::InitTime()
{
	QueryPerformanceFrequency(&frequency);	// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
	QueryPerformanceCounter(&prevCounter);  // �ʱ� TickCount ��
}

void DeltaTime::UpdateTime()
{
	QueryPerformanceCounter(&currentCounter); // ���� TickCount ��
	deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) /
		static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

	prevCounter = currentCounter;
}

float DeltaTime::GetDeltaTime()
{
	return deltaTime;
}

float DeltaTime::GetFPS()
{
	return 1.0f / deltaTime;
}
