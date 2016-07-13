
#include "Player.h"

Player::Player()
{
	reset();
}

Player::~Player()
{

}

void Player::reset()
{
	pickedUpTorch = false;
	pickedUpRocks = false;
	timeout = -1;
	rocks = 0;
}

void Player::setTorchPickupState(bool s)
{
	pickedUpTorch = s;
}

void Player::replenishRocks()
{
	rocks += 3;
}

void Player::setRockPickupState(bool s)
{
	pickedUpRocks = s;
	rocks = 3;
}

bool Player::hasTorch()
{
	return this->pickedUpTorch;
}

bool Player::hasRocks()
{
	return this->pickedUpRocks;
}

void Player::onGamepadButton(FirstPersonCamera * camera, int key, int state)
{
	if (key == SDL_CONTROLLER_BUTTON_LEFTSHOULDER && state == GAMEPAD_BUTTON_PRESSED) {
		camera->run();
	}

	if (key == SDL_CONTROLLER_BUTTON_LEFTSHOULDER && state == GAMEPAD_BUTTON_RELEASED) {
		camera->walk();
	}

	if (key == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER && state == GAMEPAD_BUTTON_PRESSED && timeout == -1 && rocks-1 >= 0) {
		throwTimer.start();
		throwSound.reset();
		throwSound.play();

		timeout = 10 * (-camera->getPitch() + 55);
		rocks--;
	}
}

void Player::onKeyEvent(FirstPersonCamera * camera, int key, int state)
{
	if (key == SDLK_LSHIFT && state == SDL_KEYDOWN) {
		camera->run();
	}

	if (key == SDLK_LSHIFT && state == SDL_KEYUP) {
		camera->walk();
	}

	if (key == SDLK_e && state == SDL_KEYDOWN && timeout == -1 && rocks - 1 >= 0) {
		throwTimer.start();
		throwSound.reset();
		throwSound.play();

		timeout = 10 * (-camera->getPitch() + 55);
		rocks--;
	}
}

void Player::create(LocalAssetManager * package)
{
	throwSound.open(package->grabMusic("data/media/woosh_1.mp3", LOAD));
	hitSound.open(package->grabMusic("data/media/hit.mp3", LOAD));
}

void Player::update(FirstPersonCamera * camera, Monster * monster)
{
	if (monster != NULL) {
		if (throwTimer.elapsed(MS) >= timeout && timeout != -1) {
			throwTimer.clear();
			hitSound.reset();
			hitSound.play();
			timeout = -1;

			float rotation = glm::radians(camera->getRotation());
			glm::vec3 mag = glm::vec3(glm::sin(rotation), 0, glm::cos(rotation)) * glm::vec3(48.0F, 0.0F, -35.0F);
			monster->distract(mag);
		}
	}
}