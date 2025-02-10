#include "Player.h"
#include "InputManager.h"

void Player::Initialize()
{
}

void Player::Update() {
	/*if (input_->IsKeyHeld(DIK_W) && pos_.y > 25) {
		pos_.y = pos_.y - kSpeed;
	}
	if (input_->IsKeyHeld(DIK_S) && pos_.y < 655) {
		pos_.y = pos_.y + kSpeed;
	}
	if (input_->IsKeyHeld(DIK_A) && pos_.x > 25) {
		pos_.x = pos_.x - kSpeed;
	}
	if (input_->IsKeyHeld(DIK_D) && pos_.x < 1255) {
		pos_.x = pos_.x + kSpeed;
	}*/
	Shot();
}

void Player::Draw() {
	Novice::DrawEllipse(pos_.x, pos_.y, 25, 25, 0.0f, WHITE, kFillModeSolid);
	if (isBulletActive_) {
		Novice::DrawTriangle(
			bulletPos_.x - 10, bulletPos_.y,
			bulletPos_.x + 10, bulletPos_.y,
			bulletPos_.x, bulletPos_.y - 20,
			GREEN, kFillModeSolid
		);
	}
}

void Player::MoveRight() {
	this->pos_.x += this->kSpeed;
}

void Player::MoveLeft() {
	this->pos_.x -= this->kSpeed;
}

void Player::Shot() {
	if (input_->IsKeyHeld(DIK_F)) {
		if (!isBulletActive_) {
			isBulletActive_ = true;
			bulletPos_.x += pos_.x;
			bulletPos_.y += pos_.y;
		}
	}
	if (isBulletActive_) {
		bulletPos_.y -= 5;
		if (bulletPos_.y <= 0) {
			isBulletActive_ = false;
			bulletPos_ = { 0,0 };
		}
	}
}
