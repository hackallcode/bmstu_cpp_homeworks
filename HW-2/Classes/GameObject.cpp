#include "GameObject.h"
#include "GameScene.h"

aad::GameObject::GameObject()
    : x_(0.f)
    , y_(0.f)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    SetSprite(nullptr); // Set sprite_, w_, h_
}

aad::GameObject::GameObject(float x, float y, cocos2d::Sprite* sprite)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    SetSprite(sprite); // Set sprite_, w_, h_
}

aad::GameObject::GameObject(float x, float y, std::string const& fileName)
    : x_(x)
    , y_(y)
    , frameWidth_(0.f)
    , isRightAlignment_(false)
{
    SetSprite(cocos2d::Sprite::create(fileName)); // Set sprite_, w_, h_
}

void aad::GameObject::Update(Game * const scene)
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

void aad::GameObject::SetSprite(cocos2d::Sprite * sprite)
{
    sprite_ = sprite;
    if (sprite_ != nullptr) {
        sprite_->setAnchorPoint(cocos2d::Vec2(0, 0));
        SetW_(sprite_->getContentSize().width);
        SetH_(sprite_->getContentSize().height);
    }
    else {
        SetW_(0.f);
        SetH_(0.f);
    }
    PositionInit_();
}

void aad::GameObject::SetLeftAlignment()
{
    if (isRightAlignment_) {
        isRightAlignment_ = false;
        OnRightAlignmentUpdate_();
    }    
}

void aad::GameObject::SetRightAlignment(float frameWidth)
{
    if (!isRightAlignment_ || frameWidth != frameWidth_) {
        frameWidth_ = frameWidth;
        isRightAlignment_ = true;
        OnRightAlignmentUpdate_();
    }
}

void aad::GameObject::SetX_(float x)
{
    x_ = x;
}

void aad::GameObject::SetY_(float y)
{
    y_ = y;
}

void aad::GameObject::SetW_(float w)
{
    w_ = w;
}

void aad::GameObject::SetH_(float h)
{
    h_ = h;
}

void aad::GameObject::PositionInit_()
{
    OnXUpdate_();
    OnYUpdate_();
    OnWUpdate_();
    OnHUpdate_();
    OnRightAlignmentUpdate_();
}

void aad::GameObject::OnPositionUpdate_()
{
    if (x_ != prevX_) OnXUpdate_();
    if (y_ != prevY_) OnYUpdate_();
    if (w_ != prevW_) OnWUpdate_();
    if (h_ != prevH_) OnHUpdate_();
}

void aad::GameObject::OnXUpdate_()
{
    SetSpriteX_(x_);
    prevX_ = x_;
}

void aad::GameObject::OnYUpdate_()
{
    SetSpriteY_(y_);
    prevY_ = y_;
}

void aad::GameObject::OnWUpdate_()
{
    prevW_ = w_;
}

void aad::GameObject::OnHUpdate_()
{
    prevH_ = h_;
}

void aad::GameObject::OnRightAlignmentUpdate_()
{
    OnXUpdate_();
    if (sprite_ != nullptr) {
        sprite_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
    }    
}

void aad::GameObject::SetSpriteX_(float x)
{
    if (sprite_ != nullptr) {
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
    if (sprite_ != nullptr) {
        sprite_->setPositionY(y);
    }
}