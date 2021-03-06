#pragma once

class InputDevice
{
protected:
	InputDevice(void *handle, size_t offsetOfButtonStates, uint16_t numButtonStates, size_t offsetOfAxisStates = 0, uint16_t numAxisStates = 0);

public:
	static const uint8_t BUTTON_STATE_DOWN_FLAG = 0x80;

	bool IsDown(int buttonId) const;
	bool WentDown(int buttonId) const;

	// Returns how many times the button went down since the last frame
	uint8_t GetPressedCount(int buttonId) const;

	// Returns the current axis position, which is usually normalized into the [0.0, 1.0] range
	float GetAxisPos(int axisId) const;

	// Returns the difference in axis position since the last frame
	float GetAxisDelta(int axisId) const;

	void *handle;

protected:
	struct AxisState
	{
		float delta;
		float pos;
	};
	
	void Update();

	void HandleButton(int buttonId, bool isDown);
	void HandleAxis(int axisId, float delta);
	void HandleAxisAbsolute(int axisId, float newPos);

	const uint16_t offsetOfButtonStatesInDerivedClass;
	const uint16_t offsetOfAxisStatesInDerivedClass;
	const uint16_t numButtonStates;
	const uint16_t numAxisStates;
};
