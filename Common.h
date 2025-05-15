#pragma once
#include "raylib.h"
#include "Random.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <iostream>

namespace astro
{
	using InstanceID = size_t;

	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 800;

	static const char* colorDiffusionFs = "game/ColorDiffusion.fs";
	static const char* frameFs = "game/Frame.fs";

	static const char* defaultVs = "game/Default.vs";

	struct TransformComponent;
	struct ActiveComponent;
	struct RenderComponent;
	struct MoveComponent;
	struct InputComponent;
	struct BrightEffectComponent;
	struct CameraComponent;
	struct RotationComponent;
	struct WarpComponent;
	struct UIComponent;
	struct FrameComponent;
	struct FrameManageComponent;
	struct MissileComponent;
	struct ShaderComponent;
	struct ShaderColorDiffusionComponent;
	struct ShaderFrameComponent;
	enum class ComponentType : uint64_t
	{
		TRANSFORM_COMPONENT					= 1 << 0,
		ACTIVE_COMPONENT					= 1 << 1,
		RENDER_COMPONENT					= 1 << 2,
		MOVE_COMPONENT						= 1 << 3,
		INPUT_COMPONENT						= 1 << 4,
		BRIGHT_EFFECT_COMPONENT				= 1 << 5,
		CAMERA_COMPONENT					= 1 << 6,
		ROTATION_COMPONENT					= 1 << 7,
		WARP_COMPONENT						= 1 << 8,
		UI_COMPONENT						= 1 << 9,
		FRAME_COMPONENT						= 1 << 10,
		FRAME_MANAGE_COMPONENT				= 1 << 11,
		MISSILE_COMPONENT					= 1 << 12,
		SHADER_COMPONENT					= 1 << 13, 
		SHADER_COLOR_DIFFUSION_COMPONENT	= 1 << 14,
		SHADER_FRAME_COMPONENT				= 1 << 15 
	};

	inline ComponentType operator|(ComponentType a , ComponentType b)
	{
		return static_cast<ComponentType>(static_cast<int>(a) | static_cast<int>(b));
	}
	template<typename T>
	constexpr ComponentType GetComponentType();

