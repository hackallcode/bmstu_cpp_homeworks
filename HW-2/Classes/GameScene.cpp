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

    //////////////////////////////
    // 2. Objects

    for (float i = 0; i < 10; ++i) {
        blocks_.push_back(std::shared_ptr<BlockObject>(new BasicBlockObject(192 * i, 0)));
        addChild(blocks_[i]->GetSprite(), 0);
    }

    InitLeftCastle_();
    InitRightCastle_();

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
    for (auto& block : GLOBAL_GAME_SCENE->blocks_) {
        block->Update(this);
    }

    if (GLOBAL_GAME_SCENE->leftCastle_) {
        GLOBAL_GAME_SCENE->leftCastle_->Update(this);
    }
    if (GLOBAL_GAME_SCENE->rightCastle_) {
        GLOBAL_GAME_SCENE->rightCastle_->Update(this);
    }

    updateAttackers_(GLOBAL_GAME_SCENE->leftAttackers_);
    updateAttackers_(GLOBAL_GAME_SCENE->rightAttackers_);
}

std::shared_ptr<CastleObject>& Game::InitLeftCastle_(CastleType id)
{
    if (leftCastle_.get() != nullptr) {
        removeChild(leftCastle_->GetSprite());
        removeChild(leftCastle_->GetLabel());
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
    addChild(leftCastle_->GetLabel(), 4);
    return leftCastle_;
}

std::shared_ptr<CastleObject>& Game::InitRightCastle_(CastleType id)
{

    if (rightCastle_.get() != nullptr) {
        removeChild(rightCastle_->GetSprite());
        removeChild(rightCastle_->GetLabel());
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
    addChild(rightCastle_->GetLabel(), 4);
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

void Game::updateAttackers_(std::vector<std::shared_ptr<AttackerObject>>& attackers)
{
    auto it = attackers.begin();
    for (int i = 0; i < attackers.size(); ++i) {
        attackers[i]->Update(this);
        if (attackers[i]->GetHealth() == 0) {
            removeChild(attackers[i]->GetSprite());
            removeChild(attackers[i]->GetLabel());
            it = attackers.erase(it);
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
        GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::SimpleAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_W) {
        GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::FirstAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_E) {
        GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::SecondAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_R) {
        GLOBAL_GAME_SCENE->AddLeftAttacker_(Game::AttackerType::ThirdAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        GLOBAL_GAME_SCENE->InitLeftCastle_(Game::CastleType::SimpleCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_S) {
        GLOBAL_GAME_SCENE->InitLeftCastle_(Game::CastleType::StrongCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_Z) {
        GLOBAL_GAME_SCENE->leftCastle_->SetHealth(GLOBAL_GAME_SCENE->leftCastle_->GetMaxHealth());
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {
        GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::SimpleAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_O) {
        GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::FirstAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_I) {
        GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::SecondAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_U) {
        GLOBAL_GAME_SCENE->AddRightAttacker_(Game::AttackerType::ThirdAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_L) {
        GLOBAL_GAME_SCENE->InitRightCastle_(Game::CastleType::SimpleCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_K) {
        GLOBAL_GAME_SCENE->InitRightCastle_(Game::CastleType::StrongCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_M) {
        GLOBAL_GAME_SCENE->rightCastle_->SetHealth(GLOBAL_GAME_SCENE->rightCastle_->GetMaxHealth());
    }
}

void OnKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
    if (GLOBAL_GAME_SCENE == nullptr) {
        return;
    }
}