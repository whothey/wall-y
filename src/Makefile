CXX=g++
LIBS=-lGL -lGLU -lglut
CPPFLAGS=-Wall

BIN=../bin
SOURCES=

ROBOT_LIB_SRCS=Window.cpp

all: cgrobot main

exec: main
	../bin/main

main: main.cpp cgrobot
	$(CXX) $< $(BIN)/WorldObject.o $(BIN)/Robot.o $(BIN)/Camera.o $(BIN)/Window.o $(BIN)/Maze.o -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

cgrobot: Window.o WorldObject.o Maze.o Camera.o Robot.o

Camera.o: ./cgrobot/Camera.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Window.o: cgrobot/Window.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Maze.o: cgrobot/Maze.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

Robot.o: cgrobot/Robot.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

WorldObject.o: cgrobot/WorldObject.cpp
	$(CXX) -c $< -o $(BIN)/$@ $(LIBS) $(CPPFLAGS)

clean:
	rm $(BIN)/main $(BIN)/Window.o $(BIN)/Camera.o $(BIN)/Maze.o $(BIN)/Robot.o

.PHONY: cgrobot
