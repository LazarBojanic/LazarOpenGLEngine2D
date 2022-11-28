#include "Application.hpp"

int main() {
	Application* application = new Application(640, 640);
	application->run();
	delete application;
	return 0;
}