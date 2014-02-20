#include <iostream>
#include <glew.h>
#include <GL/glut.h>

enum VAO_IDs{
	TRIANGLES,
	NUM_VAOS
};

enum Buffer_IDs{
	ARRAY_BUFFER,
	NUM_BUFFERS
};

enum Attrib_IDs {
	VPOSITION = 0;
};

GLuint VAOs[NUM_VAOS];
GLuint Buffers[NUM_BUFFERS];

const GLuint num_vertices = 6;


void init()
{
	glGenVertexArrays{ NUM_VAOS, VAOs };
	glBindVertexArray{ VAOs[TRIANGLES] };

	GLfloat vertices[num_vertices][2] = {
		{-0.90,-0.90},
		{0.85,-0.90},
		{-0.90,0.85},
		{0.90,-0.85},
		{0.90,0.90},
		{-0.85,0.90}
	};

	glGenBuffers(NUM_BUFFERS, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER,)

}