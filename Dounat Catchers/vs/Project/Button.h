#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

namespace Engine {
	enum class ButtonState {
		PRESS,
		PRESS_TO_ON,
		PRESS_TO_OFF,
		HOVER,
		HOVER_OFF,
		HOVER_ON,
		NORMAL,
		NORMAL_ON,
		NORMAL_OFF,
		VOLUME_UP,
		VOLUME_DOWN
	};

	class Button
	{
	public:
		Button(Sprite* sprite, string name);
		~Button();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		vec2 GetPosition();
		ButtonState GetButtonState();
		void SetButtonState(ButtonState state);
		string GetButtonName();

	private:
		ButtonState state;
		Sprite* sprite;
		string name;
	};
}

#endif