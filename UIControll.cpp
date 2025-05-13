#include "UIControll.h"
#include "Component.h"

namespace astro
{
	UIControll::UIControll()
	{
		//Object::AddComponent(std::make_shared<TransformComponent>());
		//Object::AddComponent(std::make_shared<UIComponent>());
		//Object::AddComponent(std::make_shared<ShaderColorDiffusionComponent>());
	}

	void UIControll::Init()
	{
		//auto* uiComponent = Object::GetComponent<UIComponent>(ComponentType::UI_COMPONENT);
		//auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

		//auto& textures = uiComponent->textures;
		//MyVector2& position = transformComponent->worldPosition;

		//position = { 0, 0 };

		//Texture2D texture = LoadTexture("game/resource/ControllUI.png");
		//textures.push_back(std::make_shared<Texture2D>(texture));
	}

	void UIControll::Update()
	{
	}

	void UIControll::Draw()
	{
		//const auto& textures = Object::GetComponent<UIComponent>(ComponentType::UI_COMPONENT)->textures;
		//const auto& position = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT)->worldPosition;

		//for (const auto& texture : textures)
		//{
		//	DrawTexture(*texture.get(), static_cast<int>(position.x()), static_cast<int>(position.y()), WHITE);
		//}
	}
}
