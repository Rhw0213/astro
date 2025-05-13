#pragma once

namespace astro
{
/// @brief Event
	struct Event
	{
		virtual ~Event() = default;
	};

/// @brief WarpStartEvent
	struct WarpStartEvent : Event
	{
		WarpStartEvent(float frameSize = 0.f) 
			: frameSize(frameSize)
		{};

		float frameSize;
	};

/// @brief WarpStopEvent
	struct WarpStopEvent : Event
	{
		WarpStopEvent(float frameSize = 0.f) 
			: frameSize(frameSize)
		{};

		float frameSize;
	};

/// @brief MissileFireEvent
	struct MissileFireEvent : Event
	{
		MissileFireEvent(InstanceID fireOwner = 0) 
			: fireOwner(fireOwner)
		{};

		InstanceID fireOwner;
	};

/// @brief CameraZoomEvent
	struct CameraZoomEvent : Event
	{
		CameraZoomEvent(float targetZoom, float zoomSpeed) 
			: targetZoom(targetZoom) 
			, zoomSpeed(zoomSpeed)
		{};

		float targetZoom = 0.f;
		float zoomSpeed = 0.f;
	};

/// @brief ObjectRenderEndEvent
	struct ObjectRenderEndEvent : Event
	{
		ObjectRenderEndEvent(RenderTexture2D* texture) 
			: endRenderTexture(texture) 
		{};
		
		RenderTexture2D* endRenderTexture = nullptr;
	};
}
