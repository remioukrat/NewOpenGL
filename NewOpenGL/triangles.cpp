///////////////////////////////////////////////////////////////////////
//
// triangles.cpp
//
///////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs 
{ 
	TRIANGLES,
	NUM_VAOS
};

enum Buffer_IDs 
{ 
	ARRAY_BUFFER,
	NUM_BUFFERS 
};

enum Attrib_IDs 
{ 
	V_POSITION = 0 
};

GLuint tab_vaos[NUM_VAOS];
GLuint tab_buffers[NUM_BUFFERS];
const GLuint NumVertices = 6;

//---------------------------------------------------------------------
//
// init
//
void
init(void)
{
	glGenVertexArrays(NUM_VAOS,tab_vaos);
	glBindVertexArray(tab_vaos[TRIANGLES]);
	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90 }, // Triangle 1
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },
		{ 0.90, -0.85 }, // Triangle 2
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};
	glGenBuffers(NUM_BUFFERS, tab_buffers);
	glBindBuffer(GL_ARRAY_BUFFER, tab_buffers[ARRAY_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "TRIANGLES.vert" },
		{ GL_FRAGMENT_SHADER, "TRIANGLES.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(V_POSITION, 2, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(V_POSITION);
}

//---------------------------------------------------------------------
//
// display
//
void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(tab_vaos[TRIANGLES]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush();
}

//---------------------------------------------------------------------
//
// main
//
int
main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}