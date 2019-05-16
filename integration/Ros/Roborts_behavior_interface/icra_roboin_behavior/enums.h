#ifndef ICRA_ROBOIN_BEHAVIOR_ENUMS_H
#define ICRA_ROBOIN_BEHAVIOR_ENUMS_H


namespace icra_roboin_behavior
{

enum class BehaviorState {
    IDLE=0,
    RUNNING=1,
    SUCCESS,
    FAILURE,
};

enum class BehaviorStyle {
    STOP=0,
    MOVE=1,
    MANUAL_ACCEL,
    ATTACK,
    CHASE,
    PATROL,
    ROTATE,
    RUNAWAY,
    RELOAD,
    BACKBOOT,
    MANUAL_SPEED,
    END,
    
};

enum class ChassisMode {
    IDLE=0,
    NAVIGATION=1,
    ACCEL,
    SPEED,
    
};
enum class GimbalMode {
    IDLE=0,
    ANGLE=1,
};


}

#endif