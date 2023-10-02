#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D Ball Drop");
    
    // Create a Box2D world with gravity
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // Create a ground body
    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create a dynamic ball
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(0.0f, 20.0f);
    b2Body* ballBody = world.CreateBody(&ballDef);

    b2CircleShape ballShape;
    ballShape.m_radius = 1.0f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &ballShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    ballBody->CreateFixture(&fixtureDef);

    // Set up the time step and velocity iterations
    float timeStep = 1.0f / 2000.0f;
    int velocityIterations = 6;
    int positionIterations = 2;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Simulate the world
        world.Step(timeStep, velocityIterations, positionIterations);

        // Get the position of the ball
        b2Vec2 ballPosition = ballBody->GetPosition();

        // Draw the ball
        sf::CircleShape circle(10.0f); // Radius of the circle in pixels
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(400.0f + ballPosition.x * 30.0f, 600.0f - ballPosition.y * 30.0f);
        window.draw(circle);

        // Display everything
        window.display();
    }

    return 0;
}
