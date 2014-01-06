#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "gamedesktop.h"

GameDesktop::GameDesktop(sf::RenderWindow &screen)
  : screen_(screen),
    renderer_(CEGUI::OpenGLRenderer::bootstrapSystem())
{
  // Set up default resource groups
  CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

  rp->setResourceGroupDirectory("schemes", "/usr/share/cegui-0/schemes/"); 
  rp->setResourceGroupDirectory("imagesets", "/usr/share/cegui-0/imagesets/");
  rp->setResourceGroupDirectory("fonts", "/usr/share/cegui-0/fonts/");
  rp->setResourceGroupDirectory("layouts", "/usr/share/cegui-0/layouts/");
  rp->setResourceGroupDirectory("looknfeels", "/usr/share/cegui-0/looknfeel");
  rp->setResourceGroupDirectory("lua_scripts", "/usr/share/cegui-0/lua_scripts/");

  CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
  CEGUI::Font::setDefaultResourceGroup("fonts");
  CEGUI::Scheme::setDefaultResourceGroup("schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
  CEGUI::WindowManager::setDefaultResourceGroup("layouts");
  CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

  // Set up the GUI
  CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
  CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("WindowsLook/MouseArrow");

  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *root = wmgr.createWindow("DefaultWindow", "root");
  root->setProperty("MousePassThroughEnabled", "True");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

  CEGUI::FrameWindow *fw = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow("WindowsLook/FrameWindow", "testWindow"));

  root->addChild(fw);
  fw->setText("Hello World!");

  // Initialize SFML-to-CEGUI key mapping
  initializeKeyMap();
  screen_.setView(view_);
}

void GameDesktop::handleEvent(const sf::Event &event)
{
  bool handled = false;
  CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
  sf::Vector2i mouse_pos; 

  switch (event.type)
  {
  case sf::Event::TextEntered:
    handled = context.injectChar(event.text.unicode); break;
  case sf::Event::KeyPressed:
    handled = context.injectKeyDown(toCEGUIKey(event.key.code)); break;
  case sf::Event::KeyReleased:
    handled = context.injectKeyUp(toCEGUIKey(event.key.code)); break;
  case sf::Event::MouseMoved:
    mouse_pos = sf::Mouse::getPosition(screen_);
    handled = context.injectMousePosition(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    break;
  case sf::Event::MouseButtonPressed:
    handled = context.injectMouseButtonDown(toCEGUIMouseButton(event.mouseButton.button)); break;
  case sf::Event::MouseButtonReleased:
    handled = context.injectMouseButtonUp(toCEGUIMouseButton(event.mouseButton.button)); break;
  case sf::Event::MouseWheelMoved:
    handled = context.injectMouseWheelChange(static_cast<float>(event.mouseWheel.delta)); break;
  case sf::Event::Resized:
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(event.size.width, event.size.height)); break;
  }

  // If mouse is over an UI element, we do not initiate drag scrolling
  if (!handled)
  {
    // we can handle this event here, CEGUI didn't use it ...    
  }
}

void GameDesktop::update(sf::Time delta)
{
  CEGUI::System::getSingleton().injectTimePulse(delta.asSeconds());
}

void GameDesktop::draw()
{
  // undo all transformations SFML did
  screen_.resetGLStates();
  CEGUI::System::getSingleton().renderAllGUIContexts();
}

