#pragma once

#include "Engine/Input/InputDevice.h"

class Mouse : public InputDevice
{
	friend class Input;
	friend class InputImpl;

	Mouse(void *handle);

public:
	enum EButtonId
	{
		BUTTON_1,
		BUTTON_LEFT = BUTTON_1,
		BUTTON_2,
		BUTTON_RIGHT = BUTTON_2,
		BUTTON_3,
		BUTTON_MIDDLE = BUTTON_3,
		BUTTON_4,
		BUTTON_5,
		NUM_BUTTONS
	};

	enum EAxisId
	{
		MOUSE_X,
		MOUSE_Y,
		WHEEL,
		WHEEL_HORIZONTAL,
		NUM_AXES
	};

private:
	uint8_t buttons[NUM_BUTTONS];
	AxisState axes[NUM_AXES];
};
