#include "InputHandler.h"
#include <Novice.h>

ICommand* InputHandler::HandleInput()
{
	if (Novice::CheckHitKey(DIK_D)) {
		return pressKeyD_.get();
	}
	if (Novice::CheckHitKey(DIK_A)) {
		return pressKeyA_.get();
	}
	return nullptr;
}

void InputHandler::AssignMoveRightCommand2PressKeyD()
{
	//ICommand* command = new MoveRightCommand();
	this->pressKeyD_ = std::make_unique<MoveRightCommand>();
}

void InputHandler::AssignMoveLeftCommand2PressKeyA()
{
	//ICommand* command = new MoveLeftCommand();
	this->pressKeyA_ = std::make_unique<MoveLeftCommand>();
}
