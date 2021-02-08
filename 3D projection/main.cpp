#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Functions.h"

#define M_PI 3.14159265358979323846

#define WIDTH 1600
#define HEIGHT 900

#define FRAMETIME 16666

using namespace std;

int main()
{
	//Variables for projection matrix
	float fNear = 1.0f;
	float fFar = 1000.f;
	float fov = 90.f;
	float aRatio = (float)WIDTH / (float)HEIGHT;
	float fFov = 1 / (float)tan(fov * 0.5f / 180.f * M_PI);

	mat4x4 projectionMatrix;

	projectionMatrix.mat[0][0] = aRatio * fFov;
	projectionMatrix.mat[1][1] = fFov;
	projectionMatrix.mat[2][2] = fFar / (fFar - fNear);
	projectionMatrix.mat[3][2] = (-fFar * fNear) / (fFar - fNear);
	projectionMatrix.mat[2][3] = 1.0f;
	projectionMatrix.mat[3][3] = 0.0f;

	//Objects to draw
	mesh mCube;
	mCube.createCube();

    float r_time=0;
    sf::Clock zegar;
    sf::Clock zegar2;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");

    while (window.isOpen()) 
	{
        sf::Event event;
        while (window.pollEvent(event)) 
		{
            if (event.type == sf::Event::Closed) 
				window.close();
        }

        if (zegar2.getElapsedTime().asMicroseconds() >= FRAMETIME - r_time) 
		{
            zegar2.restart();
            zegar.restart();

            window.clear();

			for (auto t : mCube.mVector)
			{
				triangle tTranslated, tProjected;

				//Offset the cube
				tTranslated = t;
				tTranslated.p[0].z = t.p[0].z + 3.0f;
				tTranslated.p[1].z = t.p[1].z + 3.0f;
				tTranslated.p[2].z = t.p[2].z + 3.0f;

				//Project
				MultiplyMatrixVector(tTranslated.p[0], tProjected.p[0], projectionMatrix);
				MultiplyMatrixVector(tTranslated.p[1], tProjected.p[1], projectionMatrix);
				MultiplyMatrixVector(tTranslated.p[2], tProjected.p[2], projectionMatrix);

				//std::cout << tProjected.p[0].x;

				//Scale
				tProjected.p[0].x = 1.0f; tProjected.p[0].y += 1.0f;
				tProjected.p[1].x += 1.0f; tProjected.p[1].y += 1.0f;
				tProjected.p[2].x += 1.0f; tProjected.p[2].y += 1.0f;
				tProjected.p[0].x *= 0.5f * (float)WIDTH;
				tProjected.p[0].y *= 0.5f * (float)HEIGHT;
				tProjected.p[1].x *= 0.5f * (float)WIDTH;
				tProjected.p[1].y *= 0.5f * (float)HEIGHT;
				tProjected.p[2].x *= 0.5f * (float)WIDTH;
				tProjected.p[2].y *= 0.5f * (float)HEIGHT;

				// create an array of 3 vertices that define a triangle primitive
				sf::VertexArray triangle(sf::Triangles, 3);

				// define the position of the triangle's points
				triangle[0].position = sf::Vector2f(tProjected.p[0].x, tProjected.p[0].y);
				triangle[1].position = sf::Vector2f(tProjected.p[1].x, tProjected.p[1].y);
				triangle[2].position = sf::Vector2f(tProjected.p[2].x, tProjected.p[2].y);

				// define the color of the triangle's points
				triangle[0].color = sf::Color::White;
				triangle[1].color = sf::Color::White;
				triangle[2].color = sf::Color::White;

				window.draw(triangle);
			}

            window.display();

            r_time=zegar.getElapsedTime().asMicroseconds();
        }
    }

    return 0;
}
