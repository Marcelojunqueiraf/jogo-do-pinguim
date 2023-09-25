FILES=Game/Game.cpp State/State.cpp Sprite/Sprite.cpp Music/Music.cpp Vec2/Vec2.cpp Rect/Rect.cpp GameObject/GameObject.cpp Component/Component.cpp Face/Face.cpp Sound/Sound.cpp
all:
	g++ main.cpp ${FILES} -o jogo `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2main
