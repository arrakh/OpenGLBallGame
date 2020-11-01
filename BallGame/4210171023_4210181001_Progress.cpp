#include<stdio.h> 
#include<glut.h> 
#include<math.h> 
#define pi 3.142857 

//c dan d adalah jumlah kiri kanan
int c = 0, d = 0, left = 0, right = 0;
int m = 0, j = 1, flag1 = 0, l = 1, flag2 = 0, n = 0, score = 0, count = 1;

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColor3f(0.0f, 1.0f, 0.0f);

	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set Window
	gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}


void keyboard(unsigned char key, int x, int y)
{
	left = -200 + 200 * (d - c);
	right = 200 + 200 * (d - c);

	//Jika sampai ujung kiri, berhenti bergerak
	if (left == -600)
	{
		//Gerak ke kanan dengan D
		if (key == 100)
			d++;
	}
	
	//Jika sampai ujung kanan, berhenti bergerak
	else if (right == 600)
	{
		//Gerak ke kanan dengan A
		if (key == 97)
			c++;
	}
	
	else
	{
		//Gerak ke kanan dengan A
		if (key == 97)
			c++;

		//Gerak ke kanan dengan D
		if (key == 100)
			d++;
	}
	glutPostRedisplay();
}

void myDisplay(void)
{
	int x, y, k;
	
	//Pergerakan Bola
	for (k = 0; k <= 400; k += 5)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_STRIP);

		// i untuk angle Bola
		float i = 0;
		
		// Gerakkan Bola
		m = m + 3;
		n = n + 2;

		// Gambar Bola berdasarkan pi
		while (i <= 2 * pi)
		{
			y = 12 + 20 * cos(i);
			x = 20 * sin(i);
			i = i + 0.1;
			
			//Tabrak Atas Bawah
			if (m == 288 && flag1 == 0)
			{
				j = -1;
				m = -288;
				flag1 = 1;
				score++;
			}
			if (m == 288 && flag1 == 1)
			{
				j = 1;
				m = -288;
				flag1 = 0;
			}

			// Tabrak Kiri Kanan
			if (n == 580 && flag2 == 0)
			{
				l = -1;
				n = -580;
				flag2 = 1;
			}
			if (n == 580 && flag2 == 1)
			{
				l = 1;
				n = -580;
				flag2 = 0;
			}
			// Arah Bola
			glVertex2i((x - l * n), (y - j * m));
		}
		glEnd();

		// Window
		glBegin(GL_LINE_LOOP);
		glVertex2i(-600, -320);
		glVertex2i(-600, 320);
		glVertex2i(600, 320);
		glVertex2i(600, -320);
		glEnd();

		// Paddle
		glBegin(GL_LINE_LOOP);
		left = -200 + 200 * (d - c);
		right = 200 + 200 * (d - c);
		glVertex2i(left, -315);
		glVertex2i(left, -295);
		glVertex2i(right, -295);
		glVertex2i(right, -315);
		glEnd();

		// Apakah Ball Fail / Tertangkap Paddle?
		if ((j * m) == 276)
		{
			if ((left > ((-1 * l * n) + 20)) || (right < (-1 * l * n) - 20))
			{
				printf("Game Over !!!\nYour Score is :\t%d\n", score);
				exit(0);
			}
		}
		glutSwapBuffers();
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1100, 600);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("BallGame");

	glutKeyboardFunc(keyboard);
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
