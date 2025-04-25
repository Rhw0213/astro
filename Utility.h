#pragma once
#include "Common.h"
#include "Object.h" 
#include "Component.h" 
#include <memory> 
#include "math.h"

namespace astro
{
	static void TranslatePosition(std::shared_ptr<Object> target, std::shared_ptr<Object> source, MyVector2 offset)
	{
		auto* targetTransformComp = target.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* targetRotationComp = target.get()->GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);

		auto* sourceTransformComp = source.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* sourceRotationComp = source.get()->GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);

		const MyVector2&	targetPos = targetTransformComp->position;
		const Angle&		targetAngle = targetRotationComp->angle;

		MyVector2&	sourcePos = sourceTransformComp->position;
		Angle&		sourceAngle = sourceRotationComp->angle;

		float cosValue = cosf(targetAngle.radian);
		float sinValue = sinf(targetAngle.radian);

		offset = { -offset.y(), offset.x() };
		float rotateOffsetX = offset.x() * cosValue - offset.y() * sinValue;
		float rotateOffsetY = offset.x() * sinValue + offset.y() * cosValue;

		sourceAngle = targetAngle;
		sourcePos = targetPos + MyVector2{ rotateOffsetX, rotateOffsetY };
	}
}