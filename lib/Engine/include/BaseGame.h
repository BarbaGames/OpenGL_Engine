#pragma once
#include "Engine.h"

#include "Rectangle.h"

namespace MyEngine {

	class DLLExport BaseGame {
	private:
		Engine* engine;

		bool initBase();
		void updateBase();
		void uninitBase();
	protected:
		Window* window;

		virtual void init() {};
		virtual void update() {};
		virtual void uninit() {};
	public:
		BaseGame();
		virtual ~BaseGame();

		void runGame();
	};

}