#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define gravity 9.81

using namespace std;

void CirclePosition(sf::RenderWindow &Physics, sf:: Event &event, sf::Text &Ctext, float &radius, float &X, float &Y, sf::CircleShape &Circle)
{


    sf::Vector2f position = Circle.getPosition(); // Gets the X & Y position



    radius = Circle.getRadius(); // Gets the Radius

    string Position = "X: " + to_string(position.x) + " Y: " + to_string(position.y); // Displays the Position of X & Y

    X = position.x + radius; // Add radius to Make it Center
    Y = position.y + radius;

    Ctext.setString(Position); // Print the text
    Ctext.setPosition(500,50); // position of text
    Physics.draw(Ctext); // draws the text


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

sf::Event event;
sf:: Font font;
sf:: Text text;
sf:: Text Ctext;
sf:: Clock clock;

if(!font.loadFromFile("C:\\Users\\joach_a5sww\\OneDrive\\Documents\\(C++)\\SFML\\Physics\\Fonts\\arial_mt_black\\ARIBL0.ttf")) // location of the font
{
    cout << "Faile to load!" << endl; // displays in terminal
    return 1;
}

text.setFont(font);
text.setCharacterSize(15);
text.setFillColor(sf::Color::White);
text.setPosition(50,50);

Ctext.setFont(font);
Ctext.setCharacterSize(15);
Ctext.setFillColor(sf::Color::White);


sf::Vector2i Dragoffset; // position of drag
sf::CircleShape Circle(50); // Circle Size
Circle.setFillColor(sf::Color::Red); // Circle Color
Circle.setPosition(350,250); // Circle Position

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
    Physics.draw(text); // draws the text


    sf::Vector2i position = sf::Mouse::getPosition(Physics); // Gets position of mouse


    string PositionText = "X: " + to_string(position.x) + " Y: " + to_string(position.y); // Displays the current position

    float DeltaTime = clock.restart().asSeconds() * 10.0f;

    float MouseX = position.x; // mouse position
    float MouseY = position.y;


    CirclePosition(Physics, event, Ctext, Circleradius, CircleX, CircleY, Circle); // Gets data of circle
    Pythagorean(Circleradius, CircleX, CircleY, MouseX, MouseY, Circle); // Checks distance of radius and mouse



    while(Physics.pollEvent(event))
    {
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {

        Dragging(Circle, position, Circleradius, Dragoffset, Clicked);
    }

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
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
    Physics.draw(Ctext);
    text.setString(PositionText);
    Physics.draw(text);
    Physics.display();
}


}
