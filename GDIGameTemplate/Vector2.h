#pragma once
struct Vector2
{
	float x,y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}
	
	void Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	/*		   x,y
	  |		    +  	
	  |         
	  |	       
	 -+---------->
	 0,0	   
	*/
	void Normalize()
	{
		float length = sqrt(x*x + y*y);	// ��Ÿ��� ������ �̿��Ͽ� ������ ����(0,0 -> x,y ������ �Ÿ�)�� ���Ѵ�.
		x /= length;	// ���̷� ������ ���� 1�� �ش�Ǵ� x,y ������ ���Ѵ�.   �� ������ ũ�Ⱑ 1�� ������ ������ ��Ÿ���� ���Ͱ� �ȴ�.
		y /= length;
	}

	float Length()
	{
		return sqrt(x*x + y*y);
	}
	// a + b;
	Vector2 operator+(const Vector2& v)
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(const Vector2& v)
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 operator*(float f)
	{
		return Vector2(x * f, y * f);
	}
	Vector2 operator/(float f)
	{
		return Vector2(x / f, y / f);
	}
	//  a += b;
	Vector2& operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2& operator*=(float f)
	{
		x *= f;
		y *= f;
		return *this;
	}
	Vector2& operator/=(float f)
	{
		x /= f;
		y /= f;
		return *this;
	}
	bool operator==(const Vector2& v)
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const Vector2& v)
	{
		return x != v.x || y != v.y;
	}	
};

