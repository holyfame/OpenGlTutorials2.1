// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <iostream>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint triang1 = LoadShaders(
	        "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task1_triangles/SimpleTransform.vertexshader",
	        "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task1_triangles/SingleColor.fragmentshader"
    );

    GLuint triang2 = LoadShaders(
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task1_triangles/SimpleTransform.vertexshader",
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task1_triangles/SingleColor2.fragmentshader"
    );


    GLuint Matrix1 = glGetUniformLocation(triang1, "MVP");
    GLuint Matrix2 = glGetUniformLocation(triang2, "MVP");

	GLuint vertexPosition_modelspaceID = glGetAttribLocation(triang1, "vertexPosition_modelspace");

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.5f,  1.0f, 0.0f,
		 -8.0f, -1.0f, 0.2f,
		 1.0f, -1.0f, 0.2f,
		 -0.5f, 1.0f, 0.2f
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int cnt = 0;
	do {

	    cnt += 1;

		glClear( GL_COLOR_BUFFER_BIT );

		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

        glm::mat4 View       = glm::lookAt(
                glm::vec3(4,3,3),
                glm::vec3(0,0,0),
                glm::vec3(0,1,0)
        );
        glm::mat4 Model      = glm::mat4(1.0f);
        Model = glm::rotate(Model, 45.0f * cnt / 1000, glm::vec3(0.0, 1.0, 0));
        glm::mat4 MVP        = Projection * View * Model;

        glUseProgram(triang1);
        glUniformMatrix4fv(Matrix1, 1, GL_FALSE, &MVP[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glUseProgram(triang2);
        glUniformMatrix4fv(Matrix2, 1, GL_FALSE, &MVP[0][0]);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		glDisableVertexAttribArray(vertexPosition_modelspaceID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(triang1);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

