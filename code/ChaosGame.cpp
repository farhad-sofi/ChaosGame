#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>

using namespace sf;
using namespace std;



void generateTrianglePoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    for (int i = 0; i < 100; ++i) {
        int randIndex = rand() % 3;
        Vector2f midpoint = (vertices[randIndex] + points.back()) / 2.f;
        points.push_back(midpoint);
    }
}

void generateSquarePoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    static int lastIndex = -1;

    for (int i = 0; i < 100; ++i) {
        int randIndex;
        do {
            randIndex = rand() % 4;
        } while (randIndex == lastIndex); // avoid repeating the same vertex

        lastIndex = randIndex;
        Vector2f midpoint = (vertices[randIndex] + points.back()) / 2.f;
        points.push_back(midpoint);
    }
}
void generateOctagonPoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    static int lastIndex = -1;

    for (int i = 0; i < 100; ++i)
    {
        int randIndex;
        do {
            randIndex = rand() % 8;
        } while (
            randIndex == lastIndex || randIndex == (lastIndex + 1) % 8 || randIndex == (lastIndex + 7) % 8
            );

        lastIndex = randIndex;
        Vector2f midpoint = (vertices[randIndex] + points.back()) / 2.f;
        points.push_back(midpoint);
    }
}

void generateSpiralPoints(vector<Vector2f>& points, const vector<Vector2f>& vertices) {
    for (int i = 0; i < 100; ++i) {
        int randIndex = rand() % vertices.size();
        Vector2f lastPoint = points.back();
        Vector2f vertex = vertices[randIndex];

        // Translate to origin
        Vector2f dir = vertex - lastPoint;

        // Rotate slightly
        float angle = 0.05f; 
        float cosA = cos(angle);
        float sinA = sin(angle);

        Vector2f rotated(
            cosA * dir.x - sinA * dir.y,
            sinA * dir.x + cosA * dir.y
        );

        rotated *= 0.97f;

        // Translate back
        Vector2f spiralPoint = lastPoint + rotated;
        points.push_back(spiralPoint);
    }
}





enum class Mode { None, Triangle, Square, Octagon , Spiral};

int main()
{
    // Create window
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game!!", Style::Default);
    window.setFramerateLimit(60);

    // Load font
    Font font;
    if (!font.loadFromFile("times.ttf")) {
        cout << "Font not found!" << endl;
        return -1;
    }

    // Instructions text
    Text instructions("", font, 24);
    instructions.setPosition(20, 20);
    instructions.setFillColor(Color::White);

    // Initial shape mode prompt
    Text shapePrompt("Press T for Triangle, S for Square, O for Octagon, R for Spiral", font, 30);
    shapePrompt.setPosition(60, 60);
    shapePrompt.setFillColor(Color::Yellow);

    vector<Vector2f> vertices;
    vector<Vector2f> points;


    Mode mode = Mode::None;
    int requiredVertices = 0;

    while (window.isOpen())
    {
        // Mode selection
        if (mode == Mode::None)
        {
            if (Keyboard::isKeyPressed(Keyboard::T))
            {
                mode = Mode::Triangle;
                requiredVertices = 3;
                instructions.setString("Click 3 points for triangle, then 1 point to start.");
            }
            else if (Keyboard::isKeyPressed(Keyboard::S))
            {
                mode = Mode::Square;
                requiredVertices = 4;
                instructions.setString("Click 4 points for square, then 1 point to start.");
            }
			else if (Keyboard::isKeyPressed(Keyboard::O))
			{
				mode = Mode::Octagon;
				requiredVertices = 8;
				instructions.setString("Click 8 points for octagon, then 1 point to start.");
			}
			else if (Keyboard::isKeyPressed(Keyboard::R))
			{
				mode = Mode::Spiral;
				requiredVertices = 5;
				instructions.setString("Click 5 points for spiral, then 1 point to start.");
			}
        }

        // --- Handle input ---
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left)
            {
                float x = event.mouseButton.x;
                float y = event.mouseButton.y;

                if (mode != Mode::None)
                {
                    if (vertices.size() < requiredVertices)
                    {
                        vertices.push_back(Vector2f(x, y));
                        cout << "Vertex " << vertices.size() << ": (" << x << ", " << y << ")" << endl;
                    }
                    else if (points.empty())
                    {
                        points.push_back(Vector2f(x, y));
                        cout << "Starting point: (" << x << ", " << y << ")" << endl;
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // --- Update ---
        if (!points.empty())
        {
            if (mode == Mode::Triangle)
                generateTrianglePoints(points, vertices);
            else if (mode == Mode::Square)
                generateSquarePoints(points, vertices);
			else if (mode == Mode::Octagon)
				generateOctagonPoints(points, vertices);
			else if (mode == Mode::Spiral)
				generateSpiralPoints(points, vertices);
        }


        // --- Draw ---
        window.clear();

        // Draw instructions and prompt
        window.draw(instructions);
        if (mode == Mode::None)
            window.draw(shapePrompt);

        // Draw vertices
        for (auto& v : vertices)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(v);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw points
        for (auto& p : points)
        {
            CircleShape dot(1);
            dot.setPosition(p);
            dot.setFillColor(Color::Green);
            window.draw(dot);
        }

        window.display();
    }

    return 0;
}

Text starterMessage;
Font font;
font.loadFromFile("C:\Users\User\Downloads\antzuw/");

