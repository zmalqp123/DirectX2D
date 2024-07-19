#include "Player.h"
#include <iostream>
using namespace std;
void Player::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	cout << "Block" << endl;
}

void Player::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	cout << "enter" << endl;
}

void Player::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	cout << "exit" << endl;
}
