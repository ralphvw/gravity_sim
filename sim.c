#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>

GLFWwindow *StartGLFW();
void draw_circle(float centerX, float centerY, float radius, int res);

float screenHeight = 600.0f;
float screenWidth = 800.0f;
const float gravity = -9.81f;
const float bounceFactor = 0.8f;
const float timeStep = 0.0016f;

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
    float radius = 50.0f;
    int res = 50;

    float velocityY = 0.0f;
    float positionY = screenHeight - radius;

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (deltaTime >= timeStep)
        {
            velocityY += gravity * deltaTime;
            positionY += velocityY * deltaTime;

            if (positionY < radius)
            {
                positionY = radius;
                velocityY = -velocityY * bounceFactor;
            }

            if (positionY > screenHeight - radius)
            {
                positionY = screenHeight - radius;
                velocityY = -velocityY * bounceFactor;
            }

            printf("Position: %.2f | Velocity: %.2f | DeltaTime: %.4f\n", positionY, velocityY, deltaTime);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        draw_circle(centerX, positionY, radius, res);
        glFlush();

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
        fprintf(stderr, "Failed to init\n");
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
        float angle = 2.0f * M_PI * ((float)i / (float)res);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;

        glVertex2d(x, y);
    }

    glEnd();
}