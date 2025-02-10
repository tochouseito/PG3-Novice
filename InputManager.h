#pragma once
#include <Novice.h>
class InputManager {
public:
	InputManager() {}
	~InputManager() {}
	void Update() {
		memcpy(preKeys_, keys_, 256);
		Novice::GetHitKeyStateAll(keys_);
	}
	bool IsKeyPushed(int key) {
		return keys_[key] && !preKeys_[key];
	}
	bool IsKeyHeld(int key) {
		return keys_[key];
	}
	bool IsKeyReleased(int key) {
		return !keys_[key] && preKeys_[key];
	}
private:
	char keys_[256] = { 0 };
	char preKeys_[256] = { 0 };
};