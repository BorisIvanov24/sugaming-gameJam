#include "UIButton.h"

UIButton::UIButton(const TextBox& text, const Texture2D& texture) : PictureBox(texture, text.getRec())
{
    this->text = text;
}

UIButton::UIButton(const Rectangle& rectangle, const Texture2D& texture, const char* text)
    : PictureBox(texture, rectangle)
{
    this->text.setRectangle(rectangle);
    this->text.setText(text);
}

UIButton::UIButton(const Rectangle& rectangle, const char* fileName, const char* text) : PictureBox(fileName, rectangle)
{
    this->text.setRectangle(rectangle);
    this->text.setText(text);
}

void UIButton::setFont(Font& font)
{
    text.setFont(font);
}

void UIButton::input()
{
    Vector2 mousePos = GetMousePosition();
    bool collide = CheckCollisionPointRec(mousePos, PictureBox::getRectangle());

    if (collide && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state = ButtonState::CLICKED;
    }
    else if (collide)
    {
        state = ButtonState::HOVER;
    }
    else
    {
        state = ButtonState::DEFAULT;
    }
}

bool UIButton::isClicked() const
{
    return (state == ButtonState::CLICKED);
}

void UIButton::draw() const
{
    switch (state)
    {
    case ButtonState::CLICKED:
    case ButtonState::HOVER:
        PictureBox::draw(LIGHTGRAY);
        DrawRectangleLinesEx(PictureBox::getRectangle(), BORDER_THICKNESS, BORDER_COLOR);
        text.draw();
        break;
    default:
        PictureBox::draw(WHITE);
        DrawRectangleLinesEx(PictureBox::getRectangle(), BORDER_THICKNESS, BORDER_COLOR);
        text.draw();
        break;
    }
}

void UIButton::play()
{
    input();
    draw();
}
