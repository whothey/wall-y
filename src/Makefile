CXX=g++
LIBS=-lGL -lGLU -lglut
CPPFLAGS=-Wall -std=c++11

BIN=../bin

OBJECTS=$(BIN)/bmp.o $(BIN)/WorldObject.o $(BIN)/Robot.o $(BIN)/Camera.o $(BIN)/Window.o $(BIN)/Maze.o $(BIN)/Plant.o $(BIN)/Lighter.o

all: cgrobot main

exec: main
	$(BIN)/main

main: main.cpp bmp.o cgrobot
<<<<<<< HEAD
	$(CXX) $< $(BIN)/bmp.o $(BIN)/WorldObject.o $(BIN)/Robot.o $(BIN)/Plant.o $(BIN)/Lighter.o $(BIN)/Camera.o $(BIN)/Window.o $(BIN)/Maze.o -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

cgrobot: Window.o WorldObject.o Maze.o Camera.o Robot.o Plant.o Lighter.o
=======
	$(CXX) $< $(OBJECTS) -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

cgrobot: Window.o WorldObject.o Maze.o Camera.o Robot.o Lighter.o Plant.o
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c

Camera.o: cgrobot/Camera.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Window.o: cgrobot/Window.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Maze.o: cgrobot/Maze.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Robot.o: cgrobot/Robot.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

<<<<<<< HEAD
Lighter.o: cgrobot/lighter.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Plant.o: cgrobot/Plant.cpp
		$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)
=======
Plant.o: cgrobot/Plant.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Lighter.o: cgrobot/Lighter.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c

WorldObject.o: cgrobot/WorldObject.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

bmp.o: bmp.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

clean:
	rm $(BIN)/WorldObject.o $(BIN)/bmp.o $(BIN)/Window.o $(BIN)/Plant.o $(BIN)/Lighter.o $(BIN)/Camera.o $(BIN)/Maze.o $(BIN)/Robot.o $(BIN)/main

#.PHONY: cgrobot
