#ifndef ICRA_ROBOIN_BEHAVIOR_ENUMS_H
#define ICRA_ROBOIN_BEHAVIOR_ENUMS_H


namespace icra_roboin_behavior
{
/////////////////////////////////////////// 
///////////////////////////////////////////    
/////////////////GAME INFO/////////////////
/////////////////////////////////////////// 
/////////////////////////////////////////// 
enum class GameState {
    DEAD=0,
    READY=1,
    PLAY=2,
    END=3,
};

enum class TeamType {
    BLUE_TEAM=0,
    RED_TEAM=1,
    NONE=2,
};

enum class PlayerType {
    ALLY=0,
    ENEMY_ONE=1,
    ENEMY_TWO=2,
    ENEMY_ANY=3,
    UNKNOWN=4,
};

enum class RuleType {
    SOLO=0,
    ONE_VS_ONE=1,
    TWO_VS_TWO=2,
    ONE_VS_TWO=3,
    TWO_VS_ONE=4,
};

enum class ArmorType {
    FRONT=0,
    LEFT=1,
    REAR=2,
    RIGHT=3,
};

enum class PenaltyType {
    COLLISION=0,
    ENEMY_SUPPLY_ZONE=1,
}; //TODO
/////////////////////////////////////////// 
///////////////////////////////////////////   
/////////////////BEHAVIORS/////////////////
/////////////////////////////////////////// 
/////////////////////////////////////////// 
enum class BehaviorProcess {
    IDLE=0,
    RUNNING=1,
    SUCCESS=2,
    FAILURE=3,
    BUSY=4,
};
enum class BehaviorStyle {
    READY=0,
    LOCKON_SEARCH_MOVE=1,
    MANUAL_SPEED_CONTROL=2,
    HOLD_ROTATE=3,
    HOLD_SENTRY=4,
    RELOAD=5,
    GET_BUFF=6,
    BACKBOOT=7,
    //////////experimental//////////
    FORCE_SEARCH_MOVE,
    FORCE_LOCKON_MOVE,
    FORCE_DIRECTION_MOVE,
    ACCEL_CONTROL,
};
enum class TaskCheck {
    NOT_YET=0,
    GET_READY=1,
    EXECUTE=2,
    BUSY=3,
    FINISHED=4,
    FAIL=5,
};
enum class SetBehaviorServiceInfo {
    SUCCESS=0,
    ALREADY_THAT_BEHAVIOR=1,
    FAIL_BEHAVIOR_BUSY=2,
    FAIL_UNKNOWN=3,
};
///////////////////////////////////////////
///////////////////////////////////////////    
/////////////////EXECUTORS/////////////////
/////////////////////////////////////////// 
/////////////////////////////////////////// 
enum class ChassisMode {
    IDLE=0,
    NAVIGATION=1,
    SPEED_WITH_LOCKON=2,
    SPEED,
    ACCEL,    
};
enum class GimbalMode {
    IDLE=0,
    ANGLE=1,
};
enum class LockonMode {
    ANGULAR_VEL=0,
    RELATIVE_ANGLE=1,
    RELATIVE_ANGLE_SENTRY=2,
    GLOBAL_YAW=3,
    GLOBAL_YAW_SENTRY=4,
    TARGET_ENEMY_LOCKON=5,
    TARGET_POSITION_LOCKON=6,
    TARGET_GOAL_LOCKON=7,
};
/////////////////////////////////////////// 
/////////////////////////////////////////// 



}

#endif