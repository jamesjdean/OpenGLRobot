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


//Globals
float camPos[] = {0, 0, 18.00f};
float greenSquarex = 0;
float greenSquarey = 0;
float modx = 0;
float mody = 1;						
float redSquarex = greenSquarex + modx;
float redSquarey = greenSquarey + mody;
int gridSize = 20;
float gridSizeL = 0;
float gridSizeR = 0;
float glScale = gridSize/20;


void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}

void makeGrid(float gridSizeL,float gridSizeR){
	for(int j=-gridSizeL;j<gridSizeR+1;j++){
		for(float i=-gridSizeL;i<gridSizeR;i=i+0.001){
		glColor3f(1, 1, 1);
		glVertex2f(i, j);
	}
}
for(int j=-gridSizeL;j<gridSizeR+1;j++){
		
	for(float i=-gridSizeL;i<gridSizeR;i=i+0.001){
	glColor3f(1, 1, 1);
	glVertex2f(j, i);
	}
}
	
}

void makeSquare(bool red, bool green, float xIn, float yIn){
	for(float i = xIn; i < xIn+1;i=i+0.01){
		for(float j = yIn; j < yIn+1;j=j+0.01){
			glColor3f(red, green, 0);
			glVertex2f(i,j);
		}
	}
}
void display(void)
{
	
	glScalef(0.25f, 0.25f, 0.25f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	makeGrid(gridSizeL,gridSizeR);
	
	makeSquare(0,1,greenSquarex,greenSquarey);
	makeSquare(1,0,redSquarex,redSquarey);

	glEnd();
	glFlush();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0,1,0);
	glutSwapBuffers();
}



void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0);
}

void callBackInit(){
	glutDisplayFunc(display);
	glutTimerFunc(0, FPS, 0);
}


void menuProc(int value){
	if (value == 3)
		greenSquarey++,
		redSquarey++;	
	if (value == 4)
		greenSquarey--,
		redSquarey--;
	if (value == 5)
		greenSquarex++,
		redSquarex++;
	if (value == 6)
		greenSquarex--,
		redSquarex--;
	if (value == 7)
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
	if (value == 8)
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
	if (value == 9)
		exit(0);
	if (value ==10)
		greenSquarex = 0, greenSquarey=0,redSquarex=0,redSquarey=1;
	if (value ==11)
		mody = redSquarey - greenSquarey,
		modx = redSquarex - greenSquarex,
		greenSquarex = rand()%(gridSize) - (gridSize/2),
		greenSquarey = rand()%(gridSize) - (gridSize/2),
		redSquarey = greenSquarey + mody,
		redSquarex = greenSquarex + modx;
	if (value ==12)
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

	if (value ==13)
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



void createOurMenu(){
	//int subMenu_id = glutCreateMenu(menuProc2);
	int subMenu_1 = glutCreateMenu(menuProc);
	glutAddMenuEntry("Up", 3);
	glutAddMenuEntry("Down", 4);
	glutAddMenuEntry("Right", 5);
	glutAddMenuEntry("Left", 6);
	
	int subMenu_2 = glutCreateMenu(menuProc);
	glutAddMenuEntry("Right", 7);
	glutAddMenuEntry("Left", 8);
	

	int main_id = glutCreateMenu(menuProc);
	glutAddSubMenu("Move", subMenu_1);
	glutAddSubMenu("Turn", subMenu_2);
	glutAddMenuEntry("Exit", 9);
	glutAddMenuEntry("Reset Robot Position and Orientation",10);
	glutAddMenuEntry("Random Position",11);
	glutAddMenuEntry("Grid Size +", 12);
	glutAddMenuEntry("Grid Size -", 13);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	
	printf("\n\n All options are accessable via right-click menu");
	
	if(gridSize%2 !=0){
		gridSizeL = (gridSize/2)-1;
		gridSizeR = (gridSize/2)+2;
	}
	else{
		gridSizeL = (gridSize/2);
		gridSizeR = (gridSize/2);
		
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("Robot.x");
	callBackInit();
	init();
	createOurMenu();
	glutMainLoop();
	return(0);
}