	// 각 컴포넌트 클래스에 대한 템플릿 특수화
	template<> constexpr ComponentType GetComponentType<TransformComponent>() { return ComponentType::TRANSFORM_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<ActiveComponent>() { return ComponentType::ACTIVE_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<RenderComponent>() { return ComponentType::RENDER_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<MoveComponent>() { return ComponentType::MOVE_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<InputComponent>() { return ComponentType::INPUT_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<BrightEffectComponent>() { return ComponentType::BRIGHT_EFFECT_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<CameraComponent>() { return ComponentType::CAMERA_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<WarpComponent>() { return ComponentType::WARP_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<UIComponent>() { return ComponentType::UI_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<FrameComponent>() { return ComponentType::FRAME_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<FrameManageComponent>() { return ComponentType::FRAME_MANAGE_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<MissileComponent>() { return ComponentType::MISSILE_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<ShaderComponent>() { return ComponentType::SHADER_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<ShaderColorDiffusionComponent>() { return ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT; }
	template<> constexpr ComponentType GetComponentType<ShaderFrameComponent>() { return ComponentType::SHADER_FRAME_COMPONENT; }

	struct ComponentData
	{
		void* data = nullptr;
		size_t size = 0;
		size_t count = 0;
		size_t capacity = 0;

		void (*destroyFunc)(void*, size_t) = nullptr;
	};

	struct Archetype
	{
		uint64_t typeMask = 0;
		std::unordered_map<ComponentType, ComponentData> components;
		std::unordered_map<InstanceID, size_t> objectIndexs;
		size_t objectCount = 0;

		template<typename T>
		void RegisterComponent(InstanceID instanceId)
		{
			ComponentType type = GetComponentType<T>();
			auto it = components.find(type); 

			if (it == components.end())
			{
				components[type] = ComponentData();
			}

			auto& component = components[type];

			// 소멸자
			component.destroyFunc = [](void* data, size_t count) {
				if (data)
				{ 
					T* typeData = static_cast<T*>(data);
					delete[] typeData;
				}
			};

			size_t tSize = sizeof(T);

			if (component.data == nullptr)
			{
				component.capacity = 16;
				component.data = new T[component.capacity];
				component.size = tSize * component.capacity;
				component.count = 0;
			}
			else
			{
				if (component.count >= component.capacity - 1)
				{
					component.capacity *= 2;

					T* newData = new T[component.capacity];

					for (size_t i = 0; i < component.count; i++)
					{
						newData[i] = static_cast<T*>(component.data)[i];
					}

					delete[] static_cast<T*>(component.data);

					component.data = newData;
					component.size = tSize * component.capacity;
				}

				if (component.count < component.capacity)
				{ 
					static_cast<T*>(component.data)[component.count] = T();
					component.count++;
				}
			}

			auto itIndex = objectIndexs.find(instanceId);

			if (itIndex == objectIndexs.end())
			{
				objectIndexs[instanceId] = objectIndexs.size();
				objectCount++;
			}
		}

		void DestoryComponentData()
		{
			for	(auto& [_, component] : components)
			{
				if (component.data && component.destroyFunc)
				{
					try
					{ 
						component.destroyFunc(component.data, component.count);
					}
					catch (...)
					{
						std::cout << "memory 중복 해제 " << std::endl;
					}
					component.data = nullptr;
					component.count = 0;
					component.capacity = 0;
				}
			}
			components.clear();
			objectIndexs.clear();
			objectCount = 0;
		}

		template<typename T>
		T* GetComponents()
		{
			ComponentType type = GetComponentType<T>();

			auto it = components.find(type);

			if (it != components.end())
			{
				return static_cast<T*>(it->second.data);
			}

			return nullptr;
		}

		template<typename T>
		T* GetComponent(InstanceID instanceId)
		{
			T* components = GetComponents<T>();

			if (!components)
			{
				return nullptr;
			}

			return &components[objectIndexs[instanceId]];
		}
	};

	struct Angle
	{
		static float DregreeToRadian(float degree)
		{
			return degree * (PI / 180.f);
		}

		static float RadianToDegree(float radian)
		{
			return radian * (180.f / PI);
		}

		float radian = 0.f;
	};

	enum class ShaderName
	{
		NONE,
		COLOR_DIFFUSION, // 뽀사시 
		FRAME,
	};

	enum class ObjectType
	{
		NONE,
		//GameObject
		GAMEOBJECT_ID,
		PLAYER_ID,
		MISSILE_ID,
		STAR_ID,
		ASTEROID_ID,

		//Effect
		FRAME_ID,
		FRAME_MANAGE_ID,

		//UI
		UI_ID,
		CONTROLL_UI_ID,

		//ShaderId
		SHADER_ID,
		SHADER_COLOR_DIFFUSION_ID,
		SHADER_FRAME_ID
	};

	struct MyVector2 
	{
		Vector2 vec;

		MyVector2() : vec{ 0, 0 } {}
		MyVector2(float x, float y) : vec{ x, y } {}
		MyVector2(const Vector2& v) : vec{ v } {}

		operator Vector2() const { return vec; }

		MyVector2 Rotate(Angle angle)
		{
			float cosAngle = cosf(angle.radian);
			float sinAngle = sinf(angle.radian);
			
			float rotatedX = { vec.x * cosAngle - vec.y * sinAngle };
			float rotatedY = { vec.x * sinAngle + vec.y * cosAngle };

			return MyVector2{ rotatedX, rotatedY };
		}

		MyVector2 operator+(const MyVector2& other) const {
			return { vec.x + other.vec.x, vec.y + other.vec.y };
		}

		MyVector2 operator-(const MyVector2& other) const {
			return { vec.x - other.vec.x, vec.y - other.vec.y };
		}

		MyVector2 operator*(float scalar) const {
			return { vec.x * scalar, vec.y * scalar };
		}

		MyVector2 operator/(float scalar) const {
			if (scalar == 0) return { 0, 0 };
			return { vec.x / scalar, vec.y / scalar };
		}

		MyVector2& operator+=(const MyVector2& other) {
			vec.x += other.vec.x;
			vec.y += other.vec.y;
			return *this;
		}

		MyVector2& operator-=(const MyVector2& other) {
			vec.x -= other.vec.x;
			vec.y -= other.vec.y;
			return *this;
		}

		MyVector2& operator*=(float scalar){
			vec.x *= scalar;
			vec.y *= scalar;
			return *this;
		}

		MyVector2 operator/=(float scalar){
			if (scalar == 0) return { 0, 0 };
			vec.x /= scalar;
			vec.y /= scalar;
			return *this;
		}

		MyVector2 DirectionTo(const MyVector2& target) const {
			return (target - *this).Normalize(); // 이름 변경 및 정규화
		}

		MyVector2 Normalize() const {
			float length = Length();
			if (length == 0) return { 0, 0 };
			return *this / length;
		}

		float Distance(const MyVector2& other) const {
			return (*this - other).Length();
		}

		float Length() const {
			return sqrtf(vec.x * vec.x + vec.y * vec.y);
		}

		float& x() { return vec.x; }
		float& y() { return vec.y; }
		const float& x() const { return vec.x; }
		const float& y() const { return vec.y; }
	};


	static float Normalize(float value, float minVal, float maxVal)
	{
		float clampValue = std::clamp(value, minVal, maxVal);

		float normalizedValue = (clampValue - minVal) / (maxVal - minVal);

		return std::clamp(normalizedValue, 0.f, 1.f);
	}
}

