compile:
	g++ app.cpp display.cpp logic.cpp -o build/app $(shell pkg-config --cflags --libs sdl2)

run:
	./build/app
