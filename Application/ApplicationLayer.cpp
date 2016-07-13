
/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "applicationLayer.h"

void onApplicationStart(OperatingSystem * operatingSystem) {
	auto window = &operatingSystem->aquireWindow();

	window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->setWindowIcon("data/textures/icon.bmp");
	window->setTitle("Silence : Enter The Forest");
	window->setSize(1280, 720);
	window->create();

	auto scenes = operatingSystem->aquireSceneManager();

	scenes->setStart(static_cast<int>(SceneID::Intro));
	scenes->packSceneList({ 
		new Intro(operatingSystem),
		new Menu(operatingSystem),
		new Indoors(operatingSystem),
		new Forest(operatingSystem),
		new Gameover(operatingSystem),
		new Options(operatingSystem)
	});
	
	operatingSystem->executeProgram();
} 