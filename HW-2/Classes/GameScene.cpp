#include "GameScene.h"
#include "SimpleAudioEngine.h"

Game * GLOBAL_GAME_SCENE = nullptr;

cocos2d::Scene* Game::createScene()
{
    // Создание сцены со слоем
    cocos2d::Scene * scene = cocos2d::Scene::create();
    
    Game * layer = Game::create();
    scene->addChild(layer);

    return scene;
}

Game * Game::create()
{
    Game *pRet = new(std::nothrow) Game();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. Super init first

    if (!Layer::init())
    {
        return false;
    }

    // Set background
    cocos2d::CCSprite * background = cocos2d::CCSprite::create("background.png");
    background->setAnchorPoint(cocos2d::Vec2(0, 0));
    addChild(background, -1);

    leftMoneyLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 60, cocos2d::Size(510, 60));
    leftMoneyLabel_->setPosition(10, getContentSize().height - MARGIN_SIZE);
    leftMoneyLabel_->setAnchorPoint(cocos2d::Vec2(0, 1));
    addChild(leftMoneyLabel_, 0);

    rightMoneyLabel_ = cocos2d::CCLabelTTF::create("", "Helvetica", 60, cocos2d::Size(510, 60));
    rightMoneyLabel_->setPosition(getContentSize().width - 10, getContentSize().height - MARGIN_SIZE);
    rightMoneyLabel_->setAnchorPoint(cocos2d::Vec2(1, 1));
    addChild(rightMoneyLabel_, 0);

    //////////////////////////////
    // 2. Objects

    for (float i = 0; i < 24; ++i) {
        blocks_.push_back(std::shared_ptr<BlockObject>(new BasicBlockObject(80 * i, 0)));
        blocks_.push_back(std::shared_ptr<BlockObject>(new GrassBlockObject(80 * i, 80)));
        addChild(blocks_[2*i]->GetSprite(), 0);
        addChild(blocks_[2*i+1]->GetSprite(), 10);
    }

    InitLeftCastle_();    
    SetLeftMoney(50);

    InitRightCastle_();
    SetRightMoney(50);

    //////////////////////////////
    // 3. Listeners 

    GLOBAL_GAME_SCENE = this;

    cocos2d::EventListenerKeyboard * listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = OnKeyPressed;
    listener->onKeyReleased = OnKeyReleased;

    this->scheduleUpdate();
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void Game::update(float)
{
    if (leftCastle_->GetHealth() == 0) {
        cocos2d::CCLabelTTF * victoryLabel_ = cocos2d::CCLabelTTF::create("RIGHT PLAYER WINS!", "Helvetica", 100, cocos2d::Size(1920, 1080),
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
        victoryLabel_->setAnchorPoint(cocos2d::Vec2(0, 0));
        victoryLabel_->setColor(cocos2d::Color3B(60, 60, 60));
        addChild(victoryLabel_);
        return;
    }
    else if (rightCastle_->GetHealth() == 0) {
        cocos2d::CCLabelTTF * victoryLabel_ = cocos2d::CCLabelTTF::create("LEFT PLAYER WINS!", "Helvetica", 100, cocos2d::Size(1920, 1080),
            cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
        victoryLabel_->setAnchorPoint(cocos2d::Vec2(0, 0));
        victoryLabel_->setColor(cocos2d::Color3B(60, 60, 60));
        addChild(victoryLabel_);
        return;
    }

    for (auto& block : GLOBAL_GAME_SCENE->blocks_) {
        block->Update(this);
    }

    if (GLOBAL_GAME_SCENE->leftCastle_) {
        GLOBAL_GAME_SCENE->leftCastle_->Update(this);
    }
    if (GLOBAL_GAME_SCENE->rightCastle_) {
        GLOBAL_GAME_SCENE->rightCastle_->Update(this);
    }

    for (int i = 0; i < leftAttackers_.size(); ++i) {
        leftAttackers_[i]->Update(this);
    }
    for (int i = 0; i < rightAttackers_.size(); ++i) {
        rightAttackers_[i]->Update(this);
    }
    for (int i = 0; i < leftAttackers_.size(); ++i) {
        leftAttackers_[i]->Attack(this);
    }
    for (int i = 0; i < rightAttackers_.size(); ++i) {
        rightAttackers_[i]->Attack(this);
    }
    killAttackers_(GLOBAL_GAME_SCENE->leftAttackers_);
    killAttackers_(GLOBAL_GAME_SCENE->rightAttackers_);
}

void Game::SetLeftMoney(size_t money)
{
    leftMoney_ = money;
    
    char buf[15];
    _itoa_s(int(money), buf, 10);
    size_t intSize = 0;
    while (buf[intSize] != '\0') {
        ++intSize;
    }

    std::string labelStr(buf, intSize);
    labelStr += " coins";
    leftMoneyLabel_->setString(labelStr);
}

void Game::SetRightMoney(size_t money)
{
    rightMoney_ = money;

    char buf[15];
    _itoa_s(int(money), buf, 10);
    size_t intSize = 0;
    while (buf[intSize] != '\0') {
        ++intSize;
    }

    std::string labelStr(buf, intSize);
    labelStr += " coins";
    rightMoneyLabel_->setString(labelStr);
}

std::shared_ptr<CastleObject>& Game::InitLeftCastle_(CastleType id)
{
    if (leftCastle_.get() != nullptr) {
        removeChild(leftCastle_->GetSprite());
        removeChild(leftCastle_->GetHealthLabel());
        removeChild(leftCastle_->GetArmorLabel());
    }
    CastleObject * t;
    switch (id)
    {
    case Game::SimpleCastle:
        t = new SimpleCastleObject;
        break;
    case Game::StrongCastle:
        t = new StrongCastleObject;
        break;
    }
    leftCastle_ = std::shared_ptr<CastleObject>(t);
    addChild(leftCastle_->GetSprite(), 3);
    addChild(leftCastle_->GetHealthLabel(), 4);
    addChild(leftCastle_->GetArmorLabel(), 4);
    return leftCastle_;
}

std::shared_ptr<CastleObject>& Game::InitRightCastle_(CastleType id)
{

    if (rightCastle_.get() != nullptr) {
        removeChild(rightCastle_->GetSprite());
        removeChild(rightCastle_->GetHealthLabel());
        removeChild(rightCastle_->GetArmorLabel());
    }
    CastleObject * t;
    switch (id)
    {
    case Game::SimpleCastle:
        t = new SimpleCastleObject;
        break;
    case Game::StrongCastle:
        t = new StrongCastleObject;
        break;
    }
    rightCastle_ = std::shared_ptr<CastleObject>(t);
    rightCastle_->SetRightAlignment(getContentSize().width);
    addChild(rightCastle_->GetSprite(), 3);
    addChild(rightCastle_->GetHealthLabel(), 4);
    addChild(rightCastle_->GetArmorLabel(), 4);
    return rightCastle_;
}

std::shared_ptr<AttackerObject>& Game::AddLeftAttacker_(AttackerType id)
{
    AttackerObject * t;
    switch (id)
    {
    case Game::SimpleAttacker:
        t = new SimpleAttackerObject;
        break;
    case Game::FirstAttacker:
        t = new FirstAttackerObject;
        break;
    case Game::SecondAttacker:
        t = new SecondAttackerObject;
        break;
    case Game::ThirdAttacker:
        t = new ThirdAttackerObject;
        break;
    default:
        break;
    }
    leftAttackers_.push_back(std::shared_ptr<AttackerObject>(t));
    addChild(leftAttackers_.back()->GetSprite(), 1);
    addChild(leftAttackers_.back()->GetLabel(), 2);
    return leftAttackers_.back();
}

std::shared_ptr<AttackerObject>& Game::AddRightAttacker_(AttackerType id)
{
    AttackerObject * t;
    switch (id)
    {
    case Game::SimpleAttacker:
        t = new SimpleAttackerObject;
        break;
    case Game::FirstAttacker:
        t = new FirstAttackerObject;
        break;
    case Game::SecondAttacker:
        t = new SecondAttackerObject;
        break;
    case Game::ThirdAttacker:
        t = new ThirdAttackerObject;
        break;
    default:
        break;
    }
    rightAttackers_.push_back(std::shared_ptr<AttackerObject>(t));
    rightAttackers_.back()->SetRightAlignment(getContentSize().width);
    addChild(rightAttackers_.back()->GetSprite(), 1);
    addChild(rightAttackers_.back()->GetLabel(), 2);
    return rightAttackers_.back();
}

void Game::killAttackers_(std::vector<std::shared_ptr<AttackerObject>>& attackers)
{
    for (int i = 0; i < attackers.size(); ++i) {
        if (attackers[i]->GetHealth() == 0) {
            if (attackers == leftAttackers_) {
                SetRightMoney(rightMoney_ + attackers[i]->GetCost() * 2);
            }
            else {
                SetLeftMoney(leftMoney_ + attackers[i]->GetCost() * 2);
            }
            removeChild(attackers[i]->GetSprite());
            removeChild(attackers[i]->GetLabel());
            attackers.erase(attackers.begin() + i);
            --i;
        }
    }
}

void OnKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
    if (GLOBAL_GAME_SCENE == nullptr) {
        return;
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_Q) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= AttackAndDefend::SimpleAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - AttackAndDefend::SimpleAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::SimpleAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_W) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= AttackAndDefend::FirstAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - AttackAndDefend::FirstAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::FirstAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_E) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= AttackAndDefend::SecondAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - AttackAndDefend::SecondAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::SecondAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_R) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= AttackAndDefend::ThirdAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - AttackAndDefend::ThirdAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::ThirdAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= AttackAndDefend::StrongCastleObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - AttackAndDefend::StrongCastleObject::GetClassCost());
            GLOBAL_GAME_SCENE->InitLeftCastle_(Game::CastleType::StrongCastle);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_S) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= 100 &&
            GLOBAL_GAME_SCENE->leftCastle_->GetHealth() < GLOBAL_GAME_SCENE->leftCastle_->GetMaxHealth()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - 100);
            GLOBAL_GAME_SCENE->leftCastle_->SetHealth(GLOBAL_GAME_SCENE->leftCastle_->GetHealth() + 100);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        if (GLOBAL_GAME_SCENE->leftMoney_ >= 100 &&
            GLOBAL_GAME_SCENE->leftCastle_->GetArmor() < GLOBAL_GAME_SCENE->leftCastle_->GetMaxArmor()) {
            GLOBAL_GAME_SCENE->SetLeftMoney(GLOBAL_GAME_SCENE->leftMoney_ - 100);
            GLOBAL_GAME_SCENE->leftCastle_->SetArmor(GLOBAL_GAME_SCENE->leftCastle_->GetArmor() + 100);
        }
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_U) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= AttackAndDefend::SimpleAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - AttackAndDefend::SimpleAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::SimpleAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_I) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= AttackAndDefend::FirstAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - AttackAndDefend::FirstAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::FirstAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_O) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= AttackAndDefend::SecondAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - AttackAndDefend::SecondAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::SecondAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= AttackAndDefend::ThirdAttackerObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - AttackAndDefend::ThirdAttackerObject::GetClassCost());
            GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::ThirdAttacker);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_J) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= AttackAndDefend::StrongCastleObject::GetClassCost()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - AttackAndDefend::StrongCastleObject::GetClassCost());
            GLOBAL_GAME_SCENE->InitRightCastle_(Game::CastleType::StrongCastle);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_K) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= 100 &&
            GLOBAL_GAME_SCENE->rightCastle_->GetHealth() < GLOBAL_GAME_SCENE->rightCastle_->GetMaxHealth()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - 100);
            GLOBAL_GAME_SCENE->rightCastle_->SetHealth(GLOBAL_GAME_SCENE->rightCastle_->GetHealth() + 100);
        }
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_L) {
        if (GLOBAL_GAME_SCENE->rightMoney_ >= 100 &&
            GLOBAL_GAME_SCENE->rightCastle_->GetArmor() < GLOBAL_GAME_SCENE->rightCastle_->GetMaxArmor()) {
            GLOBAL_GAME_SCENE->SetRightMoney(GLOBAL_GAME_SCENE->rightMoney_ - 100);
            GLOBAL_GAME_SCENE->rightCastle_->SetArmor(GLOBAL_GAME_SCENE->rightCastle_->GetArmor() + 100);
        }
    }
}

void OnKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
    if (GLOBAL_GAME_SCENE == nullptr) {
        return;
    }
}