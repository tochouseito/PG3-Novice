#pragma once
#include <memory>
#include "ICommand.h"
class InputHandler
{
public:
	ICommand* HandleInput();

	void AssignMoveRightCommand2PressKeyD();
	void AssignMoveLeftCommand2PressKeyA();
private:
	std::unique_ptr<ICommand> pressKeyD_ = nullptr;
	std::unique_ptr<ICommand> pressKeyA_ = nullptr;
};

