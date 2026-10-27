#include <cmath>
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define gravity 9.81

void CirclePosition(float &radius, float &X, float &Y, const sf::CircleShape &Circle)
{
    sf::Vector2f position = Circle.getPosition(); // Gets the X & Y position
    radius = Circle.getRadius(); // Gets the Radius
    X = position.x + radius; // Add radius to Make it Center
    Y = position.y + radius;
}

void Pythagorean(float Radius, float CircleX, float CircleY, float MouseX, float MouseY, sf::CircleShape &Circle)
{
float FY = CircleY - MouseY;
float FX = CircleX - MouseX;
float Result = sqrt(FX * FX + FY * FY); // Distance between the mouse and the radius


if(Result < Radius) // changes color if parameter is met and the cursor is inside the circle
{
    Circle.setFillColor(sf::Color::White);

} else
{
    Circle.setFillColor(sf::Color::Red);
}


}

void Gravity(sf:: CircleShape &Circle, float Gvalue, float Radius, float DeltaTime, float &velocityX, float &velocityY)
{
sf::Vector2f position = Circle.getPosition();


velocityY += Gvalue * DeltaTime;
position.y += velocityY * DeltaTime;
position.x += velocityX * DeltaTime;

if(position.y + Radius * 2 >= 600)
{
    position.y = 600 - Radius * 2;
    velocityY = -velocityY * 0.9;
}

if(position.x + Radius * 2 >= 800)
{
    position.x = 800 - Radius * 2;
    velocityX = -velocityX * 0.9;
}

Circle.setPosition(position);


}

void Dragging(sf::CircleShape &Circle, sf::Vector2i &position, float CircleRadius, sf::Vector2i &Dragoffset, bool &clicked)
{


float MouseX = position.x;
float MouseY = position.y;

sf::Vector2f Cposition = Circle.getPosition();

float CircleY = Cposition.y + CircleRadius;
float CircleX = Cposition.x + CircleRadius;

float FY = CircleY - MouseY;
float FX = CircleX - MouseX;
float result = sqrt(FY * FY + FX * FX);

if(result < CircleRadius)
{

    clicked = true;
    Dragoffset.x = Cposition.x - MouseX;
    Dragoffset.y = Cposition.y - MouseY;
}


}
//                                                                   Mouse Position
void UpdateDrag(sf::CircleShape &Circle,sf::Vector2i &Dragoffset, sf::Vector2i &position, float &VX, float &VY)
{
sf::Vector2f Cposition = Circle.getPosition();


Cposition.x = position.x + Dragoffset.x;
Cposition.y = position.y + Dragoffset.y;
VX = 0;
VY = 0;

Circle.setPosition(Cposition);


}

int main()
{
sf::RenderWindow Physics(sf::VideoMode({800, 600}), "Physics Ball"); // Window


sf::RectangleShape Background(sf::Vector2f(800,600)); // Background
Background.setFillColor(sf::Color::Black); // Background Color

sf::Font font;
if (!font.openFromFile("Fonts/arial_mt_black/ARIBL0.ttf"))
    return 1;

sf::Text text(font, "", 15);
sf::Text Ctext(font, "", 15);
text.setFillColor(sf::Color::White);
Ctext.setFillColor(sf::Color::White);
text.setPosition({50.f, 50.f});
Ctext.setPosition({500.f, 50.f});

sf:: Clock clock;


sf::Vector2i Dragoffset; // position of drag
sf::CircleShape Circle(50); // Circle Size
Circle.setFillColor(sf::Color::Red); // Circle Color
Circle.setPosition({350.f, 250.f}); // Circle Position

float Circleradius = 0;
float CircleX = 0;
float CircleY = 0;
float Gvalue = 9.81f;

float velocityX = 0;
float velocityY = 0;
bool Clicked = false;
/*----------------------------------------------------------------------------------------------------------------------------------------*/




while(Physics.isOpen())
{

    Physics.clear(); // Clears the screen per frame
    Physics.draw(Background); // draw background
    sf::Vector2i position = sf::Mouse::getPosition(Physics); // Gets position of mouse


    float DeltaTime = clock.restart().asSeconds() * 10.0f;

    float MouseX = position.x; // mouse position
    float MouseY = position.y;


    CirclePosition(Circleradius, CircleX, CircleY, Circle); // Gets data of circle
    Pythagorean(Circleradius, CircleX, CircleY, MouseX, MouseY, Circle); // Checks distance of radius and mouse



    while (const std::optional event = Physics.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            Physics.close();

        if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (pressed->button == sf::Mouse::Button::Left)
                Dragging(Circle, position, Circleradius, Dragoffset, Clicked);
        }

        if (const auto* released = event->getIf<sf::Event::MouseButtonReleased>())
        {
            if (released->button == sf::Mouse::Button::Left)
                Clicked = false;
        }
    }


    if(Clicked)
    {
        UpdateDrag(Circle,Dragoffset, position, velocityX, velocityY);
    }
    else
    {
        Gravity(Circle, Gvalue, Circleradius, DeltaTime, velocityX, velocityY); // Gravity for circle
    }




    Physics.draw(Circle);
    const std::string mousePositionText = "X: " + std::to_string(position.x) + " Y: " + std::to_string(position.y);
    const std::string circlePositionText = "X: " + std::to_string(static_cast<int>(CircleX)) +
                                           " Y: " + std::to_string(static_cast<int>(CircleY));
    text.setString(mousePositionText);
    Ctext.setString(circlePositionText);
    Physics.draw(text);
    Physics.draw(Ctext);
    Physics.display();
}


}
