#pragma once
#include "Common.h"
#include "Object.h" 
#include "Component.h" 
#include "ComponentManager.h" 
#include <memory> 
#include "math.h"

namespace astro
{
	static MyVector2 TranslatePosition(std::shared_ptr<Object> target, MyVector2 offset)
	{
		auto& CM = ComponentManager::Instance();
		auto* targetTransformComp = CM.GetComponent<TransformComponent>(target->GetComponentMask(), target->GetInstanceID());

		const MyVector2&	targetPos		= targetTransformComp->worldPosition;
		const Angle&		targetRotation	= targetTransformComp->worldRotation;
		const float&		targetScale		= targetTransformComp->worldScale;

		float cosValue = cosf(targetRotation.radian);
		float sinValue = sinf(targetRotation.radian);

		offset = MyVector2{ -offset.y(), offset.x() } * targetScale;

		float rotateOffsetX = offset.x() * cosValue - offset.y() * sinValue;
		float rotateOffsetY = offset.x() * sinValue + offset.y() * cosValue;

		return targetPos + MyVector2{ rotateOffsetX, rotateOffsetY };
	}
}