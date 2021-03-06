#include "Engine/stdafx.h"
#include "Engine/Core/IWindow.h"
#include "Engine/Core/Modules.h"
#include "Engine/Render/Render.h"

IWindow::IWindow(const CreationParams& creationParams)
	: isFullscreen(creationParams.isFullscreen)
	, isActive(false)
{
	width = std::max(WINDOW_MIN_SIZE, creationParams.width);
	height = std::max(WINDOW_MIN_SIZE, creationParams.height);
}

IWindow::~IWindow()
{

}

uint16_t IWindow::GetWidth() const
{
	return width;
}

uint16_t IWindow::GetHeight() const
{
	return height;
}

bool IWindow::IsFullscreen() const
{
	return isFullscreen;
}

bool IWindow::IsActive() const
{
	return isActive;
}

void IWindow::SetSize(uint16_t i_width, uint16_t i_height)
{
	if(width == i_width && height == i_height)
	{
		return;
	}

	width = i_width;
	height = i_height;
	Modules::Render->UpdateRenderWindow(this);
}
