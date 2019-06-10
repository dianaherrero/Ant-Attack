#pragma once

class Vector{
public:
	//virtual ~Vector2D();
	float x;
	float y;

public:
	Vector() { x = y = 0; }
	Vector(float fx, float fy) { x = fx; y = fy; }
};