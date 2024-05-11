#include "PictureBox.h"

PictureBox::PictureBox(const Texture2D &texture, const Rectangle &rectangle)
{
    this->texture = texture;
    this->rectangle = rectangle;

    resizeTexture();
}

PictureBox::PictureBox(const char *fileName, const Rectangle &rectangle)
{
    texture = LoadTexture(fileName);
    this->rectangle = rectangle;
    resizeTexture();
}

void PictureBox::loadTexture(const char *fileName)
{
    texture = LoadTexture(fileName);
    resizeTexture();
}

void PictureBox::setTexture(const Texture2D &texture)
{
    this->texture = texture;
    resizeTexture();
}

void PictureBox::setRectangle(const Rectangle &rectangle)
{
    this->rectangle = rectangle;
    resizeTexture();
}

const Rectangle &PictureBox::getRectangle() const
{
    return rectangle;
}

const Texture2D &PictureBox::getTexture2D() const
{
    return texture;
}

void PictureBox::draw(const Color &tint) const
{
    DrawTexture(texture, rectangle.x, rectangle.y, tint);
}

void PictureBox::draw(const Vector2 &position, const Color &tint) const
{
    DrawTexture(texture, position.x, position.y, tint);
}

void PictureBox::resizeTexture()
{
    Image img = LoadImageFromTexture(texture);

    ImageResize(&img, rectangle.width, rectangle.height);

    texture = LoadTextureFromImage(img);
}
