#pragma once
#include "BaseChar.h"
class Enemy : public BaseCharacter {
public:
	Enemy() {}
	~Enemy() {}
	void Initialize() override {
		isAlive_ = true;
		pos_.x = 600;
		pos_.y = 100;
		respownTime_ = 120;
	}
	void Update() override {
		if (isAlive_) {
			if (pos_.x >= 1230) {
				pos_.x -= kSpeed;
			}
			if (pos_.x <= 50) {
				pos_.x += kSpeed;
			}
		}
	}
	void Draw() override {
		Novice::DrawEllipse(pos_.x, pos_.y, 50, 50, 0.0f, RED, kFillModeSolid);
	}
private:
	Vector2Int pos_ = { 600,100 };
	const inline static int kSpeed = 3;

	bool isAlive_ = false;
	int respownTime_ = 120;
};