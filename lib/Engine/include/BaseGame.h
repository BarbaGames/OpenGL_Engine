#pragma once
#include "Engine.h"
#include "Input.h"
#include "ETime.h"

#include "Rectangle.h"
#include "AssetLoader.h"
#include "Sprite.h"
#include "Animation.h"

namespace MyEngine {

	class DLLExport BaseGame {
	private:
		Engine* engine;

		bool initBase();
		void updateBase();
		void uninitBase();
	protected:
		Window* window;
		Input* input;
		
		virtual void init() {};
		virtual void update() {};
		virtual void uninit() {};
	public:
		BaseGame();
		virtual ~BaseGame();

		void runGame();
	};

}
