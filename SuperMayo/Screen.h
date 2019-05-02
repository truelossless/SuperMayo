#pragma once
class Screen {

public:
	
	enum class State {
		GameRunning,
		GameOver
	};
	
	Screen();

	virtual State update() = 0;
};

