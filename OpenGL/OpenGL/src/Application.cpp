#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Draw Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Get access to modern OpenGL functionality */
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Create a buffer */
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    /* Select the buffer by binding */
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    /* Specify the data */
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    /* Enable the vertex attribute */
    glEnableVertexAttribArray(0);

    /* Define the layout of data 
        0 - index of first attribute
        2 - 'size' or number of components representing vertex attribute position
        GL_FLOAT - type of data
        GL_FALSE - don't want to normalize data
        sizeof(float) * 2 - size of stride to get to next vertex
        nullptr - pointer to attribute in vertex, in this case, the first byte
    */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw the data currently bound */
        glDrawArrays(GL_TRIANGLES, 0, 3);
   
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}