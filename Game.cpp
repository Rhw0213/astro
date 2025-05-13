#include "Game.h"
#include "Common.h"
#include "raylib.h"
#include "Frame.h"
#include "FrameManage.h"
#include "Player.h"
#include "Missile.h"
#include "Star.h"
#include "Asteroid.h"
#include "Setting.h"
#include <iostream> 

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
		objectManager = std::make_unique<ObjectManager>();
		systemManager = std::make_unique<SystemManager>(objectManager);
		
		CreateObject();

		objectManager.get()->Init();
		systemManager->Init();
	}

	void Game::Run()
	{
		while (!WindowShouldClose())
		{
			double start1 = GetTime();
			objectManager.get()->Update();
			double end1 = GetTime();

			double start2 = GetTime();
			systemManager.get()->Update();
			double end2 = GetTime();

			double start3 = GetTime();
			systemManager.get()->Draw();
			double end3 = GetTime();

			//std::cout << "===============================" << std::endl;
			//std::cout << "Update time: " << end1 - start1 << std::endl;
			//std::cout << "Logic  time: " << end2 - start2 << std::endl;
			//std::cout << "Draw   time: " << end3 - start3 << std::endl;
			//std::cout << "Frame  time: " << GetFrameTime() << std::endl;
			//std::cout << "===============================" << std::endl;
		}
	}

	void Game::CreateObject()
	{
		//UI
		//uiControll = std::make_shared<UIControll>();
		//systemManager.get()->RegisterObjectOfSystem(uiControll);
		//uiControll->Init();

		//PLAYER
		auto object = CreateObjectOfCount(ObjectType::PLAYER_ID, 1);
		{
			auto manage = CreateObjectManagePart(ObjectType::FRAME_MANAGE_ID, object, 1);
			CreateObjectPart(ObjectType::FRAME_ID, object, manage, 30);
		}

		// STAR
		CreateObjectOfCount(ObjectType::STAR_ID, 300);

		//asteroid
		//CreateObjectOfCount(ObjectType::ASTEROID_ID, 10);
	}

	void Game::CreateObjectPart(ObjectType type, std::shared_ptr<Object> owner, std::shared_ptr<Object> manage, int count)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (type == ObjectType::FRAME_ID)
			{ 
				auto object = objectManager->CreateObject<Frame>(owner->GetInstanceID(), manage->GetInstanceID());
				systemManager->RegisterObjectOfSystem(object);
			}
			else if (type == ObjectType::MISSILE_ID)
			{ 
				auto object = objectManager->CreateObject<Missile>(owner->GetInstanceID());
				systemManager->RegisterObjectOfSystem(object);
			}
		}
	}

	std::shared_ptr<Object> Game::CreateObjectManagePart(ObjectType type, std::shared_ptr<Object> owner, int count)
	{
		std::shared_ptr<Object> object;

		if (type == ObjectType::FRAME_MANAGE_ID)
		{
			object = objectManager->CreateObject<FrameManage>(owner->GetInstanceID());
			systemManager->RegisterObjectOfSystem(object);
		}

		return object;
	}

	std::shared_ptr<Object> Game::CreateObjectOfCount(ObjectType type, int count)
	{
		std::shared_ptr<Object> object;

		for (size_t i = 0; i < count; i++)
		{
			if (type == ObjectType::PLAYER_ID)
			{
				object = objectManager->CreateObject<Player>();
				systemManager->RegisterObjectOfSystem(object);
			}
			else if (type == ObjectType::ASTEROID_ID)
			{
				object = objectManager->CreateObject<Asteroid>();
				systemManager->RegisterObjectOfSystem(object);
			}
			else if (type == ObjectType::STAR_ID)
			{
				object = objectManager->CreateObject<Star>();
				systemManager->RegisterObjectOfSystem(object);
			}
		}

		return object;
	}
}
