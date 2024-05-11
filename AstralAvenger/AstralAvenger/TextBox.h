#pragma once
#include "raylib.h"

constexpr unsigned MAX_TEXT_SIZE = 128;
constexpr unsigned DEFAULT_OFFSET = 10;
constexpr float DEFAULT_SPACING = 2.f;
constexpr Rectangle DEFAULT_REC = {0, 0, 200, 100};
constexpr Color DEFAULT_COLOR = BLACK;

class TextBox
{
  public:
    TextBox() = default;
    TextBox(const char *text, const Rectangle &rectangle, const Font &font, const Color &color);
    void setRectangle(const Rectangle &rec);
    void setFont(const Font &font);
    void setText(const char *text);
    void setColor(const Color &color);

    const Rectangle &getRec() const;

    void draw() const;
    void drawWithRec(const Color &backgroundColor) const;

  private:
    void centerText();

    char text[MAX_TEXT_SIZE] = "";
    Rectangle rectangle = DEFAULT_REC;
    Font font = GetFontDefault();
    unsigned fontSize = 0;
    Color color = DEFAULT_COLOR;
    float offsetX = 0.f;
    float offsetY = 0.f;
};
