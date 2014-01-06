#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "gamedesktop.h"

int main(int argc, char* argv[])
{
  sf::RenderWindow screen(sf::VideoMode(640, 480), "Hello CEGUI!");
  GameDesktop gd(screen);

  sf::Event event;
  sf::Clock clock;
  sf::CircleShape shape;
  shape.setRadius(10);
  shape.setPosition(0, 300);

  while (screen.isOpen())
  {
    while (screen.pollEvent(event))
    {
      gd.handleEvent(event);

      if (event.type == sf::Event::Closed)
        screen.close();
    }

    gd.update(clock.restart());
    screen.clear();
    screen.draw(shape);
    shape.move(0.1f, 0);
    shape.scale(1.0001f, 1.0001f);

    if (shape.getPosition().x >= screen.getSize().x)
    {
      shape.setPosition(0, 300);
      shape.setScale(1, 1);
    }

    gd.draw();
    screen.display();
  }

  return 0;
}
