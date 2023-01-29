#pragma once

/*
TVector2D
Class for handling X, Y positioning in Game.
*/
template <typename T>
class TVector2D
{
public:
	T x;
	T y;
	TVector2D()
	{
		x = 0;
		y = 0;
	}
	TVector2D<T>(T X, T Y)
	{
		x = X;
		y = Y;
	}
	TVector2D<T>& operator+(TVector2D<T>& vectorTwo)
	{
		return vectorTwo;
	};
	TVector2D<T>& operator+=(TVector2D<T>& vectorTwo)
	{
		x = vectorTwo.x;
		y = vectorTwo.y;
		return *this;
	};
	bool operator==(const TVector2D<T>& vectorTwo)
	{
		return (x == vectorTwo.x) && (y == vectorTwo.y);
	};
	bool operator!=(const TVector2D<T>& vectorTwo)
	{
		return !(this == vectorTwo);
	};
};