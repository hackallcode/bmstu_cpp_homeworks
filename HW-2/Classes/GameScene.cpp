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

void aad::Game::update(float time)
{
    missedTime_ = time;

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

    castles_[LEFT]->Update(this);
    castles_[RIGHT]->Update(this);

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

float aad::Game::getMissedTime() const
{
    return missedTime_;
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
    if (subtractCash_(isRight, CastleObject::GetClassCost(id))) {
        initCastle_(isRight, id);
    }
}

void aad::Game::buyCastleHp(bool isRight)
{
    if (castles_[isRight]->GetHealth() <= castles_[isRight]->GetMaxHealth() - HEALTH_BUTTON_COST) {
        if (subtractCash_(isRight, HEALTH_BUTTON_COST)) {
            castles_[isRight]->SetHealth(castles_[isRight]->GetHealth() + 100.f);
        }
    }
}

void aad::Game::buyCastleArmor(bool isRight)
{
    if (castles_[isRight]->GetArmor() <= castles_[isRight]->GetMaxArmor() - ARMOR_BUTTON_COST) {
        if (subtractCash_(isRight, ARMOR_BUTTON_COST)) {
            castles_[isRight]->SetArmor(castles_[isRight]->GetArmor() + 100.f);
        }
    }
}

void aad::Game::buyAttacker(bool isRight, AttackerType id)
{
    if (subtractCash_(isRight, AttackerObject::GetClassCost(id))) {
        addAttacker_(isRight, id);
    }
}

void aad::Game::moneyCheat(bool isRight)
{
    setCash_(isRight, CHEAT_CASH);
}

void aad::Game::initMap_()
{
    // Set background
    cocos2d::CCSprite * background = cocos2d::CCSprite::create("res/background.png");
    background->setAnchorPoint(cocos2d::Vec2(0, 0));
    addChild(background, -1);

    // Create left buttons
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(20, 830, AttackerType::AttackerTypeNo1, "Q", false)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(160, 830, AttackerType::AttackerTypeNo2, "W", true)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(300, 830, AttackerType::AttackerTypeNo3, "E", true)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(440, 830, AttackerType::AttackerTypeNo4, "R", true)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(20, 690, CastleType::CastleTypeNo2, "A", true)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(160, 690, ButtonType::HealthButton, "S", true)));
    buttons_[LEFT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(300, 690, ButtonType::ArmorButton, "D", true)));
    // Create right buttons
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(20, 830, AttackerType::AttackerTypeNo1, "P", false)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(160, 830, AttackerType::AttackerTypeNo2, "O", true)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(300, 830, AttackerType::AttackerTypeNo3, "I", true)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(440, 830, AttackerType::AttackerTypeNo4, "U", true)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(20, 690, CastleType::CastleTypeNo2, "L", true)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(160, 690, ButtonType::HealthButton, "K", true)));
    buttons_[RIGHT].push_back(std::shared_ptr<ButtonObject>(new ButtonObject(300, 690, ButtonType::ArmorButton, "J", true)));
    // Set right aligment
    for (size_t i = 0; i < buttons_[RIGHT].size(); ++i) {
        buttons_[RIGHT][i]->SetRightAlignment(getContentSize().width);
    }
    // Show buttons
    for (float i = 0; i < buttons_[LEFT].size(); ++i) {
        addChild(buttons_[LEFT][i]->GetSprite(), BUTTON_Z_ORDER);
    }
    for (float i = 0; i < buttons_[RIGHT].size(); ++i) {
        addChild(buttons_[RIGHT][i]->GetSprite(), BUTTON_Z_ORDER);
    }

    // Blocks
    for (float i = 0; i < 24; ++i) {
        blocks_.push_back(std::shared_ptr<BlockObject>(new BlockObject(80 * i, 0, BlockType::BasicBlockType)));
        blocks_.push_back(std::shared_ptr<BlockObject>(new BlockObject(80 * i, 80, BlockType::GrassBlockType)));
        addChild(blocks_[2 * i]->GetSprite(), BLOCK_Z_ORDER);
        addChild(blocks_[2 * i + 1]->GetSprite(), BLOCK_Z_ORDER);
    }
}

