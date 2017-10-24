#include <stdio.h>
#include <iostream>
#include <array>
#include <GL/glut.h>
#include "cgrobot/Camera.hpp"
#include "cgrobot/Maze.hpp"
#include "cgrobot/Robot.hpp"
#include "cgrobot/Window.hpp"

#ifndef W_WIDTH
 #define W_WIDTH 1390
#endif

#ifndef W_HEIGHT
 #define W_HEIGHT 768
#endif

int maze_matrix[8*6]  = {
    1, 0, 0, 1, 0, 0,
    1, 1, 0, 1, 0, 0,
    0, 1, 0, 1, 1, 1,
    0, 1, 0, 0, 0, 1,
    0, 1, 1, 1, 0, 1,
    1, 1, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1,
};

enum Control {
    Camera,
    Robot
};

Control control = Camera;

cgrobot::Maze maze((GLint *) maze_matrix, 8, 6);

cgrobot::Camera
    robot_camera(0, -20, 0),
    maze_camera(0, 0, 100),
    *current_camera = &robot_camera;

cgrobot::Robot robot(0, -10, 0);

// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    current_camera->activate();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    robot.draw();
    maze.draw();

    // Executa os comandos OpenGL
    glFlush();

    // Redraw!
    glutPostRedisplay();
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
            if (control == Robot)
                robot.move(1, 0, 0);
            //else
                //current_camera.move(1, 0, 0);
            break;

        case 'a':
        case 'A':

        case 's':
        case 'S':
            if (control == Robot)
                robot.move(0, 1, 0);
            //else
                //current_camera->move(0, 1, 0);
            break;

        case 'd':
        case 'D':
            if (control == Robot)
                robot.turnZ(-45);
            else
                current_camera->turnV(-5);
            break;

        default: break;
    }
}

void special_input(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        if (control == Robot)
            robot.turnZ(45);
        else
            current_camera->turnH(-5);
        break;

    case GLUT_KEY_DOWN:
        if (control == Robot)
            robot.turnZ(45);
        else
            current_camera->turnH(5);
        break;

    case GLUT_KEY_LEFT:
        if (control == Robot)
            robot.turnZ(45);
        else
            current_camera->turnV(-5);
        break;

    case GLUT_KEY_RIGHT:
        if (control == Robot)
            robot.turnZ(45);
        else
            current_camera->turnV(5);
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
    gluPerspective(90, w/h, 1, 100);
}

int* load_maze_csv(FILE *f)
{
    return NULL;
}

// Programa Principal
int main(int argc, char **argv)
{
    cgrobot::Window window(&argc, argv);

    window.setDisplayModes(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    window.name = "Trabalho 1 - Robô";
    window.setSize(W_WIDTH, W_HEIGHT);
    window.setPosition(100, 100);
    window.setDisplayFunc(draw);
    window.setReshapeFunc(resize_window);
    window.setKeyboardFunc(keyboard);
    window.setSpecialFunc(special_input);

    robot_camera.lookAt(1, 1, 1);
    robot_camera.up(0, 0, 1);

    maze_camera.lookAt(1, 1, 1);
    maze_camera.up(-1, 0, 0);

    window.init();
    window.start();

    return 0;
}
