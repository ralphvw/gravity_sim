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
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 50;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_circle(centerX, centerY, radius, res);

        centerY -= 1.0f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *StartGLFW()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to init");
        return NULL;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "gravity_sim", NULL, NULL);

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