CC=g++
# Adapt the variables below to your needs:
EXE=snake
CPP= tdasilva/*.cpp tdasilva/*/*.cpp tdasilva/*/*/*.cpp #tdasilva/utils/utils.cpp tdasilva/utils/text.cpp tdasilva/MainSDLWindow.cpp tdasilva/map/map.cpp tdasilva/entity/snake/body.cpp tdasilva/entity/snake/snake.cpp tdasilva/entity/fruit/apple.cpp tdasilva/game.cpp tdasilva/menu/button.cpp tdasilva/menu/menu.cpp tdasilva/main.cpp
HPP= tdasilva/*.hpp tdasilva/*/*.hpp tdasilva/*/*/*.hpp #tdasilva/utils/utils.hpp tdasilva/utils/text.hpp tdasilva/MainSDLWindow.hpp tdasilva/map/map.hpp tdasilva/entity/snake/body.hpp tdasilva/entity/snake/snake.hpp tdasilva/entity/fruit/apple.hpp tdasilva/game.hpp tdasilva/menu/button.hpp tdasilva/menu/menu.hpp

# The default is build the executable file:
default: $(EXE)

# The executable file must be rebuilt if source files changed:
$(EXE): $(CPP) $(HPP)
	$(CC) $(CPP) -lSDL2 -lSDL2_image -lSDL2_ttf -o $(EXE)

# Run of the (always up-to-date) executable:
run: $(EXE)
	./$(EXE)

# Build the UML diagram as a PNG image:
uml/classes.png: $(HPP)
	./uml/mk_uml.sh $@ $^

# Count the number of lines of code:
nblines:
	@wc -l $(CPP) $(HPP)
