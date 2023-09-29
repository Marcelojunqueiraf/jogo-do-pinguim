COMPONENTES=Componentes/Sprite/Sprite.cpp Componentes/Component/Component.cpp Componentes/Face/Face.cpp Componentes/Sound/Sound.cpp Componentes/TileMap/TileMap.cpp
UTILS=Utils/Vec2/Vec2.cpp Utils/Rect/Rect.cpp Utils/TileSet/TileSet.cpp
FILES=Game/Game.cpp State/State.cpp  Music/Music.cpp GameObject/GameObject.cpp 
all:
	g++ main.cpp ${COMPONENTES} ${UTILS} ${FILES} -o jogo `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2main
	./jogo