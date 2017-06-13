#include "ButtonObject.h"
#include "GameScene.h"

aad::ButtonObject::ButtonObject()
    : StaticObject()
    , isLocked_(false)
    , faceSprite_(nullptr)
    , lockSprite_(nullptr)
{}

aad::ButtonObject::ButtonObject(float x, float y, std::string fileName, std::string topLabel, std::string bottomLabel, bool isLocked)
    : StaticObject(x, y, BUTTON_BACKGROUND_FILE)
    , isLocked_(false)
{
    faceSprite_ = cocos2d::Sprite::create(fileName);
    faceSprite_->setScale(
        std::min((GetW() - BUTTON_PADDING * 2) / faceSprite_->getContentSize().width, 
        (GetH() - BUTTON_PADDING * 2) / faceSprite_->getContentSize().height)
    );
    faceSprite_->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    faceSprite_->setPosition(cocos2d::Vec2(GetW() / 2, GetH() / 2));
    faceSprite_->setOpacity(60);
    GetSprite()->addChild(faceSprite_, 1);

    lockSprite_ = cocos2d::Sprite::create(LOCK_BUTTON_FILE);
    lockSprite_->setScale(
        std::min(GetW() / lockSprite_->getContentSize().width,
        GetH() / lockSprite_->getContentSize().height)
    );
    lockSprite_->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    lockSprite_->setPosition(cocos2d::Vec2(GetW() / 2, GetH() / 2));
    lockSprite_->setVisible(false);
    GetSprite()->addChild(lockSprite_, 3);

    if (!topLabel.empty()) {
        topLabel_ = cocos2d::CCLabelTTF::create(topLabel, "Arial Rounded MT Bold", BUTTON_FONT_SIZE, cocos2d::Size(GetW(), BUTTON_FONT_SIZE));
        topLabel_->setColor(cocos2d::Color3B(0, 0, 0));
        topLabel_->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        topLabel_->setPosition(GetW() / 2, 3 * GetH() / 4);
        GetSprite()->addChild(topLabel_, 2);
    }

    if (!bottomLabel.empty()) {
        bottomLabel_ = cocos2d::CCLabelTTF::create(bottomLabel, "Arial Rounded MT Bold", BUTTON_FONT_SIZE, cocos2d::Size(GetW(), BUTTON_FONT_SIZE));
        bottomLabel_->setColor(cocos2d::Color3B(0, 0, 0));
        bottomLabel_->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        bottomLabel_->setPosition(GetW() / 2, GetH() / 4);
        GetSprite()->addChild(bottomLabel_, 2);
    }

    if (isLocked) {
        Lock();
    }
}

aad::ButtonObject::ButtonObject(float x, float y, ButtonType type, std::string key, bool isLocked)
    : ButtonObject(x, y, ButtonObject::GetClassFile_(type), key, std::to_string(ButtonObject::GetClassCost_(type)), isLocked)
{}

aad::ButtonObject::ButtonObject(float x, float y, AttackerType type, std::string key, bool isLocked)
    : ButtonObject(x, y, AttackerObject::GetClassFile(type), key, std::to_string(AttackerObject::GetClassCost(type)), isLocked)
{}

aad::ButtonObject::ButtonObject(float x, float y, CastleType type, std::string key, bool isLocked)
    : ButtonObject(x, y, CastleObject::GetClassFile(type), key, std::to_string(CastleObject::GetClassCost(type)), isLocked)
{}

void aad::ButtonObject::Lock()
{
    if (!isLocked_ || lockSprite_ != nullptr) {
        lockSprite_->setVisible(true);
    }
}

void aad::ButtonObject::Unlock()
{
    if (isLocked_ || lockSprite_ != nullptr) {
        lockSprite_->setVisible(false);
    }
}

std::string aad::ButtonObject::GetTopLabel() const
{
    return topLabel_->getString();
}

std::string aad::ButtonObject::GetBottomLabel() const
{
    return bottomLabel_->getString();
}

void aad::ButtonObject::OnRightAlignmentUpdate_()
{
    StaticObject::OnRightAlignmentUpdate_();

    if (faceSprite_ != nullptr) {
        faceSprite_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
    }
    if (lockSprite_ != nullptr) {
        lockSprite_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
    }
    if (topLabel_ != nullptr) {
        topLabel_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
    }
    if (bottomLabel_ != nullptr) {
        bottomLabel_->setRotation3D(cocos2d::Vec3(0, (IsRightAlignment() ? 180 : 0), 0));
    }
}

size_t aad::ButtonObject::GetClassCost_(ButtonType type)
{
    switch (type)
    {
    case aad::HealthButton:
        return HEALTH_BUTTON_COST;
    case aad::ArmorButton:
        return ARMOR_BUTTON_COST;
    default:
        return UNKNOWN_BUTTON_COST;
    }
}

std::string aad::ButtonObject::GetClassFile_(ButtonType type)
{
    switch (type)
    {
    case aad::HealthButton:
        return HEALTH_BUTTON_FILE;
    case aad::ArmorButton:
        return ARMOR_BUTTON_FILE;
    default:
        return UNKNOWN_BUTTON_FILE;
    }
}
