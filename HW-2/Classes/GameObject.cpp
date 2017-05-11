#include "GameObject.h"
#include "GameScene.h"

using namespace AttackAndDefend;

GameObject::GameObject()
    : sprite_(nullptr)
    , x_(0.f)
    , y_(0.f)
    , w_(0.f)
    , h_(0.f)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{}

GameObject::GameObject(float x, float y, cocos2d::Sprite* sprite)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    // Set sprite_, w_, h_
    SetSprite(sprite);
}

GameObject::GameObject(float x, float y, std::string const& fileName)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    // Set sprite_, w_, h_
    SetSprite(cocos2d::Sprite::create(fileName));
}

void GameObject::Update(Game* const scene)
{}

cocos2d::Sprite * GameObject::GetSprite()
{
    return sprite_;
}

float GameObject::GetX()
{
    return x_;
}

float GameObject::GetY()
{
    return y_;
}

float GameObject::GetW()
{
    return w_;
}

float GameObject::GetH()
{
    return h_;
}

bool GameObject::IsRightAlignment()
{
    return isRightAlignment_;
}

void GameObject::SetSprite(cocos2d::Sprite * pointer)
{
    sprite_ = pointer;
    if (sprite_) {
        SetW_(sprite_->getContentSize().width);
        SetH_(sprite_->getContentSize().height);
    }
    else {
        SetW_(0.f);
        SetH_(0.f);
    }
    onPositionUpdate_();
}

void GameObject::SetX(float x)
{
    x_ = x;
    onPositionUpdate_();
}

void GameObject::SetY(float y)
{
    y_ = y;
    onPositionUpdate_();
}

void GameObject::SetLeftAlignment()
{
    if (isRightAlignment_) {
        isRightAlignment_ = false;
        onPositionUpdate_();
    }
}

void GameObject::SetRightAlignment(float frameWidth)
{
    if (!isRightAlignment_) {
        isRightAlignment_ = true;
        frameWidth_ = frameWidth;
        onPositionUpdate_();
    }
}

void AttackAndDefend::GameObject::onPositionUpdate_()
{
    if (sprite_) {
        if (isRightAlignment_ != prevIsRightAlignment_) {
            sprite_->setAnchorPoint(cocos2d::Vec2((IsRightAlignment() ? 1 : 0), 0));
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

void GameObject::SetSpriteX_(float x)
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

void GameObject::SetSpriteY_(float y)
{
    if (sprite_) {
        sprite_->setPositionY(y);
    }
}

void GameObject::SetW_(float w)
{
    w_ = w;
    onPositionUpdate_();
}

void GameObject::SetH_(float h)
{
    h_ = h;
    onPositionUpdate_();
}