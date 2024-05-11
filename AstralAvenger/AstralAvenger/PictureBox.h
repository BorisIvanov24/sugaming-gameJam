#pragma once
#include "TextBox.h"
#include "raylib.h"

class PictureBox
{
  public:
    PictureBox() = default;
    PictureBox(const Texture2D &texture, const Rectangle &rectangle);
    PictureBox(const char *fileName, const Rectangle &rectangle);

    void loadTexture(const char *fileName);
    void setTexture(const Texture2D &texture);
    void setRectangle(const Rectangle &rectangle);

    const Rectangle &getRectangle() const;
    const Texture2D &getTexture2D() const;

    void draw(const Color &tint) const;
    void draw(const Vector2 &position, const Color &tint) const;

  private:
    void resizeTexture();

    Texture2D texture = {0};
    Rectangle rectangle = DEFAULT_REC;
    Vector2 position = {0};
};
