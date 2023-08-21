#include <windows.h>
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <chrono>
#include "sort_type.h"

// Global Variables
// ----------------------------------------------------------------------------
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;
std::vector<float> arrayElements;
std::vector<bool> isSorted;
int numElements = 10;
int sTime = 50;
int comparisons = 0;
int flag=0;

// Function Prototypes
// ----------------------------------------------------------------------------

void display();
void init();
void frontscreen(void);
void draw(int x, int y);
void generate();
void myKeyboardFunc( unsigned char key, int x, int y );
void displayText(std::string textToDraw, int x, int y);
void displayTitle(std::string textToDraw, int x, int y);
void displayInfo();
void mydisplay(void);
void menuFunc(int id);
void createMenu();
void drawstring(float x,float y,float z,char *string);
void clear();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sorting Algorithm Visualizer");
	init();
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboardFunc);
	createMenu();
	glutMainLoop();

	return 0;
}
void frontscreen(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(0.7,0,1);
 drawstring(0.35 * SCREEN_HEIGHT,SCREEN_WIDTH * .7,0.0,"JSS ACADEMY OF TECHNICAL EDUCATION, BENGALURU ");
 glColor3f(0.7,0,1);
 drawstring(0.33 * SCREEN_HEIGHT,SCREEN_WIDTH * .62,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
 glColor3f(1,0.5,0);
 drawstring(0.55 * SCREEN_HEIGHT,SCREEN_WIDTH * .54,0.0,"A MINI PROJECT ON");
 glColor3f(1,0,0);
 drawstring(0.45 * SCREEN_HEIGHT,SCREEN_WIDTH * .46,0.0,"SORTING ALGORITHM VISUALIZER");
 glColor3f(1,0.5,0);
 drawstring(0.45 * SCREEN_HEIGHT,SCREEN_WIDTH * .38,0.0,"BY:");
 glColor3f(1,1,1);
 drawstring(0.5 * SCREEN_HEIGHT,SCREEN_WIDTH * .35,0.0,"SHREEYA R HEGDE(1JS20CS155)");
 glColor3f(1,1,1);
 drawstring(0.5 * SCREEN_HEIGHT,SCREEN_WIDTH * .3,0.0,"    SINCHANA S(1JS20CS159)");
 glColor3f(1,0.5,0);
 drawstring(0.4 * SCREEN_HEIGHT,SCREEN_WIDTH * .22,0.0,"GUIDES:");
 glColor3f(1,1,1);
 drawstring(0.5 * SCREEN_HEIGHT,SCREEN_WIDTH * .17,0.0,"Dr.Sharana Basavana Gowda");
 glColor3f(1,1,1);
 drawstring(0.5 * SCREEN_HEIGHT,SCREEN_WIDTH * .12,0.0,"Mrs.Rashmi.B.N");
 glColor3f(1,0.1,1);
 drawstring(0.55 * SCREEN_HEIGHT,SCREEN_WIDTH * .05,0.0,"PRESS ENTER TO START");
 glFlush();
}
void myKeyboardFunc( unsigned char key, int x, int y )

{
 switch(key)
 {
 case 13:if(flag==0) //Ascii of 'enter' key is 13
    flag=1;
  break;
       }
    mydisplay();
}
void mydisplay(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 if(flag==0)
   frontscreen ();
 if(flag==1)
  display();
}
void drawstring(float x,float y,float z,char *string)
{
    char *c;
    int len = (int) strlen(string);
    int i;
    glRasterPos3f(x,y,z);
    /*for(c=string;*c!='\0';c++)
    {
        glColor3f(0.0,0.0,0.0);
        glutBitmapCharacter(currentfont,*c);
    }*/
    for(i = 0;i<len;i++)
    {
        glColor3f(1.0,1.0,1.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	generate();
}

void displayText(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textToDraw[i]);
}

void displayTitle(std::string textToDraw, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < textToDraw.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textToDraw[i]);
}

void displayInfo()
{
	//glColor3f(0.0f, 1.0f, 0.0f);
	//std::string title = "Sorting Visualizer";
	//displayTitle(title, SCREEN_WIDTH * .4, 0.85 * SCREEN_HEIGHT);
	glColor3f(1.0f, 1.0f, 1.0f);//color of the blocks before selection of algorithm
	std::string info = "Values: " + std::to_string(numElements) + "    Delay: " + std::to_string(sTime) + " ms delay";
	displayText(info, 5, 0.97 * SCREEN_HEIGHT);
}

void displayTotalTime(int diff, std::string algorithm, std::string formula)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string info = "Sort Algorithm: " + algorithm + "    Comparisons: " + std::to_string(comparisons);
	displayText(info, 5, 0.93 * SCREEN_HEIGHT);
	std::string totalTime = "Total Time: " + std::to_string(diff) + " ms"+"         Formula: "+formula;
	displayText(totalTime, 5, .89 * SCREEN_HEIGHT);
	glFlush();
}

