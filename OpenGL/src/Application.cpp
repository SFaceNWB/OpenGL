#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "vertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

	std::cout << glGetString(GL_VERSION) << std::endl;
    {

        float Positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        //unsigned int vertexArrayObject;
        //GLCall(glGenVertexArrays(1, &vertexArrayObject));
        //GLCall(glBindVertexArray(vertexArrayObject));

        VertexArray va;
        VertexBuffer vb(Positions, 4 * 2 * sizeof(float));
        //unsigned int buffer; 
        //GLCall(glGenBuffers(1, &buffer));
        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        //GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), Positions, GL_STATIC_DRAW));

		VertexBufferLayout layout;
		layout.Push<float>(2);
        //GLCall(glEnableVertexAttribArray(0));
        //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
		va.AddBuffer(vb, layout);

        

        IndexBuffer ib(indices, 6);
        //unsigned int indexBufferObject;
        //glGenBuffers(1, &indexBufferObject);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        //ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        //unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        //glUseProgram(shader);
		shader.SetUniform4f("u_Color", 0.6f, 0.3f, 0.6f, 1.0f);
        //GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        //ASSERT(location != -1);
        //GLCall(glUniform4f(location, 0.6f, 0.3f, 0.6f, 1.0f));

        va.Unbind();
        //GLCall(glBindVertexArray(0));
        shader.Unbind();
        //GLCall(glUseProgram(0));
        vb.Unbind();
        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		ib.Unbind();
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
			renderer.Clear();
            //GLCall(glClear(GL_COLOR_BUFFER_BIT));

            shader.Bind();
            //GLCall(glUseProgram(shader));
			shader.SetUniform4f("u_Color", r, 0.3f, 0.6f, 1.0f);
            //GLCall(glUniform4f(location, r, 0.3f, 0.6f, 1.0f));

			renderer.Draw(va, ib, shader);
            //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}