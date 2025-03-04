#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>

GLFWwindow *StartGLFW();
void draw_circle(float centerX, float centerY, float radius, int res);
float screenHeight = 600.0f;
float screenWidth = 800.0f;

int main()
{
    GLFWwindow *window = StartGLFW();
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 50;

    float velocity[] = {0.0f, 0.0f};
    float positions[] = {0.0f, 0.0f};

    positions[0] = centerX;
    positions[1] = screenHeight - radius;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_circle(positions[0], positions[1], radius, res);
        glFlush();

        printf("Circle position: (%.2f, %.2f)\n", positions[0], positions[1]);

        positions[1] += -9.81f / 20.0f;

        if (positions[1] < radius)
        {
            positions[1] = screenHeight - radius;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLFWwindow *StartGLFW()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to init");
        return NULL;
    }

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "gravity_sim", NULL, NULL);

    return window;
}

void draw_circle(float centerX, float centerY, float radius, int res)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(centerX, centerY);

    for (int i = 0; i <= res; ++i)
    {
        float angle = 2.0f * 3.141592653589f * ((float)i / (float)res);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;

        glVertex2d(x, y);
    }

    glEnd();
}