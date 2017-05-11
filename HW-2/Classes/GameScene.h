#ifndef __GAME_SCENE_INCLUDED__
#define __GAME_SCENE_INCLUDED__

#include "cocos2d.h"
#include <vector>
#include <memory>

#include "blocks/BasicBlockObject.h"

#include "castles/SimpleCastleObject.h"
#include "castles/StrongCastleObject.h"

#include "attackers/SimpleAttackerObject.h"
#include "attackers/FirstAttackerObject.h"
#include "attackers/SecondAttackerObject.h"
#include "attackers/ThirdAttackerObject.h"

using namespace AttackAndDefend;

class Game
    : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    static Game* create();
    virtual bool init();

    virtual void update(float);

    ~Game() = default;

    friend class AttackerObject;
    friend void OnKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);
    friend void OnKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);
    
private:
    enum AttackerType {
        SimpleAttacker = 0
        , FirstAttacker
        , SecondAttacker
        , ThirdAttacker
    };

    enum CastleType {
        SimpleCastle = 0
        , StrongCastle
    };

    std::vector<std::shared_ptr<BlockObject>> blocks_;

    std::shared_ptr<CastleObject> leftCastle_;
    std::vector<std::shared_ptr<AttackerObject>> leftAttackers_;
    std::shared_ptr<CastleObject> rightCastle_;
    std::vector<std::shared_ptr<AttackerObject>> rightAttackers_;

    std::shared_ptr<CastleObject>& InitLeftCastle_(CastleType id = CastleType::SimpleCastle);
    std::shared_ptr<CastleObject>& InitRightCastle_(CastleType id = CastleType::SimpleCastle);
    std::shared_ptr<AttackerObject>& AddLeftAttacker_(AttackerType id = AttackerType::SimpleAttacker);
    std::shared_ptr<AttackerObject>& AddRightAttacker_(AttackerType id = AttackerType::SimpleAttacker);
    void updateAttackers_(std::vector<std::shared_ptr<AttackerObject>>& attackers);
};

#endif // __GAME_SCENE_INCLUDED__
