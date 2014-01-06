#ifndef GAMEDESKTOP_H
#define GAMEDESKTOP_H

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

class GameDesktop
{
  public:
    GameDesktop(sf::RenderWindow &screen);

    void handleEvent(const sf::Event &event);
    void update(sf::Time delta);
    void draw();

  private:
    void initializeKeyMap();
    CEGUI::Key::Scan toCEGUIKey(sf::Keyboard::Key code);
    CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button button);

    sf::RenderWindow& screen_;
    CEGUI::OpenGLRenderer& renderer_;
    CEGUI::WindowManager* wm_;

    std::map<sf::Keyboard::Key, CEGUI::Key::Scan> key_map_;
    std::map<sf::Mouse::Button, CEGUI::MouseButton> mouse_map_;

    sf::View view_;
    float zoom_;
};

#endif // GAMEDESKTOP_H
