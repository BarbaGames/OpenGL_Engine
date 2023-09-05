#pragma once
#include "Engine.h"

namespace MyEngine {

	class BaseGame {
	private:
		Engine* engine;

		bool initBase();
		void updateBase();
		void uninitBase();
	protected:
		Window* window;

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void uninit() = 0;
	public:
		BaseGame();
		virtual ~BaseGame();
	};

}