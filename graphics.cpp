// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <iostream>
#include <cmath>
#include <cstring>
#include <GL/glut.h>
#include <stdio.h>
#include "graphics.h"
#include "gameboard.h"
#include "poisoncookie.h"
#include "menu.h"

using namespace std;
// Global Variables (Only what you need!)
double screen_x = 1024;
double screen_y = 768; 

bool STARTED = false;
bool COMPUTER = false;

string player1;
string player2;
string CURRENTPLAYER;

int GAME_X = 9;
int GAME_Y = 9;

enum {QUIT, RESTART};

PoisonCookie POISON = PoisonCookie(GAME_X, GAME_Y);
Board BOARD(&POISON);
//Menu MENU = Menu(-0.5,-1.5);

// 
// Functions that draw basic primitives
//
//
void DrawLine(double x1, double y1, double x2, double y2) {
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2 ,y2);
	glEnd();
}

void DrawCircle(double x1, double y1, double radius, double deviation)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double r;
		int c = i % 3;
		switch (c) {
			case 0:
				r = radius + deviation;
				break;
			case 1:
				r = radius - deviation;
				break;
			default:
				r = radius;
				break;
		}
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + r * cos(theta);
		double y = y1 + r * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2) {
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string) {
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glColor3d(93.0/255, 64.0/255, 55.0/255); // #5D4037
	DrawRectangle(-.5, -.5, GAME_X+.5, GAME_Y+.5); 
	glColor3d(215.0/255, 204.0/255, 200.0/255); // #D7CCC8
	DrawRectangle(0, 0, GAME_X, GAME_Y); 

	BOARD.updateCookies();
	BOARD.Draw();

	//DrawLine(0,0, GAME_X, GAME_Y);

	if (!STARTED) {
		glColor3d(121./255, 85.0/255, 72.0/255); // #795548
		DrawRectangle(.5, .5, GAME_X - .5, GAME_Y - .5);
		glColor3d(1,1,1); // #FFFFFF
		DrawText(1, 2, "Welcome to the game of PoisonCookie!");
		DrawText(2, 3, "Objective: Try not to eat the poisoned cookie.");
		DrawText(2, 4, "Gameplay: Click on a cookie to eat.");
		DrawText(2, 4.5, "All cookies down and to the right from that");
		DrawText(2, 5, "cookie will be eaten. Try to force your");
		DrawText(2, 5.5, "opponent to be left with only the poisoned cookie.");
		DrawText(2, 7.5, "Click anywhere to start game.");
	}
	if (POISON.gameOver()) {
		glColor3d(121./255, 85.0/255, 72.0/255); // #795548
		DrawRectangle(1.5, 1.5, GAME_X - 1.5, GAME_Y - 1.5);
		glColor3d(1,1,1); // #FFFFFF
		DrawText(GAME_X/2, GAME_Y/2, "GameOver!");
		DrawText(GAME_X/2-.25, GAME_Y/2+1, "Congratulations!");
		DrawText(GAME_X/2, GAME_Y/2+1.5, CURRENTPLAYER.c_str());
		DrawText(GAME_X/2, GAME_Y/2+2, "You Won!");
	}

	glColor3d(1,1,1);
	DrawText(GAME_X/2 - 1, -.2, "Current Player: ");
	DrawText(GAME_X/2 + 1, -.2, CURRENTPLAYER.c_str());

	glColor3d(1,0,0);

	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y) {
	//int mx, my;
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'q':
			exit(0);
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);
	//SetTopView();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.5, GAME_X+0.5, GAME_Y+0.5, -0.5);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (POISON.gameOver()) return;
	double gridy = screen_y/(GAME_Y + 1);
	double gridx = screen_x/(GAME_X + 1);
	double fy = y / gridy - 0.5;
	double fx = x / gridx - 0.5;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//if (!MENU.click(fx, fy));
		if (!STARTED) {
			STARTED = true;
			glutPostRedisplay();
			return;
		}
		if (fx >= 0 && fy >= 0 && fx < GAME_X && fx < GAME_Y) {
			if (POISON.move((int)fx, (int)fy, 0) )
				CURRENTPLAYER = CURRENTPLAYER == player1 ? player2 : player1;
			if (!POISON.gameOver() && COMPUTER) {
				POISON.computerMove();
				CURRENTPLAYER = CURRENTPLAYER == player1 ? player2 : player1;
			}
		}
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
	}
	glutPostRedisplay();
}

void top_menu(int id) {
	switch (id) {
		case QUIT:
			exit(0);
			break;
		case RESTART:
			CURRENTPLAYER = player1;
			POISON.restart();
			break;
		default:
			break;
	}
}

// Your initialization code goes here.
void InitializeMyStuff()
{
}


int main(int argc, char **argv)
{
	srand(time(0));
	int choice;
	cout << "What type of game would you like to play?" << endl;
	cout << "1. Human/Human" << endl;
	cout << "2. Human/Computer" << endl;
	cout << "Enter choice: ";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter Player 1 name: ";
		cin >> player1;
		cout << "Enter Player 2 name: ";
		cin >> player2;
		CURRENTPLAYER = player1;
	} else {
		cout << "Enter name: ";
		cin >> player1;
		player2 = "Computer";
		COMPUTER = true;
		CURRENTPLAYER = player1;
	}
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Poison Cookie");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	// Create Menu
	glutCreateMenu(top_menu);
	glutAddMenuEntry("Quit", QUIT);
	glutAddMenuEntry("Restart", RESTART);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
