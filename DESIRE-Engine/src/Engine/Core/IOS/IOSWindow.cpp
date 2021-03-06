#include "stdafx.h"
#include "Core/IOS/IOSWindow.h"

IOSWindow::IOSWindow(const IWindow::CreationParams& creationParams)
	: IWindow(creationParams)
{

}

IOSWindow::~IOSWindow()
{

}

void IOSWindow::HandleWindowMessages()
{

}

void* IOSWindow::GetHandle() const
{
	return nullptr;
}

void IOSWindow::SetCursor(ECursor cursor)
{

}

bool IOSWindow::SetClipboardString(const String& string)
{
	return false;
}

String IOSWindow::GetClipboardString()
{
	String str;
	return str;
}

// --------------------------------------------------------------------------------------------------------------------
//	IWindow
// --------------------------------------------------------------------------------------------------------------------

std::unique_ptr<IWindow> IWindow::Create(const IWindow::CreationParams& creationParams)
{
	return std::make_unique<IOSWindow>(creationParams);
}
