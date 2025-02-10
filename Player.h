#pragma once

#include "BaseChar.h"

class InputManager;

class Player : public BaseCharacter {
public:
	Player() {}
	~Player() {}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void SetInput(InputManager* inputManager) { input_ = inputManager; }
	void MoveRight();
	void MoveLeft();
private:
	void Shot();
private:
	Vector2Int pos_ = { 640,360 };
	const inline static int kSpeed = 5;

	// Bullet
	Vector2Int bulletPos_ = { 0,0 };
	bool isBulletActive_ = false;

	// Input
	InputManager* input_ = nullptr;
};