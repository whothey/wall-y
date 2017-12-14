#include <iostream>
#include <GL/glut.h>

#include "cgrobot/Camera.hpp"
#include "cgrobot/Maze.hpp"
#include "cgrobot/Robot.hpp"
#include "cgrobot/Plant.hpp"
#include "cgrobot/Lighter.hpp"
#include "cgrobot/Light.hpp"
#include "cgrobot/WindowGlass.hpp"
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

#define MENU_CAMERA_3RD  0
#define MENU_CAMERA_MAZE 1
#define MENU_CAMERA_FIX  2
#define MENU_CAMERA_ONROBOT 3

#define MENU_CAMERA_MOVEONCLICK 0
#define MENU_CAMERA_MOVEALWAYS  1
#define MENU_CONTROL_ROBOT      2

#define MENU_AMBIENT_LIGHTS_ON  0
#define MENU_AMBIENT_LIGHTS_OFF 1

int *maze_matrix = nullptr;
unsigned int
    initial_time = time(NULL),
    final_time,
    frames = 0;

enum Control {
    Camera,
    Robot
};

enum CameraPan {
    None,
    LockedPan,
    Pan,
    Move
};

CameraPan pan = None;
Control control = Camera;

cgrobot::Maze maze = cgrobot::Maze();

cgrobot::Camera
    robot_camera(0, 10, -10),
    maze_camera(0, 80, 0),
    *current_camera = &robot_camera;

cgrobot::Robot robot(0, 0, 5);
cgrobot::Plant plant(0, 0, 10);
cgrobot::Lighter lighter(5, 0, 5);
cgrobot::WindowGlass windowglass(5, 0, 5);

cgrobot::Light
    robotLight(GL_LIGHT0),
    mazeLight(GL_LIGHT1);
    //cameraLight(GL_LIGHT2);

GLdouble rotAngle = 0, deltaAngle = 0;
GLint xOrigin = -1;

float ambientLight[4] = {0.3f, 0.3f, 0.3f, .3f};
bool cameraOnRobot = false;

int panStartX, panStartY;

// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    current_camera->activate();

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    robotLight.draw();
    mazeLight.draw();
    robot.draw();
    lighter.draw();
    plant.draw();
    maze.draw();
    windowglass.draw();

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

    if (cameraOnRobot) {
        current_camera->posX = robot.posX;
        current_camera->posZ = robot.posZ - 10;
    }

    maze_camera.lookAt(&robot);

    plant.posX = maze.indexX(12, 3);
    plant.posZ = maze.indexZ(12, 3);

    lighter.posX = maze.indexX(5, 13);
    lighter.posZ = maze.indexZ(5, 13);

    windowglass.posX = maze.indexX(12, 14);
    windowglass.posZ = maze.indexZ(12, 14);

    robotLight.spotCutoff = 30.0;
    robotLight.spotExponent = 1;
    robotLight.setSpecular(1, 1, 1, .3);
    robotLight.setDiffuse(1, 1, 1, .8);
    robotLight.setDirection(0, -1, 0);
    robotLight.setPosition(robot.posX, 40, robot.posZ);

    robot.update();
    maze.update();
    lighter.update();
    plant.update();

    glutTimerFunc(1000 / FPS, update, 0);
}

void manageMenu(int option)
{
}

void cameraMenuController(int option)
{
    switch (option) {
    case MENU_CAMERA_3RD:
        current_camera = &robot_camera;
        break;
    
    case MENU_CAMERA_MAZE:
        current_camera = &maze_camera;
        break;

    case MENU_CAMERA_FIX:
        cameraOnRobot = !cameraOnRobot;
        break;

    case MENU_CAMERA_ONROBOT:
        current_camera->posX = robot.posX;
        current_camera->posZ = robot.posZ;
        current_camera->lookAt(&robot);
        break;

    default:
        std::cout << "Comando não encontrado." << std::endl;
        break;
    }
}

void controlMenuController(int option)
{
    switch (option)
    {
    case MENU_CONTROL_ROBOT:
        control = Robot;
        break;

    case MENU_CAMERA_MOVEONCLICK:
        control = Camera;
        pan = None;
        break;

    default:
        std::cout << "Comando não encontrado" << std::endl;
        break;
    }
}

