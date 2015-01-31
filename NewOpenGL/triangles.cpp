////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	triangles.cpp
///
/// @brief	Implements the triangles in OpenGl.
////////////////////////////////////////////////////////////////////////////////////////////////////
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
const GLuint num_vertices = 6;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	void init(void)
///
/// @brief	Initialises this object.
/// 		1 - vertex information for later use when rendering  
/// 		2 - LoadShaders() routine to simplify the process of preparing shaders for GPU  
/// 		3 - shader plumbing : associate data with variables in shader programs
///
/// @author	Rémi
/// @date	21/02/2014
////////////////////////////////////////////////////////////////////////////////////////////////////

void init(void)
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	glGenVertexArrays(NUM_VAOS, tab_vaos);
	///
	/// @brief	To generate Vertex array.
	///
	/// @author	Rémi
	/// @date	22/02/2014
	///
	/// @param	parameter1	GLsizei.
	/// @param	parameter2	GLuint* arrays.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glGenVertexArrays(NUM_VAOS, tab_vaos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	glBindVertexArray(tab_vaos[TRIANGLES]);
	///
	/// @brief	To bind with vertex array object.
	///
	/// @author	Rémi
	/// @date	22/02/2014
	///
	/// @param	parameter1	GLuint array.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glBindVertexArray(tab_vaos[TRIANGLES]);

	GLfloat vertices[num_vertices][2] = {
		{ -0.90, -0.90 }, // Triangle 1
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },
		{ 0.90, -0.85 }, // Triangle 2
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	glGenBuffers(NUM_BUFFERS, tab_buffers);
	///
	/// @brief	To generate vertex buffer.
	///
	/// @author	Rémi
	/// @date	22/02/2014
	///
	/// @param	parameter1	Glsizei.
	/// @param	parameter2	GLuint* buffers.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glGenBuffers(NUM_BUFFERS, tab_buffers);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	glBindBuffer(GL_ARRAY_BUFFER, tab_buffers[ARRAY_BUFFER]);
	///
	/// @brief	To bind with vertex buffer object.
	///
	/// @author	Rémi
	/// @date	22/02/2014
	///
	/// @param	parameter1	GLenum target.
	/// @param	parameter2	CLuint buffer.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glBindBuffer(GL_ARRAY_BUFFER, tab_buffers[ARRAY_BUFFER]);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	///
	/// @brief	To load data.
	///
	/// @author	Rémi
	/// @date	22/02/2014
	///
	/// @param	parameter1	GLenum target.
	/// @param	parameter2	GLsizeiptr size.
	/// @param	parameter3	const GLvoid* data.
	/// @param	parameter4	GLenum usage.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
		glVertexAttribPointer(V_POSITION, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(V_POSITION);
	glUseProgram(0);
	//glClearColor(0, 0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	void display(void)
///
/// @brief	Displays this object.
/// 		1 - clear the window  
/// 		2 - OpenGL calls required to render object  
/// 		3 - request thate the image is presented to the screen
///
/// @author	Rémi
/// @date	21/02/2014
////////////////////////////////////////////////////////////////////////////////////////////////////

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(tab_vaos[TRIANGLES]);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	glFlush();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	int main(int argc, char** argv)
///
/// @brief	Main entry-point for this application.
/// 		1 - creating a window  
/// 		2 - calling init  
/// 		3 - entering in the event loop
///
/// @author	Rémi
/// @date	21/02/2014
///
/// @param	argc	Number of command-line arguments.
/// @param	argv	Array of command-line argument strings.
///
/// @return	Exit-code for the process - 0 for success, else an error code.
////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

    /* This line is an obligation to display the triangle */
	glewExperimental = GL_TRUE;
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}