void aad::Game::initCastle_(bool isRight, CastleType id)
{
    if (castles_[isRight]) {
        removeChild(castles_[isRight]->GetSprite());
    }

    castles_[isRight] = std::shared_ptr<CastleObject>(new CastleObject(id));
     
    if (isRight) {
        castles_[isRight]->SetRightAlignment(getContentSize().width);
    }

    addChild(castles_[isRight]->GetSprite(), CASTLE_Z_ORDER);
}

void aad::Game::addAttacker_(bool isRight, AttackerType id)
{
    attackers_[isRight].push_back(std::shared_ptr<AttackerObject>(new AttackerObject(id)));
    
    if (isRight) {
        attackers_[isRight].back()->SetRightAlignment(getContentSize().width);
    }

    addChild(attackers_[isRight].back()->GetSprite(), ATTACKER_Z_ORDER);
}

void aad::Game::deleteDeadAttackers_(bool isRight)
{
    for (size_t i = 0; i < attackers_[isRight].size(); ++i) {
        if (attackers_[isRight][i]->GetHealth() == 0) {
            addCash_(!isRight, attackers_[isRight][i]->GetCost() * CORPSE_COST_FACTOR);

            removeChild(attackers_[isRight][i]->GetSprite());
            attackers_[isRight].erase(attackers_[isRight].begin() + i);
            --i;
        }
    }
}

void aad::Game::deleteAllAttackers_(bool isRight)
{
    while (attackers_[isRight].size() > 0) {
        removeChild(attackers_[isRight].back()->GetSprite());
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

    for (std::shared_ptr<ButtonObject>& button : buttons_[isRight]) {
        if (cash_[isRight] < std::stoi(button->GetBottomLabel())) {
            button->Lock();
        }
        else {
            button->Unlock();
        }
    }
}

void aad::Game::addCash_(bool isRight, size_t count)
{
    setCash_(isRight, cash_[isRight] + count);
}

bool aad::Game::subtractCash_(bool isRight, size_t count)
{
    if (count > cash_[isRight]) {
        return false;
    }
    else {
        setCash_(isRight, cash_[isRight] - count);
        isPlayerBegin_[isRight] = true;
        return true;
    }
}

void aad::Game::incCash_(bool isRight)
{
    if (isPlayerBegin_[isRight]) {
        ++steps_[isRight];
        if (steps_[isRight] % (
            (steps_[isRight] / CASH_INC_INTERVAL_BOOST < CASH_INC_INTERVAL) ?
            (CASH_INC_INTERVAL - steps_[isRight] / CASH_INC_INTERVAL_BOOST) : 1
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

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_F1) {
        GLOBAL_GAME_SCENE->initNewGame();
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_F2) {
        GLOBAL_GAME_SCENE->moneyCheat(LEFT);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_F3) {
        GLOBAL_GAME_SCENE->moneyCheat(RIGHT);
    }

    if ((code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE || code == cocos2d::EventKeyboard::KeyCode::KEY_ENTER) 
        && GLOBAL_GAME_SCENE->isGameEnd()) {
        GLOBAL_GAME_SCENE->initNewGame();
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_Q) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, AttackerType::AttackerTypeNo1);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_W) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, AttackerType::AttackerTypeNo2);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_E) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, AttackerType::AttackerTypeNo3);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_R) {
        GLOBAL_GAME_SCENE->buyAttacker(LEFT, AttackerType::AttackerTypeNo4);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
        GLOBAL_GAME_SCENE->buyCastle(LEFT, CastleType::CastleTypeNo2);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_S) {
        GLOBAL_GAME_SCENE->buyCastleHp(LEFT);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        GLOBAL_GAME_SCENE->buyCastleArmor(LEFT);
    }

    if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, AttackerType::AttackerTypeNo1);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_O) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, AttackerType::AttackerTypeNo2);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_I) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, AttackerType::AttackerTypeNo3);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_U) {
        GLOBAL_GAME_SCENE->buyAttacker(RIGHT, AttackerType::AttackerTypeNo4);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_L) {
        GLOBAL_GAME_SCENE->buyCastle(RIGHT, CastleType::CastleTypeNo2);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_K) {
        GLOBAL_GAME_SCENE->buyCastleHp(RIGHT);
    }
    if (code == cocos2d::EventKeyboard::KeyCode::KEY_J) {
        GLOBAL_GAME_SCENE->buyCastleArmor(RIGHT);
    }
}