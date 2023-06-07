#include "Button.h"

Engine::Button::Button(Sprite* sprite, string name)
{
	state = Engine::ButtonState::NORMAL;
	this->sprite = sprite;
	this->name = name;
}

Engine::Button::~Button()
{
	delete sprite;
	sprite = NULL;
}

void Engine::Button::Update(float deltaTime)
{
	if (Engine::ButtonState::NORMAL == state) {
		sprite->PlayAnim("normal");
	}
	else if (Engine::ButtonState::NORMAL_ON == state) {
		sprite->PlayAnim("normal-on");
	}
	else if (Engine::ButtonState::NORMAL_OFF == state) {
		sprite->PlayAnim("normal-off");
	}
	else if (Engine::ButtonState::HOVER == state) {
		sprite->PlayAnim("hover");
	}
	else if (Engine::ButtonState::HOVER_OFF == state) {
		sprite->PlayAnim("hover-off");
	}
	else if (Engine::ButtonState::HOVER_ON == state) {
		sprite->PlayAnim("hover-on");
	}
	else if (Engine::ButtonState::PRESS == state) {
		sprite->PlayAnim("press");
	}
	else if (Engine::ButtonState::PRESS_TO_OFF == state) {
		sprite->PlayAnim("press-to-off");
	}
	else if (Engine::ButtonState::PRESS_TO_ON == state) {
		sprite->PlayAnim("press-to-on");
	}
	else if (Engine::ButtonState::VOLUME_UP == state) {
		sprite->PlayAnim("volume-up");
	}
	else if (Engine::ButtonState::VOLUME_DOWN == state) {
		sprite->PlayAnim("volume-down");
	}

	sprite->Update(deltaTime);
}

void Engine::Button::Draw()
{
	sprite->Draw();
}

void Engine::Button::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

Engine::ButtonState Engine::Button::GetButtonState()
{
	return state;
}

void Engine::Button::SetButtonState(ButtonState state)
{
	this->state = state;
}

string Engine::Button::GetButtonName()
{
	return name;
}

vec2 Engine::Button::GetPosition()
{
	return sprite->GetPosition();
}

