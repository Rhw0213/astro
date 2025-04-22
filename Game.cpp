#include "Game.h"
#include "Common.h"
#include "raylib.h"
#include "Frame.h"

namespace astro
{
	Game::Game()
	{
		InitWindow(astro::SCREEN_WIDTH, astro::SCREEN_HEIGHT, "Game");
		SetTargetFPS(60);
	}

	Game::~Game()
	{
		CloseWindow();
	}

	void Game::Init()
	{
		//Manager
		gameObjects = std::make_unique<ObjectManager>();
		systemManager = std::make_unique<SystemManager>();

		//UI
		uiControll = std::make_shared<UIControll>();
		//systemManager.get()->RegisterObjectOfSystem(uiControll);

		//uiControll->Init();

		// PLAYER
		auto player = gameObjects.get()->CreateObject<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		auto playerFrame = gameObjects.get()->CreateObject<Frame>(player.get()->GetInstanceID());

		systemManager.get()->RegisterObjectOfSystem(player);
		systemManager.get()->RegisterObjectOfSystem(playerFrame);

		// STAR
		for (size_t i = 0; i < 200; i++)
		{
			auto star = gameObjects.get()->CreateObject<Star>();
			systemManager.get()->RegisterObjectOfSystem(star);
		}

		//asteroid
		for (size_t i = 0; i < 10; i++)
		{
			auto asteroid = gameObjects.get()->CreateObject<Asteroid>();
			systemManager.get()->RegisterObjectOfSystem(asteroid);
		}

		gameObjects.get()->Init();
		systemManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			gameObjects.get()->Update();
			systemManager->Update();

			systemManager->Draw();
		}
	}
}
