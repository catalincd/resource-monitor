#include <ftxui/screen/screen.hpp>
#include <iostream>
 
int main(void) {
  using namespace ftxui;
  auto screen = Screen::Create(Dimension::Fixed(32), Dimension::Fixed(10));
 
  auto& pixel = screen.PixelAt(9,9);
  pixel.character = U'A';
  pixel.bold = true;
  pixel.foreground_color = Color::Blue;
 
  std::cout << screen.ToString();
  return EXIT_SUCCESS;
}
