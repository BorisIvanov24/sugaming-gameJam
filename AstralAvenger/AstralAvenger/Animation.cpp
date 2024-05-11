#include "Animation.h"
#include <iostream>
#include <sstream>

Animation::Animation(const Texture2D* textures, unsigned size, const Rectangle& rec) : Animation()
{
    PictureBox pb;

    for (unsigned i = 0; i < size; i++)
    {
        pb.setTexture(textures[i]);
        pb.setRectangle(rec);
        this->textures.push_back(pb);
    }
}

unsigned Animation::getTexturesCount() const
{
    return textures.size();
}

void Animation::loadFromFolder(const char* path, uint8_t numberOfTextures)
{
    PictureBox pb;
    pb.setRectangle(rec);

    textures.clear();
    for (int i = 0; i < numberOfTextures; i++)
    {
        std::stringstream ss("");
        ss << path << i << ".png";

        std::string fileName = ss.str();

        pb.setTexture(LoadTexture(fileName.c_str()));
        textures.push_back(pb);
    }
}

void Animation::play(const Vector2& posToPlay) const
{
    textures[currentTexture].draw(posToPlay, RAYWHITE);

    if (frames % CHANGE_FRAME_AFTER == 0)
    {
        if (currentTexture == (getTexturesCount() - 1))
            currentTexture = 0;
        else
            currentTexture++;
    }

    frames++;
}

bool Animation::playRun(const Vector2& posToPlay) const
{
    textures[currentTexture].draw(posToPlay, RAYWHITE);

    if (frames % CHANGE_FRAME_AFTER == 0)
    {
        if (currentTexture == (getTexturesCount() - 1))
        {
            currentTexture = 0;
            return false;
        }
        else
            currentTexture++;
    }

    frames++;
    return true;
}

void Animation::addTexture(const Texture2D& texture)
{
    PictureBox pb(texture, rec);
    textures.push_back(pb);
}

void Animation::removeLastTexture(uint8_t index)
{
    textures.pop_back();
}

void Animation::setRectangle(const Rectangle& rec)
{
    this->rec = rec;
    for (int i = 0; i < textures.size(); i++)
    {
        textures[i].setRectangle(rec);
    }
}
