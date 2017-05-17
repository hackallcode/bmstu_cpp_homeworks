#include "GameObject.h"
#include "GameScene.h"

aad::GameObject::GameObject()
    : sprite_(nullptr)
    , x_(0.f)
    , y_(0.f)
    , w_(0.f)
    , h_(0.f)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{}

aad::GameObject::GameObject(float x, float y, cocos2d::Sprite* sprite)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    // Set sprite_, w_, h_
    SetSprite(sprite);
}

aad::GameObject::GameObject(float x, float y, std::string const& fileName)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    // Set sprite_, w_, h_
    SetSprite(cocos2d::Sprite::create(fileName));
}

void aad::GameObject::Update(Game * const scene)
{}

void aad::GameObject::Damage(float power)
{}

cocos2d::Sprite * aad::GameObject::GetSprite() const
{
    return sprite_;
}

float aad::GameObject::GetX() const
{
    return x_;
}

float aad::GameObject::GetY() const
{
    return y_;
}

float aad::GameObject::GetW() const
{
    return w_;
}

float aad::GameObject::GetH() const
{
    return h_;
}

bool aad::GameObject::IsRightAlignment() const
{
    return isRightAlignment_;
}

void aad::GameObject::SetSprite(cocos2d::Sprite * pointer)
{
    sprite_ = pointer;
    if (sprite_) {
        sprite_->setAnchorPoint(cocos2d::Vec2(0, 0));
        SetW_(sprite_->getContentSize().width);
        SetH_(sprite_->getContentSize().height);
    }
    else {
        SetW_(0.f);
        SetH_(0.f);
    }
    onPositionUpdate_();
}

void aad::GameObject::SetX(float x)
{
    x_ = x;
    onPositionUpdate_();
}

void aad::GameObject::SetY(float y)
{
    y_ = y;
    onPositionUpdate_();
}

void aad::GameObject::SetLeftAlignment()
{
    if (isRightAlignment_) {
        isRightAlignment_ = false;
        onPositionUpdate_();
    }
}

void aad::GameObject::SetRightAlignment(float frameWidth)
{
    if (!isRightAlignment_) {
        isRightAlignment_ = true;
        frameWidth_ = frameWidth;
        onPositionUpdate_();
    }
}

void aad::GameObject::onPositionUpdate_()
{
    if (sprite_) {
        if (isRightAlignment_ != prevIsRightAlignment_) {
            sprite_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
            prevIsRightAlignment_ = isRightAlignment_;
        }
        if (x_ != prevX_ || w_ != prevW_ || frameWidth_ != prevFrameWidth_) {
            SetSpriteX_(GetX());
            prevX_ = x_;
            prevW_ = w_;
            prevFrameWidth_ = frameWidth_;
        }
        if (y_ != prevY_ || h_ != prevH_) {
            SetSpriteY_(GetY());
            prevY_ = y_;
            prevH_ = h_;
        }
    }
}

void aad::GameObject::SetSpriteX_(float x)
{
    if (sprite_) {
        if (isRightAlignment_) {
            sprite_->setPositionX(frameWidth_ - x_);
        }
        else {
            sprite_->setPositionX(x_);
        }
    }
}

void aad::GameObject::SetSpriteY_(float y)
{
    if (sprite_) {
        sprite_->setPositionY(y);
    }
}

void aad::GameObject::SetW_(float w)
{
    w_ = w;
    onPositionUpdate_();
}

void aad::GameObject::SetH_(float h)
{
    h_ = h;
    onPositionUpdate_();
}