void GameDesktop::initializeKeyMap()
{
  key_map_[sf::Keyboard::A]			= CEGUI::Key::A;
	key_map_[sf::Keyboard::B]			= CEGUI::Key::B;
	key_map_[sf::Keyboard::C]			= CEGUI::Key::C;
	key_map_[sf::Keyboard::D]			= CEGUI::Key::D;
	key_map_[sf::Keyboard::E]			= CEGUI::Key::E;
	key_map_[sf::Keyboard::F]			= CEGUI::Key::F;
	key_map_[sf::Keyboard::G]			= CEGUI::Key::G;
	key_map_[sf::Keyboard::H]			= CEGUI::Key::H;
	key_map_[sf::Keyboard::I]			= CEGUI::Key::I;
	key_map_[sf::Keyboard::J]			= CEGUI::Key::J;
	key_map_[sf::Keyboard::K]			= CEGUI::Key::K;
	key_map_[sf::Keyboard::L]			= CEGUI::Key::L;
	key_map_[sf::Keyboard::M]			= CEGUI::Key::M;
	key_map_[sf::Keyboard::N]			= CEGUI::Key::N;
	key_map_[sf::Keyboard::O]			= CEGUI::Key::O;
	key_map_[sf::Keyboard::P]			= CEGUI::Key::P;
	key_map_[sf::Keyboard::Q]			= CEGUI::Key::Q;
	key_map_[sf::Keyboard::R]			= CEGUI::Key::R;
	key_map_[sf::Keyboard::S]			= CEGUI::Key::S;
	key_map_[sf::Keyboard::T]			= CEGUI::Key::T;
	key_map_[sf::Keyboard::U]			= CEGUI::Key::U;
	key_map_[sf::Keyboard::V]			= CEGUI::Key::V;
	key_map_[sf::Keyboard::W]			= CEGUI::Key::W;
	key_map_[sf::Keyboard::X]			= CEGUI::Key::X;
	key_map_[sf::Keyboard::Y]			= CEGUI::Key::Y;
	key_map_[sf::Keyboard::Z]			= CEGUI::Key::Z;
	key_map_[sf::Keyboard::Num0]		= CEGUI::Key::Zero;
	key_map_[sf::Keyboard::Num1]		= CEGUI::Key::One;
	key_map_[sf::Keyboard::Num2]		= CEGUI::Key::Two;
	key_map_[sf::Keyboard::Num3]		= CEGUI::Key::Three;
	key_map_[sf::Keyboard::Num4]		= CEGUI::Key::Four;
	key_map_[sf::Keyboard::Num5]		= CEGUI::Key::Five;
	key_map_[sf::Keyboard::Num6]		= CEGUI::Key::Six;
	key_map_[sf::Keyboard::Num7]		= CEGUI::Key::Seven;
	key_map_[sf::Keyboard::Num8]		= CEGUI::Key::Eight;
	key_map_[sf::Keyboard::Num9]		= CEGUI::Key::Nine;
	key_map_[sf::Keyboard::Escape]		= CEGUI::Key::Escape;
	key_map_[sf::Keyboard::LControl]	= CEGUI::Key::LeftControl;
	key_map_[sf::Keyboard::LShift]		= CEGUI::Key::LeftShift;
	key_map_[sf::Keyboard::LAlt]		= CEGUI::Key::LeftAlt;
	key_map_[sf::Keyboard::LSystem]		= CEGUI::Key::LeftWindows;
	key_map_[sf::Keyboard::RControl]	= CEGUI::Key::RightControl;
	key_map_[sf::Keyboard::RShift]		= CEGUI::Key::RightShift;
	key_map_[sf::Keyboard::RAlt]		= CEGUI::Key::RightAlt;
	key_map_[sf::Keyboard::RSystem]		= CEGUI::Key::RightWindows;
	key_map_[sf::Keyboard::LBracket]	= CEGUI::Key::LeftBracket;
	key_map_[sf::Keyboard::RBracket]	= CEGUI::Key::RightBracket;
	key_map_[sf::Keyboard::SemiColon]	= CEGUI::Key::Semicolon;
	key_map_[sf::Keyboard::Comma]		= CEGUI::Key::Comma;
	key_map_[sf::Keyboard::Period]		= CEGUI::Key::Period;
	key_map_[sf::Keyboard::Quote]		= CEGUI::Key::Apostrophe;
	key_map_[sf::Keyboard::Slash]		= CEGUI::Key::Slash;
	key_map_[sf::Keyboard::BackSlash]	= CEGUI::Key::Backslash;
	key_map_[sf::Keyboard::Tilde]		= CEGUI::Key::Grave;
	key_map_[sf::Keyboard::Equal]		= CEGUI::Key::Equals;
	key_map_[sf::Keyboard::Dash]		= CEGUI::Key::Minus;
	key_map_[sf::Keyboard::Space]		= CEGUI::Key::Space;
	key_map_[sf::Keyboard::Return]		= CEGUI::Key::Return;
	key_map_[sf::Keyboard::BackSpace]	= CEGUI::Key::Backspace;
	key_map_[sf::Keyboard::Tab]			= CEGUI::Key::Tab;
	key_map_[sf::Keyboard::PageUp]		= CEGUI::Key::PageUp;
	key_map_[sf::Keyboard::PageDown]	= CEGUI::Key::PageDown;
	key_map_[sf::Keyboard::End]			= CEGUI::Key::End;
	key_map_[sf::Keyboard::Home]		= CEGUI::Key::Home;
	key_map_[sf::Keyboard::Insert]		= CEGUI::Key::Insert;
	key_map_[sf::Keyboard::Delete]		= CEGUI::Key::Delete;
	key_map_[sf::Keyboard::Add]			= CEGUI::Key::Add;
	key_map_[sf::Keyboard::Subtract]	= CEGUI::Key::Subtract;
	key_map_[sf::Keyboard::Multiply]	= CEGUI::Key::Multiply;
	key_map_[sf::Keyboard::Divide]		= CEGUI::Key::Divide;
	key_map_[sf::Keyboard::Left]		= CEGUI::Key::ArrowLeft;
	key_map_[sf::Keyboard::Right]		= CEGUI::Key::ArrowRight;
	key_map_[sf::Keyboard::Up]			= CEGUI::Key::ArrowUp;
	key_map_[sf::Keyboard::Down]		= CEGUI::Key::ArrowDown;
	key_map_[sf::Keyboard::Numpad0] 	= CEGUI::Key::Numpad0;
	key_map_[sf::Keyboard::Numpad1] 	= CEGUI::Key::Numpad1;
	key_map_[sf::Keyboard::Numpad2] 	= CEGUI::Key::Numpad2;
	key_map_[sf::Keyboard::Numpad3] 	= CEGUI::Key::Numpad3;
	key_map_[sf::Keyboard::Numpad4] 	= CEGUI::Key::Numpad4;
	key_map_[sf::Keyboard::Numpad5] 	= CEGUI::Key::Numpad5;
	key_map_[sf::Keyboard::Numpad6] 	= CEGUI::Key::Numpad6;
	key_map_[sf::Keyboard::Numpad7] 	= CEGUI::Key::Numpad7;
	key_map_[sf::Keyboard::Numpad8] 	= CEGUI::Key::Numpad8;
	key_map_[sf::Keyboard::Numpad9] 	= CEGUI::Key::Numpad9;
	key_map_[sf::Keyboard::F1]			= CEGUI::Key::F1;
	key_map_[sf::Keyboard::F2]			= CEGUI::Key::F2;
	key_map_[sf::Keyboard::F3]			= CEGUI::Key::F3;
	key_map_[sf::Keyboard::F4]			= CEGUI::Key::F4;
	key_map_[sf::Keyboard::F5]			= CEGUI::Key::F5;
	key_map_[sf::Keyboard::F6]			= CEGUI::Key::F6;
	key_map_[sf::Keyboard::F7]			= CEGUI::Key::F7;
	key_map_[sf::Keyboard::F8]			= CEGUI::Key::F8;
	key_map_[sf::Keyboard::F9]			= CEGUI::Key::F9;
	key_map_[sf::Keyboard::F10]			= CEGUI::Key::F10;
	key_map_[sf::Keyboard::F11]			= CEGUI::Key::F11;
	key_map_[sf::Keyboard::F12]			= CEGUI::Key::F12;
	key_map_[sf::Keyboard::F13]			= CEGUI::Key::F13;
	key_map_[sf::Keyboard::F14]			= CEGUI::Key::F14;
	key_map_[sf::Keyboard::F15]			= CEGUI::Key::F15;
	key_map_[sf::Keyboard::Pause]		= CEGUI::Key::Pause;
 
	mouse_map_[sf::Mouse::Left]		= CEGUI::LeftButton;
	mouse_map_[sf::Mouse::Right]		= CEGUI::RightButton;
	mouse_map_[sf::Mouse::Middle]		= CEGUI::MiddleButton;
	mouse_map_[sf::Mouse::XButton1]	= CEGUI::X1Button;
	mouse_map_[sf::Mouse::XButton2]	= CEGUI::X2Button;
}

CEGUI::Key::Scan GameDesktop::toCEGUIKey(sf::Keyboard::Key code)
{
  return key_map_[code];
}

CEGUI::MouseButton GameDesktop::toCEGUIMouseButton(sf::Mouse::Button button)
{
  return mouse_map_[button];
}
