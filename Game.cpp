#include "Game.h"
#include "Common.h"
#include "raylib.h"
#include "Frame.h"
#include "FrameEffect.h"
#include "Player.h"
#include "Star.h"
#include "Asteroid.h"
#include "Setting.h"

namespace astro
{
	Game::Game()
	{
		InitWindow(astro::SCREEN_WIDTH, astro::SCREEN_HEIGHT, "Game");
		SetTargetFPS(60);

		if (!GameSettingManager::Instance().LoadFile())
		{
			return;
		}
	}

	Game::~Game()
	{
		CloseWindow();
	}

	void Game::Init()
	{
		//Manager
		objectManager = std::make_unique<ObjectManager>();
		systemManager = std::make_unique<SystemManager>(objectManager);

		//UI
		uiControll = std::make_shared<UIControll>();
		//systemManager.get()->RegisterObjectOfSystem(uiControll);

		//uiControll->Init();

		// PLAYER
		auto player = objectManager.get()->CreateObject<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });

		for (size_t i = 0; i < 10; i++)
		{
			auto frame = objectManager.get()->CreateObject<Frame>(player.get()->GetInstanceID());
			systemManager.get()->RegisterObjectOfSystem(frame);
		}
		auto frameEffect = objectManager.get()->CreateObject<FrameEffect>(player.get()->GetType());

		systemManager.get()->RegisterObjectOfSystem(frameEffect);
		systemManager.get()->RegisterObjectOfSystem(player);

		// STAR
		for (size_t i = 0; i < 300; i++)
		{
			auto star = objectManager.get()->CreateObject<Star>();
			systemManager.get()->RegisterObjectOfSystem(star);
		}

		//asteroid
		for (size_t i = 0; i < 10; i++)
		{
			auto asteroid = objectManager.get()->CreateObject<Asteroid>();
			systemManager.get()->RegisterObjectOfSystem(asteroid);
		}

		objectManager.get()->Init();
		systemManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			objectManager.get()->Update();
			systemManager->Update();

			systemManager->Draw();
		}
	}
}