void ambientMenuController(int option)
{
    switch (option)
    {
    case MENU_AMBIENT_LIGHTS_ON:
        ambientLight[0] = ambientLight[1] = ambientLight[2] = ambientLight[3] =  1.0;
        break;

    case MENU_AMBIENT_LIGHTS_OFF:
        ambientLight[0] = ambientLight[1] = ambientLight[2] = 0.2f;
        ambientLight[3] =  1.0;
        break;
    }
}

void buildMenu()
{
    int
        main_menu     = glutCreateMenu(manageMenu),
        ambient_menu  = glutCreateMenu(ambientMenuController),
        controls_menu = glutCreateMenu(controlMenuController),
        cameras_menu  = glutCreateMenu(cameraMenuController);

    glutSetMenu(controls_menu);

    glutAddMenuEntry("Movimentar o robo", MENU_CONTROL_ROBOT);
    glutAddMenuEntry("Movimentar camera com o mouse", MENU_CAMERA_MOVEALWAYS);
    glutAddMenuEntry("Movimentar camera com o mouse ao clicar", MENU_CAMERA_MOVEONCLICK);

    glutSetMenu(ambient_menu);

    glutAddMenuEntry("Ativar Luz Global", MENU_AMBIENT_LIGHTS_ON);
    glutAddMenuEntry("Desativar Luz Global", MENU_AMBIENT_LIGHTS_OFF);

    glutSetMenu(cameras_menu);

    glutAddMenuEntry("Camera em Terceira Pessoa", MENU_CAMERA_3RD);
    glutAddMenuEntry("Camera no Teto", MENU_CAMERA_MAZE);
    glutAddMenuEntry("Fixar/Desafixar camera no robo", MENU_CAMERA_FIX);
    glutAddMenuEntry("Mover camera ate o robo", MENU_CAMERA_ONROBOT);

    glutSetMenu(main_menu);

    glutAddSubMenu("Cameras", cameras_menu);
    glutAddSubMenu("Controles", controls_menu);
    glutAddSubMenu("Ambiente", ambient_menu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
            } else {
                if (current_camera == &robot_camera)
                    robot_camera.moveForward(2);
                else
                    current_camera->move(0, 0, 1);
            }
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
                if (current_camera == &robot_camera)
                    robot_camera.moveForward(-2);
                else
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

void mouse_action(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN && pan != LockedPan) {
            pan = Pan;
            panStartX = x;
            panStartY = y;
        } else if (pan != LockedPan) {
            pan = Move;
        }

        break;

    case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN) {
            pan = Move;
            panStartX = x;
            panStartY = y;
        }
    }
}

void mouse_motion(int x, int y)
{
    int deltaX = x - panStartX;
    int deltaY = y - panStartY;

    if (pan == Pan || pan == LockedPan) {
        robot_camera.pitch += deltaY * 0.1f;
        robot_camera.yaw   -= deltaX * 0.1f;

        panStartX = x;
        panStartY = y;
    } else if (pan == Move) {
        robot_camera.moveForward(-deltaY * 0.1f);

        panStartX = x;
        panStartY = y;
    }
}

void init()
{
    size_t
        mazeMidRow = maze.getRows(),
        mazeMidCol = maze.getCols();

    GLdouble
        mazeMiddleX = maze.indexX(mazeMidRow, mazeMidCol),
        mazeMiddleZ = maze.indexZ(mazeMidRow, mazeMidCol);

    robot_camera.lookAt(0, 0, 0);
    robot_camera.type = cgrobot::CameraType::ThirdPerson;
    robot_camera.up(0, 1, 0);
    robot_camera.posX = robot.posX;
    robot_camera.posY = robot.posY + 10;
    robot_camera.posZ = robot.posZ - 10;
    robot_camera.yaw = 90;
    robot_camera.pitch = 0;

    mazeLight.setPosition(mazeMiddleX / 2, 30, mazeMiddleZ /2 );
    mazeLight.setDirection(0, -1, 0);
    mazeLight.spotCutoff = 45;
    mazeLight.spotExponent = 1;

    maze_camera.lookAt(0, 0, 0);
    maze_camera.up(0, 0, 1);
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
    window.setMouseFunc(mouse_action);
    window.setMotionFunc(mouse_motion);

    glutTimerFunc(1000 / FPS, update, 0);

    maze.setAscpect(20);

    window.init();
    buildMenu();
    maze.init();
    init();
    window.start();

    return 0;
}
