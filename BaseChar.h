#pragma once
#include "Vector2Int.h"
class BaseCharacter {
public:
	BaseCharacter() {}
	virtual ~BaseCharacter() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};