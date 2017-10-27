#include <iostream>
#include <GL/glut.h>

#include "cgrobot/Camera.hpp"
#include "cgrobot/Maze.hpp"
#include "cgrobot/Robot.hpp"
#include "cgrobot/Plant.hpp"
#include "cgrobot/Lighter.hpp"
#include "cgrobot/Window.hpp"

#ifndef W_WIDTH
 #define W_WIDTH 1390
#endif

#ifndef W_HEIGHT
 #define W_HEIGHT 768
#endif

#ifndef MAZE_FILE
 #define MAZE_FILE "../mazes/maze_two.mcsv"
#endif

#ifndef FPS
 #define FPS 60
#endif

int *maze_matrix = nullptr;
unsigned int
    initial_time = time(NULL),
    final_time,
    frames = 0;

enum Control {
    Camera,
    Robot
};

Control control = Camera;

cgrobot::Maze maze = cgrobot::Maze();

cgrobot::Camera
    robot_camera(0, 10, -10),
    maze_camera(0, 80, 0),
    *current_camera = &robot_camera;

cgrobot::Robot robot(0, 0, 5);
cgrobot::Plant plant(0, 0, 10);
cgrobot::Lighter lighter(5, 0, 5);

GLdouble rotAngle = 0, deltaAngle = 0;
GLint xOrigin = -1;

// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    current_camera->activate();

    lighter.draw();
    robot.draw();
    lighter.draw();
    plant.draw();
    maze.draw();

    // Executa os comandos OpenGL
    glFlush();

    // Frame count
    frames++;
    final_time = time(NULL);

    if (final_time - initial_time > 0) {
        std::cout << "FPS: " << frames / (final_time - initial_time) << std::endl;
        frames = 0;
        initial_time = final_time;
    }
}

void update(int)
{
    glutPostRedisplay();

    maze_camera.lookAt(&robot);
    maze_camera.posX = robot.posX;
    maze_camera.posZ = robot.posZ;
    robot_camera.lookAt(&robot);

    plant.posX = maze.indexX(14, 14);
    plant.posZ = maze.indexZ(14, 14);

    lighter.posX = maze.indexX(3, 9);
    lighter.posZ = maze.indexZ(3, 9);

    robot.update();
    maze.update();
    lighter.update();
    plant.update();

    glutTimerFunc(1000 / FPS, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        // Tab
        // Change cameras
        case '\t':
            if (current_camera == &maze_camera)
                current_camera = &robot_camera;
            else
                current_camera = &maze_camera;
            break;

        case 'r':
        case 'R':
            control = Robot;
            std::cout << "Controlling the robot!" << std::endl;
            break;

        case 'c':
        case 'C':
            // Now WASD controls the cameras
            control = Camera;
            std::cout << "Controlling the camera!" << std::endl;
            break;

        case 'w':
        case 'W':
            if (control == Robot) {
                robot.move(0, 0, 1);
            } else
                current_camera->move(0, 0, 1);
            break;

        case 'a':
        case 'A':
            if (control == Robot) {
                robot.turnY(5);
            } else {
                current_camera->move(1, 0, 0);
            }

            break;

        case 's':
        case 'S':
            if (control == Robot) {
                robot.move(0, 0, -1);
            } else {
                current_camera->move(0, 0, -1);
            }
            break;

        case 'd':
        case 'D':
            if (control == Robot) {
                robot.turnY(-5);
            } else {
                current_camera->move(-1, 0, 0);
            }
            break;

        case '+':
            current_camera->move(0, 1, 0);
            break;

        case '-':
            current_camera->move(0, -1, 0);
            break;

        default: break;
    }
}

void special_input(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        current_camera->move(0, 1, 0);
        break;

    case GLUT_KEY_DOWN:
        current_camera->move(0, -1, 0);
        break;

    case GLUT_KEY_LEFT:
        current_camera->move(1, 0, 0);
        break;

    case GLUT_KEY_RIGHT:
        current_camera->move(-1, 0, 0);
        break;

    default:
        break;
    }
}

// Função callback chamada quando o tamanho da janela é alterado
void resize_window(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0) h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define campo de visão
    gluPerspective(90, w/h, 1, 300);
}

// Ugly for now
int* load_maze_csv(FILE *f, size_t& rows, size_t& cols)
{
    int *maze = nullptr;

    // Read specs
    fscanf(f, "%lux%lu\n", &rows, &cols);

    maze = (int *)malloc(rows * cols * sizeof(int));

    std::cout << "Maze Size: " << rows << "x" << cols << std::endl;

    for (size_t i = 0; i < rows; i++) {
        fscanf(f, "%d", &maze[i * cols]); // j = 0

        for (size_t j = 1; j < cols; j++) {
            fscanf(f, ",%d", &maze[i * cols + j]);
        }

        fscanf(f, "\n");
    }

    return maze;
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
            std::cout << "left ";
		if (state == GLUT_UP) {
			rotAngle += deltaAngle;
			xOrigin = -1;
            std::cout << "NOT " << xOrigin;
		} else {
			xOrigin = x;
            std::cout << "PRESSING " << xOrigin;
		}
	}
}

void mouseMove(int x, int y)
{
	// this will only be true when the left button is down
	if (xOrigin >= 0) {
		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		robot_camera.lx = sin(rotAngle + deltaAngle);
		robot_camera.lz = -cos(rotAngle + deltaAngle);
	}
}

// Programa Principal
int main(int argc, char **argv)
{
    cgrobot::Window window(&argc, argv);
    FILE *mazef = fopen(MAZE_FILE, "r");
    size_t mrows, mcols;

    maze_matrix = load_maze_csv(mazef, mrows, mcols);
    maze.loadFromMatrix(maze_matrix, mrows, mcols);

    window.setDisplayModes(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    window.name = "Trabalho 1 - Robô";
    window.setSize(W_WIDTH, W_HEIGHT);
    window.setPosition(100, 100);
    window.setDisplayFunc(draw);
    window.setReshapeFunc(resize_window);
    window.setKeyboardFunc(keyboard);
    window.setSpecialFunc(special_input);

	glutMotionFunc(mouseMove);
    glutMouseFunc(mouseButton);

    glutTimerFunc(1000 / FPS, update, 0);

    robot_camera.lookAt(&robot);
    robot_camera.up(0, 1, 0);
    robot_camera.offsetX = 0;
    robot_camera.offsetY = 10;
    robot_camera.offsetZ = -10;
    robot_camera.follow(&robot);

    maze_camera.lookAt(0, 0, 0);
    maze_camera.up(0, 0, 1);

    maze.setAscpect(10);
    window.init();
    maze.init();
    window.start();

    return 0;
}
