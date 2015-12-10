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

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "poisoncookie.h"
#include <unistd.h>
#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif


// Global Variables (Only what you need!)
//Changeable to affect gameplay.
double screen_x = 800; //starting window size variables
double screen_y = 600;
int amount = 4; //4 will make it connect 4, changed to 3 or 5 will change the game to 'connect 3' or 'connect 5'
int ai = 0; //Set computer as player 2 to on/off.
int game_x = 7; //to change board size
int game_y = 6;

//Global variables not particularly designed to be changed.
int player = 0;
PoisonCookie game(game_x, game_y, amount);
double cell_x = screen_x/game_x;
double cell_y = screen_y/game_y;
double smaller = std::min(cell_x,cell_y);
double p_rad = (smaller-4)/2;

/* Used for testing, no longer needed.
void draw_matrix(int ** b)
{
    for (int i=0; i<7; i++)
    {   
        for (int j=0; j<6; j++)
        {   
            std::cout << b[i][j] << " ";
        }   
        std::cout << std::endl;
    }   
}
*/

// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
  glBegin(GL_POLYGON);
  for(int i=0; i<32; i++)
    {
      double theta = (double)i/32.0 * 2.0 * 3.1415926;
      double x = x1 + radius * cos(theta);
      double y = y1 + radius * sin(theta);
      glVertex2d(x, y);
    }
  glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
  glBegin(GL_QUADS);
  glVertex2d(x1,y1);
  glVertex2d(x2,y1);
  glVertex2d(x2,y2);
  glVertex2d(x1,y2);
  glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
  glBegin(GL_TRIANGLES);
  glVertex2d(x1,y1);
  glVertex2d(x2,y2);
  glVertex2d(x3,y3);
  glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
  void *font = GLUT_BITMAP_9_BY_15;

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
void draw_grid()
{
  glColor3d(0,0,0);
  for (int i = 1; i<game_x; i++)
  {
	  DrawRectangle(cell_x*i-2, 0, cell_x*i+2, screen_y);
  }
  for (int i=1; i< game_y; i++)
  {
	  DrawRectangle(0, cell_y*i-2, screen_x, cell_y*i+2);
  }
}

void draw_board()
{
  int ** brd = game.getBoard();
  int x_zero = cell_x/2;
  int y_zero = cell_y/2;
  for (int i=0; i<game_x; i++)
  {
	for (int j=0; j<game_y; j++)
	{
		if (brd[i][j] == 1)
		{
  			glColor3d(1,1,0);
			DrawCircle(x_zero+cell_x*i, y_zero+cell_y*j, p_rad);
		}
		else if (brd[i][j] == 2)
		{
  			glColor3d(1,0,0);
			DrawCircle(x_zero+cell_x*i, y_zero+cell_y*j, p_rad);
		}
	}
  }

  if (game.gameOver() != 0)
	{
		glColor3d(0,0,0);
		DrawRectangle(screen_x/2-100, screen_y/2-20, screen_x/2+100, screen_y/2+20);
		glColor3d(1,1,1);
		std::stringstream game_over_msg;
		game_over_msg << "Player " << game.gameOver() << " Wins!";
		DrawText(screen_x/2-60, screen_y/2-5, game_over_msg.str().c_str());
	}
}

void draw_player()
{
	glColor3d(0.6,0.6,0.6);
	DrawRectangle(0, screen_y, 90, screen_y-20);
	glColor3d(1,1,1);
	std::stringstream player_msg;
	player_msg << "Player " << player+1;
	DrawText(5, screen_y-15, player_msg.str().c_str());
}


// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  draw_grid();
  draw_board();
  draw_player();

  // Test lines that draw all three shapes and some text.
  // Delete these when you get your code working.

  glutSwapBuffers();
}

/*
void aiMove()
{
	if (game.gameOver() != 0)
		return;
	display();
	usleep(500000);
	int move = comp.Move(game, player+1);
	game.makeMove( move, player+1);

	player = (player+1)%2;
}
*/

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
  switch (c) 
    {
    case 'q':
    case 27: // escape character means to quit the program
      exit(0);
      break;
    case 'n':
      // do something when 'b' character is hit.
		game.restart();
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
		if (game.gameOver() == 0)
		{
			int col = c-'1';
			if (game.makeMove(col, player+1))
			{
				player = (player+1)%2;
				if (ai == 1)
				{
					//aiMove();
				}
			}
		}
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
  cell_x = screen_x/game_x;
  cell_y = screen_y/game_y;
  smaller = std::min(cell_x, cell_y);
  p_rad = (smaller-4)/2;

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = screen_y - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
		if (game.gameOver() == 0)
		{
			int col = xdisplay/cell_x;
			if (game.makeMove(col, player+1))
			{
				player = (player+1)%2;
				if (ai == 1)
				{
					// aiMove();
				}
			}
		}
    }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    {
    }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
    {
    }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
    {
    }
  glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screen_x, screen_y);
  glutInitWindowPosition(1550, 50);

  int fullscreen = 0;
  if (fullscreen) 
    {
      glutGameModeString("800x600:32");
      glutEnterGameMode();
    } 
  else 
    {
      glutCreateWindow("Connect Four");
    }

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);

  glColor3d(0,0,0); // forground color
  glClearColor(1, 1, 1, 0); // background color
  InitializeMyStuff();
  display();

  glutMainLoop();

  return 0;
}
