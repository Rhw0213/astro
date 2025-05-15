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
#include "ObjectCountState.h"
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

		std::cout << "Game 소멸자 시작" << std::endl;

		try {
			std::cout << "시스템 매니저 해제 시작" << std::endl;
			systemManager.reset();
			std::cout << "시스템 매니저 해제 완료" << std::endl;

			std::cout << "오브젝트 매니저 해제 시작" << std::endl;
			objectManager.reset();
			std::cout << "오브젝트 매니저 해제 완료" << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "소멸 중 예외 발생: " << e.what() << std::endl;
		}

		std::cout << "CloseWindow 호출" << std::endl;
		CloseWindow();
		std::cout << "Game 소멸자 종료" << std::endl;
		//objectManager.reset();
		//systemManager.reset();
		//uiControll.reset();
		//CloseWindow();
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

			std::cout << "===============================" << std::endl;
			std::cout << "Update time: " << end1 - start1 << std::endl;
			std::cout << "Logic  time: " << end2 - start2 << std::endl;
			std::cout << "Draw   time: " << end3 - start3 << std::endl;
			std::cout << "Frame  time: " << GetFrameTime() << std::endl;
			std::cout << "===============================" << std::endl;
		}
	}

	void Game::CreateObject()
	{
		auto& objectCounts = ObjectCountState::Instance();

		//UI
		//uiControll = std::make_shared<UIControll>();
		//systemManager.get()->RegisterObjectOfSystem(uiControll);
		//uiControll->Init();

		//PLAYER
		size_t playerCount = objectCounts.AddObjectCount(ObjectType::PLAYER_ID, 1);
		auto object = CreateObjectOfCount(ObjectType::PLAYER_ID, playerCount);
		{
			InstanceID playerFrameManage = CreateObjectManagePart(ObjectType::FRAME_MANAGE_ID, object->GetInstanceID());

			size_t frameCount = objectCounts.AddObjectCount(ObjectType::FRAME_ID, 30);
			for (size_t i = 0; i < frameCount; i++)
			{ 
				CreateObjectPart(ObjectType::FRAME_ID, object->GetInstanceID(), playerFrameManage);
			}

			size_t missileCount = objectCounts.AddObjectCount(ObjectType::MISSILE_ID, 15);
			for (size_t i = 0; i < missileCount; i++)
			{ 
				InstanceID missile = CreateObjectPart(ObjectType::MISSILE_ID, object->GetInstanceID(), 0);
				InstanceID missileFrameManage = CreateObjectManagePart(ObjectType::FRAME_MANAGE_ID, missile);

				size_t missileFrameCount = objectCounts.AddObjectCount(ObjectType::FRAME_ID, 30);
				for (size_t j = 0; j < missileFrameCount; j++)
				{ 
					CreateObjectPart(ObjectType::FRAME_ID, missile, missileFrameManage);
				}
			}
		}

		// STAR
		size_t starCount = objectCounts.AddObjectCount(ObjectType::STAR_ID, 5000);
		CreateObjectOfCount(ObjectType::STAR_ID, starCount);

		//asteroid
		//CreateObjectOfCount(ObjectType::ASTEROID_ID, 10);
	}

	InstanceID Game::CreateObjectPart(ObjectType type, InstanceID ownerId, InstanceID manageId)
	{
		std::shared_ptr<Object> object = nullptr;

		if (type == ObjectType::FRAME_ID)
		{ 
			object = objectManager->CreateObject<Frame>(ownerId, manageId);
		}
		else if (type == ObjectType::MISSILE_ID)
		{ 
			object = objectManager->CreateObject<Missile>(ownerId);
		}

		if (!object)
		{
			std::cout << "nullptr";
		}
		return object->GetInstanceID();
	}

	InstanceID Game::CreateObjectManagePart(ObjectType type, InstanceID owner)
	{
		std::shared_ptr<Object> object = nullptr;

		if (type == ObjectType::FRAME_MANAGE_ID)
		{
			object = objectManager->CreateObject<FrameManage>(owner);
		}

		if (!object)
		{
			std::cout << "nullptr";
		}

		return object->GetInstanceID();
	}

	std::shared_ptr<Object> Game::CreateObjectOfCount(ObjectType type, size_t count)
	{
		std::shared_ptr<Object> object = nullptr;

		for (size_t i = 0; i < count; i++)
		{
			if (type == ObjectType::PLAYER_ID)
			{
				object = objectManager->CreateObject<Player>();
			}
			else if (type == ObjectType::ASTEROID_ID)
			{
				object = objectManager->CreateObject<Asteroid>();
			}
			else if (type == ObjectType::STAR_ID)
			{
				object = objectManager->CreateObject<Star>();
			}
		}

		if (!object)
		{
			std::cout << "nullptr";
		}

		return object;
	}
}
