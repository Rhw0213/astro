#include "Game.h"
#include "Common.h"
#include "raylib.h"

namespace astro
{
	Game::Game()
	{
	}

	Game::~Game()
	{
		CloseWindow();
	}

	void Game::Init()
	{
		InitWindow(astro::SCREEN_WIDTH, astro::SCREEN_HEIGHT, "Game");
		SetTargetFPS(60);

		//Manager
		starManager = std::make_unique<ObjectManager>();
		asteroidManager = std::make_unique<ObjectManager>();
		systemManager = std::make_unique<SystemManager>();

		//UI
		uiControll = std::make_shared<UIControll>();
		systemManager.get()->RegisterObjectOfSystem(
			{	
				SystemManager::RENDER_SYSTEM,
				SystemManager::SHADER_SYSTEM,
			}, uiControll);

		uiControll->Init();

		// PLAYER
		player = std::make_shared<Player>(MyVector2{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });

		systemManager.get()->RegisterObjectOfSystem(
			{	
				SystemManager::RENDER_SYSTEM,
				SystemManager::MOVE_SYSTEM,
				SystemManager::INPUT_SYSTEM,
				SystemManager::CAMERA_SYSTEM,
				SystemManager::ROTATION_SYSTEM,
				SystemManager::SHADER_SYSTEM
			}, player);

		player.get()->Init();

		// STAR
		for (size_t i = 0; i < 200; i++)
		{
			std::shared_ptr<Star> star = starManager->CreateObject<Star>();

			systemManager.get()->RegisterObjectOfSystem(
				{	
					SystemManager::RENDER_SYSTEM,
					SystemManager::MOVE_SYSTEM,
					SystemManager::STAR_EFFECT_SYSTEM,
					SystemManager::WARP_SYSTEM,
			}, star);
		}
		starManager->Init();

		for (size_t i = 0; i < 10; i++)
		{
			std::shared_ptr<Asteroid> asteroid = asteroidManager->CreateObject<Asteroid>();

			systemManager.get()->RegisterObjectOfSystem(
				{
						SystemManager::RENDER_SYSTEM,
						SystemManager::MOVE_SYSTEM,
						SystemManager::ROTATION_SYSTEM
				}, asteroid);
		}
		asteroidManager->Init();

		systemManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			player->Update();
			starManager->Update();
			asteroidManager->Update();

			systemManager->Update();
			systemManager->Draw();
		}
	}
}