void draw(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	float quadSize = (SCREEN_WIDTH - 2 * (numElements + 1.0)) / numElements;
	for (int i = 0; i < numElements; i++)
	{
		float normalizedValue = arrayElements[i] / (SCREEN_HEIGHT * 0.8); // Normalize the value to range [0, 1]
		glColor3f(normalizedValue, 1.0f - normalizedValue, 0.0f); // Set color based on the normalized value
		glBegin(GL_POLYGON);
		glVertex2f(2 + i * (2 + quadSize), 0);
		glVertex2f(2 + i * (2 + quadSize), arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, arrayElements[i]);
		glVertex2f(2 + i * (2 + quadSize) + quadSize, 0);
		glEnd();
	}
	displayInfo();
	glFlush();
}




void generate()
{
	comparisons = 0;
	isSorted.clear();
	arrayElements.clear();
	srand(time(0));
	for (int i = 0; i < numElements; i++)
	{
		arrayElements.push_back(((float)rand() / RAND_MAX) * SCREEN_HEIGHT * 0.8);
		isSorted.push_back(false);
	}
	draw(-1, -1);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(0);
	glEnd();
	glFlush();
}

void menuFunc(int id)
{
	switch (id)
	{
	case 11: numElements = 10; generate(); break;
	case 12: numElements = 20; generate(); break;
	case 13: numElements = 50; generate(); break;
	case 14: numElements = 100; generate(); break;
	case 15: numElements = 200; generate(); break;
	//case 16: numElements = 1000; generate(); break;

	case 21: sTime = 10; draw(-1, -1); break;
	case 22: sTime = 20; draw(-1, -1); break;
	case 23: sTime = 50; draw(-1, -1); break;
	case 24: sTime = 100; draw(-1, -1); break;
	//case 25: sTime = 500; draw(-1, -1); break;

	case 31: {
		auto start = std::chrono::system_clock::now();
		bubbleSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "BubbleSort","(n - 1) + (n - 2)... (2) + (1) = n*(n - 1)/2 or O(n^2)");
		//std::string Formulaa =+"                        Formula: (n - 1) + (n - 2)... (2) + (1) = n(n - 1)/2 or O(n^2)";
	    //displayText(Formulaa,5, .89 * SCREEN_HEIGHT);
	} break;
	case 32: {
		auto start = std::chrono::system_clock::now();
		mergeSort(0, numElements - 1);
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "MergeSort","T(n) = T(n/2) + T(n/2) + n, if n>1");
	} break;
	case 33: {
		auto start = std::chrono::system_clock::now();
		quickSort(0, numElements - 1);
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "QuickSort","T(n) = T(k) + T(n-k-1) + Θ(n)");
	} break;
	case 34: {
		auto start = std::chrono::system_clock::now();
		selectionSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "SelectionSort","(n - 1) + (n - 2)... (2) + (1) = n*(n - 1)/2 or O(n^2)");
	} break;
	case 35: {
		auto start = std::chrono::system_clock::now();
		insertionSort();
		auto stop = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		displayTotalTime(diff.count(), "InsertionSort"," ∑q(from q=1 to p) = p*( p + 1 )/2 ");
	} break;
	case 4:exit(0);
	}
}

void createMenu() {
	int s1 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10 Numbers", 11);
	glutAddMenuEntry("20 Numbers", 12);
	glutAddMenuEntry("50 Numbers", 13);
	glutAddMenuEntry("100 Numbers", 14);
	glutAddMenuEntry("200 Numbers", 15);
	//glutAddMenuEntry("1000 Numbers", 16);

	int s2 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("10", 21);
	glutAddMenuEntry("20", 22);
	glutAddMenuEntry("50", 23);
	glutAddMenuEntry("100", 24);
	//glutAddMenuEntry("500", 25);

	int s3 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("BubbleSort", 31);
	glutAddMenuEntry("MergeSort", 32);
	glutAddMenuEntry("QuickSort", 33);
	glutAddMenuEntry("SelectionSort", 34);
	glutAddMenuEntry("InsertionSort", 35);

	glutCreateMenu(menuFunc);
	glutAddSubMenu("Values", s1);
	glutAddSubMenu("Speed", s2);
	glutAddSubMenu("Sort", s3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
