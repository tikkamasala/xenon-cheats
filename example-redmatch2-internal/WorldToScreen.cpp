#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <il2cpp_resolver/il2cpp_resolver.hpp>
#include <xenon/utility/vec2.hpp>
#include <xenon/utility/vec3.hpp>

bool WorldToScreen(Vec2 screenSize, Vec3 world, Vec2& screen)
{
	Unity::CCamera* cameraMain = Unity::Camera::GetMain();
	if (!cameraMain) {
		return false;
	}

	Unity::Vector3 buffer = cameraMain->CallMethodSafe<Unity::Vector3>("WorldToScreenPoint", Unity::Vector3(world.x, world.y, world.z), Unity::m_eCameraEye::m_eCameraEye_Center);

	if (buffer.x > screenSize.x || buffer.y > screenSize.y || buffer.x < 0 || buffer.y < 0 || buffer.z < 0)
	{
		return false;
	}

	if (buffer.z > 0.0f)
	{
		screen = Vec2(buffer.x, screenSize.y - buffer.y);
	}

	if (screen.x > 0 || screen.y > 0)
	{
		return true;
	}

	return false;
}