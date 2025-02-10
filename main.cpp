#include <Novice.h>

// C++
#include <memory>
#include <string>
#include <algorithm>

const char kWindowTitle[] = "LC2A_21_ヤラ_チョウセイ";

struct Vector2Int final{
	int x = 0;
	int y = 0;
};

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

class BaseCharacter {
public:
	BaseCharacter() {}
	virtual ~BaseCharacter() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class Player : public BaseCharacter {
public:
	Player() {}
	~Player() {}
	void Initialize() override {}
	void Update() override {
		if (input_->IsKeyHeld(DIK_W) && pos_.y > 25) {
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
		}
		Shot();
	}
	void Draw() override {
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
	void SetInput(InputManager* inputManager) { input_ = inputManager; }
private:
	void Shot() {
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
private:
	Vector2Int pos_ = { 640,360 };
	const inline static int kSpeed = 5;

	// バレット
	Vector2Int bulletPos_ = { 0,0 };
	bool isBulletActive_ = false;

	// Input
	InputManager* input_ = nullptr;
};

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

// シーンインタフェース
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

	std::unique_ptr<IScene> scene = std::make_unique<TitleScene>();// タイトルシーンを生成
	scene->Initialize();
	std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>();// インプットマネージャを生成

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
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
		}

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
