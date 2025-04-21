#pragma once

namespace astro
{
	struct Event
	{
		virtual ~Event() = default;
	};

	struct WarpStartEvent : Event
	{
		WarpStartEvent() {};
	};

	struct WarpStopEvent : Event
	{
		WarpStopEvent() {};
	};

	struct CameraZoomEvent : Event
	{
		CameraZoomEvent(float targetZoom, float zoomSpeed) 
			: targetZoom(targetZoom) 
			, zoomSpeed(zoomSpeed)
		{};

		float targetZoom = 0.f;
		float zoomSpeed = 0.f;
	};

	struct ObjectRenderEndEvent : Event
	{
		ObjectRenderEndEvent(RenderTexture2D* texture) 
			: endRenderTexture(texture) 
		{};
		
		RenderTexture2D* endRenderTexture = nullptr;
	};
}
