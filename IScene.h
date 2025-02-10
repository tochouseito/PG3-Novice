#pragma once
#include <string>
class InputManager;
class IScene {
public:
	virtual ~IScene() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetNextScene(const std::string& nextSceneName) { nextSceneName_ = nextSceneName; }
	virtual std::string GetNextScene() { return nextSceneName_; }
	virtual void ChangeScene() = 0;
	virtual void SetInput(InputManager* inputManager) {
		inputManager_ = inputManager;
	}
protected:
	std::string nextSceneName_ = {};
	InputManager* inputManager_ = nullptr;
};