#pragma once
#include "PictureBox.h"
#include "TextBox.h"
#include "raylib.h"

constexpr Color BORDER_COLOR = BLACK;
constexpr float BORDER_THICKNESS = 2.f;

enum class ButtonState
{
    DEFAULT,
    HOVER,
    CLICKED
};

class UIButton : public PictureBox
{
public:
    UIButton() = default;
    UIButton(const TextBox& text, const Texture2D& texture);
    UIButton(const Rectangle& rectangle, const Texture2D& texture, const char* text);
    UIButton(const Rectangle& rectangle, const char* fileName, const char* text);

    void setFont(Font& font);

    bool isClicked() const;

    void play();

private:
    void input();
    void draw() const;

    ButtonState state = ButtonState::DEFAULT;
    TextBox text;
};
