#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


/* the globals for the code. These are defined here as they are
required in multiple functions and methods down below, and also
serves as an easy to access hub to change starting values
*/
float camPos[] = {0, 0, 18.00f};	//where the camera is
float greenSquarex = 0;				//initial green x square poition
float greenSquarey = 0;				//initial green y square position
float modx = 0;						// mods keep track of where red square is
float mody = 1;						
float redSquarex = greenSquarex + modx;		//generates red square position using green and mod
float redSquarey = greenSquarey + mody;
int gridSize = 20;							//initial gridSize - changable in menus
float gridSizeL = 0;						//used to calc left bound of grid
float gridSizeR = 0;
float glScale = gridSize/20;				//used to scale the screen to good size dependant on grid size


void init(void)//sets up variables for optimal visual size
{
	glClearColor(0, 0, 0, 0);	// background color
	glColor3f(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}

/*
This method creates the grid by drawing in every pixle in the line,
and then drawns multiple lines to make a grid
*/

void makeGrid(float gridSizeL,float gridSizeR){			//Method to make the entire grid
for(int j=-gridSizeL;j<gridSizeR+1;j++){			//used to draw the grid, this does x lines
	for(float i=-gridSizeL;i<gridSizeR;i=i+0.001){
	glColor3f(1, 1, 1);
	glVertex2f(i, j);
	}
}
for(int j=-gridSizeL;j<gridSizeR+1;j++){			//used to draw grid, this does y lines
		
	for(float i=-gridSizeL;i<gridSizeR;i=i+0.001){
	glColor3f(1, 1, 1);
	glVertex2f(j, i);
	}
}
	
}
/*
this method is used a lot, as it draws the squares of 
either color by drawing in every pixel of the square
*/

void makeSquare(bool red, bool green, float xIn, float yIn){
	for(float i = xIn; i < xIn+1;i=i+0.01){
		for(float j = yIn; j < yIn+1;j=j+0.01){
			glColor3f(red, green, 0);
			glVertex2f(i,j);
		}
	}
}
/* This method is called everytime a new image(frame) is to be generated.
it it contains most visual elements
*/

void display(void)
{
	
	glScalef(0.25f, 0.25f, 0.25f);	//scales to fit 10x10 to 50x50 - DO NOT CHANGE
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);				//startd the graphic fun!
	makeGrid(gridSizeL,gridSizeR);	//makes the grid with custum values!
	
	makeSquare(0,1,greenSquarex,greenSquarey);		//makes the green square
	makeSquare(1,0,redSquarex,redSquarey);			//makes the red square

	glEnd();
	glFlush();


	glMatrixMode(GL_MODELVIEW);	// This is the basic code for delaring a 2D camera view
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0,1,0);
	glutSwapBuffers();
}



void FPS(int val){			//sets the fps of the program
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}

void callBackInit(){		//calls all the functions that need calling
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutTimerFunc(0, FPS, 0);
}

/*
The following functions are basiclly keybinds,
the values defined here are used in other functions,
they basicly refer to the order in which these menu options appear
*/

void menuProc(int value){
	if (value == 3) //up
		greenSquarey++,
		redSquarey++;	
	if (value == 4) //down
		greenSquarey--,
		redSquarey--;
	if (value == 5) //right
		greenSquarex++,
		redSquarex++;
	if (value == 6) // left
		greenSquarex--,
		redSquarex--;
	if (value == 7)// turn right (Considers current orentation)
		if(redSquarey>greenSquarey){
			redSquarey--,
			redSquarex++;
		}
		else if(redSquarey<greenSquarey){
			redSquarey++,
			redSquarex--;
		}
		else if(redSquarex<greenSquarex){
			redSquarex++,
			redSquarey++;
		}
		else{
			redSquarex--,
			redSquarey--;
		}
	if (value == 8)//turn left (Considers current orentation)
		if(redSquarey>greenSquarey){
			redSquarey--,
			redSquarex--;
		}
		else if(redSquarey<greenSquarey){
			redSquarey++,
			redSquarex++;
		}
		else if(redSquarex<greenSquarex){
			redSquarex++,
			redSquarey--;
		}
		else{
			redSquarex--,
			redSquarey++;
		}
	if (value == 9) //exit
		exit(0);
	if (value ==10)//reset
		greenSquarex = 0, greenSquarey=0,redSquarex=0,redSquarey=1;
	if (value ==11)//random
		mody = redSquarey - greenSquarey,
		modx = redSquarex - greenSquarex,
		greenSquarex = rand()%(gridSize) - (gridSize/2),
		greenSquarey = rand()%(gridSize) - (gridSize/2),
		redSquarey = greenSquarey + mody,
		redSquarex = greenSquarex + modx;
	if (value ==12)// grid ++
		if(gridSize<50){
			gridSize++;
			if(gridSize%2 !=0){
				gridSizeL = (gridSize/2)-1;
				gridSizeR = (gridSize/2)+2;
	}
	else{
		gridSizeL = (gridSize/2);
		gridSizeR = (gridSize/2);
	}
	}

	if (value ==13)// grid --
		if(gridSize>10){
			gridSize--;
				if(gridSize%2 !=0){
				gridSizeL = (gridSize/2)-1;
				gridSizeR = (gridSize/2)+2;
				}
	
	else{
		gridSizeL = (gridSize/2);
		gridSizeR = (gridSize/2);
	}
		}
		
	
	
}

/* Here we create the menus, and use the numbers assigned above
to navigate the desired menu,
and menu options
*/

void createOurMenu(){	//menus
	//int subMenu_id = glutCreateMenu(menuProc2);
	int subMenu_1 = glutCreateMenu(menuProc);	// sub menu for moving the robot
	glutAddMenuEntry("Up", 3);
	glutAddMenuEntry("Down", 4);
	glutAddMenuEntry("Right", 5);
	glutAddMenuEntry("Left", 6);
	
	int subMenu_2 = glutCreateMenu(menuProc);	// sub menu for turning the robot
	glutAddMenuEntry("Right", 7);
	glutAddMenuEntry("Left", 8);
	

	int main_id = glutCreateMenu(menuProc);	//main menu
	glutAddSubMenu("Move", subMenu_1);
	glutAddSubMenu("Turn", subMenu_2);
	glutAddMenuEntry("Exit", 9);
	glutAddMenuEntry("Reset Robot Position and Orientation",10);
	glutAddMenuEntry("Random Position",11);
	glutAddMenuEntry("Grid Size +", 12);
	glutAddMenuEntry("Grid Size -", 13);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)	//main function starts here
{
	
	printf("\n\n All options are accessable via right-click menu");
	
	if(gridSize%2 !=0){// sets up the grid size and adjustability
		gridSizeL = (gridSize/2)-1;
		gridSizeR = (gridSize/2)+2;
	}
	else{
		gridSizeL = (gridSize/2);
		gridSizeR = (gridSize/2);
		
	}
	
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);		//generates window size and position
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("Robot.x");	//creates the window
	callBackInit();					//calls all the functions needed
	init();							//calls all the dependancies
	createOurMenu();
	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
