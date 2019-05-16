#ifndef ICRA_ROBOIN_BEHAVIOR_ENUMS_H
#define ICRA_ROBOIN_BEHAVIOR_ENUMS_H


namespace icra_roboin_behavior
{
///////////////////////////////////////////
///////////////////////////////////////////
/////////////////GAME INFO/////////////////
///////////////////////////////////////////
///////////////////////////////////////////
enum class GameStatus {
    PRE_MATCH=0,
    SETUP=1,
    INIT=2,
    FIVE_SEC_CD=3,
    ROUND=4,
    CALCULATION=5,
};

enum class GameResult {
    DRAW=0,
    RED_WIN=1,
    BLUE_WIN=2,
};

enum class RobotId {
    NEUTRAL=0,
    RED3=3,
    RED4=4,
    BLUE3=13,
    BLUE4=14,
};

enum class RobotLife {
    DEAD=0,
    ALIVE=1,
};

enum class BonusZone {
    UNOCCUPIED=0,
    BEING_OCCUPIED=1,
    OCCUPIED=2,
};

enum class SupplierStatus {
    CLOSE=0,
    PREPARING=1,
    SUPPLYING=2,
};

enum class RobotBonus {
    BUFF_OFF=0,
    BUFF_ON=1,
};

enum class RobotDamageType {
    ARMOR=0,
    OFFLINE=1,
    EXCEED_HEAT=2,
    EXCEED_POWER=3,
};

enum class RobotDamageArmor {
    FORWARD=0,
    BACKWARD=1,
    LEFT=2,
    RIGHT=3,
};

enum class TeamType {
    NONE=0,
    RED_TEAM=1,
    BLUE_TEAM=2,
};

enum class GameType {
    ALLY=0,
    ENEMY_ONE=1,
    ENEMY_TWO=2,
    ENEMY_ANY=3,
    UNKNOWN=4,
}; //->SHOULD FIX IT

enum class RuleType {
    SOLO=0,
    ONE_VS_ONE=1, // ALLY VS ENEMY
    TWO_VS_TWO=2,
    ONE_VS_TWO=3,
    TWO_VS_ONE=4,
};

enum class PlayerType {
        ALLY = 0,
        ENEMY_ONE = 1,
        ENEMY_TWO = 2,
        ENEMY_ANY = 3,
        UNKNOWN = 4,
};
///////////////////////////////////////////
///////////////////////////////////////////
/////////////////BEHAVIORS/////////////////
///////////////////////////////////////////
///////////////////////////////////////////
enum class BehaviorStyle {
    READY=0,
    HOLD=1,
    MOVE=2,

};
enum class TaskCheck {
    NOT_YET=0,
    GET_READY=1,
    EXECUTE=2,
    BUSY=3,
    FINISHED=4,
    FAIL=5,
};
///////////////////////////////////////////
///////////////////////////////////////////
/////////////////EXECUTORS/////////////////
///////////////////////////////////////////
///////////////////////////////////////////
enum class ChassisMode {
    IDLE=0,
    NAVIGATION=1,
    SPEED=2,
    ACCEL=3,
};

///////////////////////////////////////////
///////////////////////////////////////////



}

#endif
