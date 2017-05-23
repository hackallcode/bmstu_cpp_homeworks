#include "GameScene.h"
#include "SimpleAudioEngine.h"

aad::Game* GLOBAL_GAME_SCENE = nullptr;

cocos2d::Scene* aad::Game::createScene()
{
    // Создание сцены со слоем
    cocos2d::Scene * scene = cocos2d::Scene::create();
    Game * layer = Game::create();
    scene->addChild(layer);

    return scene;
}

aad::Game* aad::Game::create()
{
    Game *result = new(std::nothrow) Game();
    if (result && result->init())
    {
        result->autorelease();
        return result;
    }
    else
    {
        delete result;
        return nullptr;
    }
}

// on "init" you need to initialize your instance
bool aad::Game::init()
{
    //////////////////////////////
    // 1. Super init first

    if (!Layer::init())
    {
        return false;
    }

    //////////////////////////////
    // 2. Objects

    initMap_();
    initNewGame();

    //////////////////////////////
    // 3. Listeners 

    GLOBAL_GAME_SCENE = this;

    cocos2d::EventListenerKeyboard * listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = keyListener;

    this->scheduleUpdate();
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void aad::Game::update(float)
{
    incCash_(LEFT);
    incCash_(RIGHT);

    if (castles_[LEFT]->GetHealth() == 0) {
        setWinningPlayer_(RIGHT);
        return;
    }
    else if (castles_[RIGHT]->GetHealth() == 0) {
        setWinningPlayer_(LEFT);
        return;
    }

    for (int i = 0; i < attackers_[LEFT].size(); ++i) {
        attackers_[LEFT][i]->Update(this);
    }
    for (int i = 0; i < attackers_[RIGHT].size(); ++i) {
        attackers_[RIGHT][i]->Update(this);
    }

    for (int i = 0; i < attackers_[LEFT].size(); ++i) {
        attackers_[LEFT][i]->Attack(this);
    }
    for (int i = 0; i < attackers_[RIGHT].size(); ++i) {
        attackers_[RIGHT][i]->Attack(this);
    }

    deleteDeadAttackers_(LEFT);
    deleteDeadAttackers_(RIGHT);
}

std::shared_ptr<aad::CastleObject> aad::Game::getCastle(bool isRight)
{
    return castles_[isRight];
}

std::vector<std::shared_ptr<aad::AttackerObject>>& aad::Game::getAttackers(bool isRight)
{
    return attackers_[isRight];
}

size_t aad::Game::getCash(bool isRight)
{
    return cash_[isRight];
}

bool aad::Game::isGameEnd()
{
    return victoryLabel_ != nullptr;
}

void aad::Game::initNewGame()
{
    initCastle_(LEFT);
    initCastle_(RIGHT);

    deleteAllAttackers_(LEFT);
    deleteAllAttackers_(RIGHT);

    initCash_(LEFT);
    initCash_(RIGHT);

    if (victoryLabel_ != nullptr) {
        removeChild(victoryLabel_);
        victoryLabel_ = nullptr;
    }
}

void aad::Game::buyCastle(bool isRight, CastleType id)
{
    switch (id)
    {
    case Game::SimpleCastle:
        if (subtractCash_(isRight, SimpleCastleObject::GetClassCost())) {
            initCastle_(isRight, id);
        }
        break;
    case Game::StrongCastle:
        if (subtractCash_(isRight, StrongCastleObject::GetClassCost())) {
            initCastle_(isRight, id);
        }
        break;
    }
}

void aad::Game::buyCastleHp(bool isRight)
{
    if (castles_[isRight]->GetHealth() <= castles_[isRight]->GetMaxHealth() - 100.f) {
        if (subtractCash_(isRight, 100)) {
            castles_[isRight]->SetHealth(castles_[isRight]->GetHealth() + 100.f);
        }
    }
}

void aad::Game::buyCastleArmor(bool isRight)
{
    if (castles_[isRight]->GetArmor() <= castles_[isRight]->GetMaxArmor() - 100.f) {
        if (subtractCash_(isRight, 100)) {
            castles_[isRight]->SetArmor(castles_[isRight]->GetArmor() + 100.f);
        }
    }
}

void aad::Game::buyAttacker(bool isRight, AttackerType id)
{
    switch (id)
    {
    case aad::Game::SimpleAttacker:
        if (subtractCash_(isRight, SimpleAttackerObject::GetClassCost())) {
            addAttacker_(isRight, id);
        }
        break;
    case aad::Game::FirstAttacker:
        if (subtractCash_(isRight, FirstAttackerObject::GetClassCost())) {
            addAttacker_(isRight, id);
        }
        break;
    case aad::Game::SecondAttacker:
        if (subtractCash_(isRight, SecondAttackerObject::GetClassCost())) {
            addAttacker_(isRight, id);
        }
        break;
    case aad::Game::ThirdAttacker:
        if (subtractCash_(isRight, ThirdAttackerObject::GetClassCost())) {
            addAttacker_(isRight, id);
        }
        break;
    }
}

void aad::Game::initMap_()
{
    // Set background
    cocos2d::CCSprite * background = cocos2d::CCSprite::create("background.png");
    background->setAnchorPoint(cocos2d::Vec2(0, 0));
    addChild(background, -1);

    // Blocks
    for (float i = 0; i < 24; ++i) {
        blocks_.push_back(std::shared_ptr<BlockObject>(new BasicBlockObject(80 * i, 0)));
        blocks_.push_back(std::shared_ptr<BlockObject>(new GrassBlockObject(80 * i, 80)));
        addChild(blocks_[2 * i]->GetSprite(), BLOCK_Z_ORDER);
        addChild(blocks_[2 * i + 1]->GetSprite(), BLOCK_Z_ORDER);
    }
}

void aad::Game::initCastle_(bool isRight, CastleType id)
{
    if (castles_[isRight]) {
        removeChild(castles_[isRight]->GetSprite());
        removeChild(castles_[isRight]->GetHealthLabel());
        removeChild(castles_[isRight]->GetArmorLabel());
    }

    switch (id)
    {
    case Game::SimpleCastle:
        castles_[isRight] = std::shared_ptr<CastleObject>(new SimpleCastleObject);
        break;
    case Game::StrongCastle:
        castles_[isRight] = std::shared_ptr<CastleObject>(new StrongCastleObject);
        break;
    }
    if (isRight) {
        castles_[isRight]->SetRightAlignment(getContentSize().width);
    }

    addChild(castles_[isRight]->GetSprite(), CASTLE_Z_ORDER);
    addChild(castles_[isRight]->GetHealthLabel(), CASTLE_HEALTH_Z_ORDER);
    addChild(castles_[isRight]->GetArmorLabel(), CASTLE_HEALTH_Z_ORDER);    
}

void aad::Game::addAttacker_(bool isRight, AttackerType id)
{
    switch (id)
    {
    case Game::SimpleAttacker:
        attackers_[isRight].push_back(std::shared_ptr<AttackerObject>(new SimpleAttackerObject));
        break;
    case Game::FirstAttacker:
        attackers_[isRight].push_back(std::shared_ptr<AttackerObject>(new FirstAttackerObject));
        break;
    case Game::SecondAttacker:
        attackers_[isRight].push_back(std::shared_ptr<AttackerObject>(new SecondAttackerObject));
        break;
    case Game::ThirdAttacker:
        attackers_[isRight].push_back(std::shared_ptr<AttackerObject>(new ThirdAttackerObject));
        break;
    }
    if (isRight) {
        attackers_[isRight].back()->SetRightAlignment(getContentSize().width);
    }

    addChild(attackers_[isRight].back()->GetSprite(), ATTACKER_Z_ORDER);
    addChild(attackers_[isRight].back()->GetHealthLabel(), ATTACKER_HEALTH_Z_ORDER);
    addChild(attackers_[isRight].back()->GetArmorLabel(), ATTACKER_HEALTH_Z_ORDER);
}

void aad::Game::deleteDeadAttackers_(bool isRight)
{
    for (size_t i = 0; i < attackers_[isRight].size(); ++i) {
        if (attackers_[isRight][i]->GetHealth() == 0) {
            addCash_(!isRight, attackers_[isRight][i]->GetCost() * CORPSE_COST_FACTOR);

            removeChild(attackers_[isRight][i]->GetSprite());
            removeChild(attackers_[isRight][i]->GetHealthLabel());

            attackers_[isRight].erase(attackers_[isRight].begin() + i);
            --i;
        }
    }
}

void aad::Game::deleteAllAttackers_(bool isRight)
{
    while (attackers_[isRight].size() > 0) {
        removeChild(attackers_[isRight].back()->GetSprite());
        removeChild(attackers_[isRight].back()->GetHealthLabel());

        attackers_[isRight].pop_back();
    }
}

void aad::Game::initCash_(bool isRight)
{
    isPlayerBegin_[isRight] = false;
    steps_[isRight] = 0;

    if (cashLabels_[isRight] == nullptr) {
        cashLabels_[isRight] = cocos2d::CCLabelTTF::create("", "Helvetica", 60, cocos2d::Size(960, 60));
        cashLabels_[isRight]->setHorizontalAlignment(
            isRight ? cocos2d::TextHAlignment::RIGHT : cocos2d::TextHAlignment::LEFT
        );
        cashLabels_[isRight]->setAnchorPoint(cocos2d::Vec2(isRight ? 1 : 0, 1));
        cashLabels_[isRight]->setPositionX(isRight ? getContentSize().width - CASH_LEFT : CASH_LEFT);
        cashLabels_[isRight]->setPositionY(getContentSize().height - CASH_TOP);
        addChild(cashLabels_[isRight], CASH_Z_ORDER);
    }

    setCash_(isRight, START_CASH);
}

void aad::Game::setCash_(bool isRight, size_t count)
{
    cash_[isRight] = count;

    cashLabels_[isRight]->setString(std::to_string(cash_[isRight]) + " coins");
}

void aad::Game::addCash_(bool isRight, size_t count)
{
    setCash_(isRight, cash_[isRight] + count);
}

bool aad::Game::subtractCash_(bool isRight, size_t count)
{
    isPlayerBegin_[isRight] = true;

    if (count > cash_[isRight]) {
        return false;
    }
    else {
        setCash_(isRight, cash_[isRight] - count);
        return true;
    }
}

void aad::Game::incCash_(bool isRight)
{
    if (isPlayerBegin_[isRight]) {
        ++steps_[isRight];
        if (steps_[isRight] % (
            (steps_[isRight] / CHANGE_CASH_INC_INTERVAL < CASH_INC_INTERVAL) ?
            (CASH_INC_INTERVAL - steps_[isRight] / CHANGE_CASH_INC_INTERVAL) : 1
            ) == 0) {
            addCash_(isRight, 1);
        }
    }
}

void aad::Game::setWinningPlayer_(bool isRight)
{
    if (victoryLabel_ == nullptr) {
        victoryLabel_ = cocos2d::CCLabelTTF::create(
            std::string(isRight ? "RIGHT" : "LEFT") + " PLAYER WINS!"
            , "Helvetica", 100
            , cocos2d::Size(1920, 1080)
            , cocos2d::TextHAlignment::CENTER
            , cocos2d::TextVAlignment::CENTER
        );
        victoryLabel_->setAnchorPoint(cocos2d::Vec2(0, 0));
        victoryLabel_->setColor(cocos2d::Color3B(60, 60, 60));
        addChild(victoryLabel_);
    }
}

void aad::keyListener(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
    if (GLOBAL_GAME_SCENE == nullptr) {
        return;
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE && GLOBAL_GAME_SCENE->isGameEnd()) {
        GLOBAL_GAME_SCENE->initNewGame();
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_Q) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, Game::AttackerType::SimpleAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_W) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, Game::AttackerType::FirstAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_E) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, Game::AttackerType::SecondAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_R) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, Game::AttackerType::ThirdAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        GLOBAL_GAME_SCENE->buyCastle(LEFT, Game::CastleType::StrongCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_S) {
        GLOBAL_GAME_SCENE->buyCastleHp(LEFT);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        GLOBAL_GAME_SCENE->buyCastleArmor(LEFT);
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_U) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, Game::AttackerType::SimpleAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_I) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, Game::AttackerType::FirstAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_O) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, Game::AttackerType::SecondAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, Game::AttackerType::ThirdAttacker);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_J) {
        GLOBAL_GAME_SCENE->buyCastle(RIGHT, Game::CastleType::StrongCastle);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_K) {
        GLOBAL_GAME_SCENE->buyCastleHp(RIGHT);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_L) {
        GLOBAL_GAME_SCENE->buyCastleArmor(RIGHT);
    }
}