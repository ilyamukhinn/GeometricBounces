#include <iostream>

#include "Engine.hpp"

int main(int argc, char* argv[]) {
	Engine e;

	e.init("configs/config.txt");

	if (!e.playGame()) {
		std::cout << "Game is ended!";
	}

	return 0;
}