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
    window = glfwCreateWindow( 1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
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

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);




    GLuint programID = LoadShaders(
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task2_volumetric_figure/TransformVertexShader.vertexshader",
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task2_volumetric_figure/ColorFragmentShader.fragmentshader"
    );

    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");

    static const GLfloat g_vertex_buffer_data[] = {
            0, -3, 0,
            0, 0, 1,
            1, 0, 0,
            0, -3, 0,
            1, 0, 0,
            0.5, 0, -1,
            0, -3, 0,
            0.5, 0, -1,
            -0.5, 0, -1,
            0, -3, 0,
            -0.5, 0, -1,
            -1, 0, 0,
            0, -3, 0,
            -1, 0, 0,
            0, 0, 1,
// крышка
            0, 0, 1,
            1, 0, 0,
            0.5, 0, -1,
            0, 0, 1,
            0.5, 0, -1,
            -0.5, 0, -1,
            0, 0, 1,
            -0.5, 0, -1,
            -1, 0, 0
    };

    static const GLfloat g_color_buffer_data[] = {
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            // дно
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");






    GLuint triangID = LoadShaders(
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task2_volumetric_figure/TransformVertexShader.vertexshader",
            "/Users/s.perchuk/Desktop/workspace/Projects/OpenGLTutorials2.1/task2_volumetric_figure/SingleColorOpaque.fragmentshader"
    );

    GLuint triang_vertexPosition = glGetAttribLocation(triangID, "vertexPosition_modelspace");
    GLuint triang_vertexColor = glGetAttribLocation(triangID, "vertexColor");

    GLuint triang_matrix = glGetUniformLocation(triangID, "MVP");

    static const GLfloat triang_vertex_buffer_data[] = {
            // дно
            0, 3, 0,
            0, 1, 1,
            1, 1, 0,
            0, 3, 0,
            1, 1, 0,
            0.5, 1, -1,
            0, 3, 0,
            0.5, 1, -1,
            -0.5, 1, -1,
            0, 3, 0,
            -0.5, 1, -1,
            -1, 1, 0,
            0, 3, 0,
            -1, 1, 0,
            0, 1, 1,
// крышка
            0, 1, 1,
            1, 1, 0,
            0.5, 1, -1,
            0, 1, 1,
            0.5, 1, -1,
            -0.5, 1, -1,
            0, 1, 1,
            -0.5, 1, -1,
            -1, 1, 0
    };
    static const GLfloat triang_color_buffer_data[] = {
            // крышка
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.8,0,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            0.8,0.3,0.8,
            // дно
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
            0.3, 0.6, 0.3,
    };

    GLuint triang_vertexbuffer;
    glGenBuffers(1, &triang_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triang_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triang_vertex_buffer_data), triang_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint triang_colorbuffer;
    glGenBuffers(1, &triang_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triang_colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triang_color_buffer_data), triang_color_buffer_data, GL_STATIC_DRAW);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int cnt = 0;
    do{
        cnt++;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(programID);

        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                vertexPosition_modelspaceID, // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*)0                     // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(vertexColorID);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                vertexColorID,               // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*)0                     // array buffer offset
        );


        glm::mat4 View       = glm::lookAt(
                glm::vec3(4,4,3),
                glm::vec3(0,0,0),
                glm::vec3(0,1,0)
        );
        glm::mat4 Model      = glm::mat4(1.0f);
        Model = glm::rotate(Model, 45.0f * cnt / 1000, glm::vec3(0.0, 1, 0));
        glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        glm::mat4 MVP        = Projection * View * Model;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Draw the triangleS !
        glDrawArrays(GL_TRIANGLES, 0, 8*3);

        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexColorID);





        glUseProgram(triangID);

        glEnableVertexAttribArray(triang_vertexPosition);
        glBindBuffer(GL_ARRAY_BUFFER, triang_vertexbuffer);
        glVertexAttribPointer(
                triang_vertexPosition, // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*)0                     // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(triang_vertexColor);
        glBindBuffer(GL_ARRAY_BUFFER, triang_colorbuffer);
        glVertexAttribPointer(
                triang_vertexColor,               // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*)0                     // array buffer offset
        );


        glm::mat4 triang_Model      = glm::mat4(1.0f);
        triang_Model = glm::rotate(triang_Model, -45.0f * cnt / 1000, glm::vec3(0.0, 1, 0));
        glm::mat4 triang_MVP        = Projection * View * triang_Model;

        glUniformMatrix4fv(triang_matrix, 1, GL_FALSE, &triang_MVP[0][0]);

        // Draw the triangleS !
        glDrawArrays(GL_TRIANGLES, 0, 24);

        glDisableVertexAttribArray(triang_vertexPosition);
        glDisableVertexAttribArray(triang_vertexColor);



        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(programID);

    glDeleteBuffers(1, &triang_vertexbuffer);
    glDeleteBuffers(1, &triang_colorbuffer);
    glDeleteProgram(triangID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

