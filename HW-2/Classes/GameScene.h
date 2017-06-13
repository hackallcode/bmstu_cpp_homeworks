#ifndef __GAME_SCENE_INCLUDED__
#define __GAME_SCENE_INCLUDED__

#include "cocos2d.h"
#include <vector> // std::vector
#include <memory> // std::shared_ptr
#include <string> // std::to_string

#include "BlockObject.h"
#include "CastleObject.h"
#include "AttackerObject.h"
#include "ButtonObject.h"

namespace aad {

    // CONSTANTS
    bool const LEFT = 0;
    bool const RIGHT = 1;

    // GAME PARAMETERS
    size_t const START_CASH = 40;
    float const CORPSE_COST_FACTOR = 1.5f;
    size_t const CASH_INC_INTERVAL = 50;
    size_t const CASH_INC_INTERVAL_BOOST = 120;

    // COORDINATES
    float const CASH_TOP = 20.f;
    float const CASH_LEFT = 20.f;

    // Z ORDERS
    int const ATTACKER_Z_ORDER = 1;
    int const ATTACKER_HEALTH_Z_ORDER = 2;
    int const CASTLE_Z_ORDER = 3;
    int const CASTLE_HEALTH_Z_ORDER = 4;
    int const BLOCK_Z_ORDER = 5;
    int const BUTTON_Z_ORDER = 6;
    int const CASH_Z_ORDER = 7;

    // CHEATS PARAMETERS
    size_t const CHEAT_CASH = 999999999;

    class Game
        : public cocos2d::Layer
    {
    public:
        static cocos2d::Scene* createScene();
        static Game* create();

        ~Game() = default;

        virtual bool init() override;
        virtual void update(float time) override;

        float getMissedTime() const;

        std::shared_ptr<CastleObject> getCastle(bool isRight);
        std::vector<std::shared_ptr<AttackerObject>>& getAttackers(bool isRight);
        size_t getCash(bool isRight);
        bool isGameEnd();

        void initNewGame();
        void buyCastle(bool isRight, CastleType id);
        void buyCastleHp(bool isRight);
        void buyCastleArmor(bool isRight);
        void buyAttacker(bool isRight, AttackerType id);
        
        void moneyCheat(bool isRight);

    private:
        float missedTime_;
        
        std::vector<std::shared_ptr<BlockObject>> blocks_;
        std::vector<std::shared_ptr<ButtonObject>> buttons_[2];
        void initMap_();

        std::shared_ptr<CastleObject> castles_[2];
        void initCastle_(bool isRight, CastleType id = CastleType::CastleTypeNo1);

        std::vector<std::shared_ptr<AttackerObject>> attackers_[2];
        void addAttacker_(bool isRight, AttackerType id);
        void deleteDeadAttackers_(bool isRight);
        void deleteAllAttackers_(bool isRight);
        
        bool isPlayerBegin_[2];
        size_t steps_[2];
        size_t cash_[2];
        cocos2d::CCLabelTTF* cashLabels_[2];        
        void initCash_(bool isRight);
        void setCash_(bool isRight, size_t count);
        void addCash_(bool isRight, size_t count);
        bool subtractCash_(bool isRight, size_t count);
        void incCash_(bool isRight);
        
        cocos2d::CCLabelTTF* victoryLabel_ = nullptr;
        void setWinningPlayer_(bool isRight);
    };

    void keyListener(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);

}

#endif // __GAME_SCENE_INCLUDED__
