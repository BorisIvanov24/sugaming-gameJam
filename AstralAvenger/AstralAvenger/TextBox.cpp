#include "TextBox.h"
#include <string>

#pragma warning(disable : 4996)

static size_t calculateFontSize(const Rectangle &rec, const char *text, const Font &font)
{
    Vector2 textSize = {0, 0};
    size_t fontSize = 2;
    size_t width = rec.width - (2 * (rec.width / DEFAULT_OFFSET));
    size_t height = rec.height - (2 * (rec.height / DEFAULT_OFFSET));

    do
    {
        fontSize++;
        textSize = MeasureTextEx(font, text, fontSize, DEFAULT_SPACING);

    } while ((textSize.x < width) && (textSize.y < height));

    return fontSize;
}

TextBox::TextBox(const char *text, const Rectangle &rectangle, const Font &font, const Color &color)
{
    this->rectangle = rectangle;
    this->font = font;
    this->color = color;

    strcpy(this->text, text);

    centerText();
}

void TextBox::setRectangle(const Rectangle &rectangle)
{
    this->rectangle = rectangle;
    centerText();
}

void TextBox::setFont(const Font &font)
{
    this->font = font;
    centerText();
}

void TextBox::setText(const char *text)
{
    strcpy(this->text, text);
    centerText();
}

void TextBox::setColor(const Color &color)
{
    this->color = color;
}

const Rectangle &TextBox::getRec() const
{
    return rectangle;
}

void TextBox::draw() const
{
    DrawTextEx(font, text, {rectangle.x + offsetX, rectangle.y + offsetY}, fontSize, DEFAULT_SPACING, color);
}

void TextBox::drawWithRec(const Color &backgroundColor) const
{
    DrawRectangleRec(rectangle, backgroundColor);
    draw();
}

void TextBox::centerText()
{
    fontSize = calculateFontSize(rectangle, text, font);
    Vector2 textSize = MeasureTextEx(font, text, fontSize, DEFAULT_SPACING);

    offsetX = (rectangle.width - textSize.x) / 2;
    offsetY = (rectangle.height - textSize.y) / 2;
}
