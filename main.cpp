#include <Novice.h>

// C++
#include <memory>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Enemy.h"
#include "InputManager.h"
#include "IScene.h"
#include "InputHandler.h"

const char kWindowTitle[] = "LC2A_21_ヤラ_チョウセイ";

// タイトル
class TitleScene : public IScene {
public:
	// IScene を介して継承されました
	void Initialize() override
	{
	}
	void Update() override
	{
	}
	void Draw() override
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
	}
	void ChangeScene() override
	{
		SetNextScene("GameScene");
	}
};

// ゲーム
class GameScene : public IScene {
public:
	// IScene を介して継承されました
	void Initialize() override
	{
		bgTextureHandle_ = Novice::LoadTexture("./bg.png");
		expTextureHandle_ = Novice::LoadTexture("./explode.png");

		inputHandler = std::make_unique<InputHandler>();
		inputHandler->AssignMoveLeftCommand2PressKeyA();
		inputHandler->AssignMoveRightCommand2PressKeyD();

		player_ = std::make_unique<Player>();
		player_->Initialize();
		player_->SetInput(inputManager_);

		enemy_ = std::make_unique<Enemy>();
		enemy_->Initialize();
	}
	void Update() override
	{
		posY1 += 1;
		posY2 += 1;
		if (posY1 == 400) {
			posY1 = -400;
		}
		if (posY2 == 400) {
			posY2 = -400;
		}
		ICommand* newCommand = inputHandler->HandleInput();
		
		if (newCommand) {
			command_ = newCommand;
		}

		if (this->command_) {
			command_->Execute(*player_.get());
		}

		player_->Update();
		enemy_->Update();
	}
	void Draw() override
	{
		Novice::DrawSprite(posX1, posY1, bgTextureHandle_, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(posX2, posY2, bgTextureHandle_, 1, 1, 0.0f, 0xFFFFFFFF);

		player_->Draw();
		enemy_->Draw();
	}
	void ChangeScene() override
	{
		SetNextScene("ClearScene");
	}
private:
	int bgTextureHandle_ = 0;
	int expTextureHandle_ = 0;
	int posX1 = 0;
	int posX2 = 0;
	int posY1 = 0;
	int posY2 = -400;

	// Player
	std::unique_ptr<Player> player_ = nullptr;
	// Enemy
	std::unique_ptr<Enemy> enemy_ = nullptr;

	std::unique_ptr<InputHandler> inputHandler = nullptr;
	ICommand* command_ = nullptr;
};

// クリア
class ClearScene : public IScene {
public:
	// IScene を介して継承されました
	void Initialize() override
	{
	}
	void Update() override
	{
	}
	void Draw() override
	{
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED, kFillModeSolid);
	}
	void ChangeScene() override
	{
		SetNextScene("TitleScene");
	}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>();// インプットマネージャを生成
	std::unique_ptr<IScene> scene = std::make_unique<GameScene>();
	scene->SetInput(inputManager.get());
	scene->Initialize();

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		inputManager->Update();

		///
		/// ↓更新処理ここから
		///
		
		// シーンの更新
		scene->Update();

		// シーンの切り替え
		/*if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			scene->ChangeScene();
			std::unique_ptr<IScene> nextScene = nullptr;
			if (scene->GetNextScene() == "TitleScene") {
				nextScene = std::make_unique<TitleScene>();
				nextScene->SetInput(inputManager.get());
				nextScene->Initialize();
			}
			else if (scene->GetNextScene() == "GameScene") {
				nextScene = std::make_unique<GameScene>();
				nextScene->SetInput(inputManager.get());
				nextScene->Initialize();
			}
			else if (scene->GetNextScene() == "ClearScene") {
				nextScene = std::make_unique<ClearScene>();
				nextScene->SetInput(inputManager.get());
				nextScene->Initialize();
			}
			if (nextScene) {
				scene = std::move(nextScene);
			}
		}*/

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		scene->Draw();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
