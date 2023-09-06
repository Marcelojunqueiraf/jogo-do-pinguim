
all:
	g++ main.cpp Game/Game.cpp State/State.cpp Sprite/Sprite.cpp Music/Music.cpp -o myProgram `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2main
