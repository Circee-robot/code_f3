#define TYPE_ASSERVISSEMENT_PID_POS double
#define TYPE_ASSERVISSEMENT_PID_TIME double
#define TYPE_ASSERVISSEMENT_PID_PARAM double

#define TYPE_ASSERVISSEMENT_PID_INTEGRAL double
#define TYPE_ASSERVISSEMENT_PID_DERIVATIVE double
#define TYPE_ASSERVISSEMENT_PID_RETURN double

typedef struct
{
    TYPE_ASSERVISSEMENT_PID_PARAM P, I, D;
    TYPE_ASSERVISSEMENT_PID_INTEGRAL AbsIMax; //Anti-windup

    TYPE_ASSERVISSEMENT_PID_INTEGRAL Integration;
    TYPE_ASSERVISSEMENT_PID_POS LastPosition;
    TYPE_ASSERVISSEMENT_PID_POS LastValue;
    TYPE_ASSERVISSEMENT_PID_POS Target;

} PID_Data;

#define PID_A_PROPORTIONAL (1)
#define PID_A_DERIVATIVE   (1)
#define PID_A_INTEGRAL     (1)

#define PID_B_PROPORTIONAL (1)
#define PID_B_DERIVATIVE   (1)
#define PID_B_INTEGRAL     (1)

#define PID_ABSIMAX        (1)

/*
Sets P, I, and D for a given PID loop, and sets the max of the error integration (before multiplication by I)
*/
void PID_SetParameters(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_PARAM InP,
    TYPE_ASSERVISSEMENT_PID_PARAM InI,
    TYPE_ASSERVISSEMENT_PID_PARAM InD,
    TYPE_ASSERVISSEMENT_PID_INTEGRAL InAbsIMax
    );

/*
Set the target position
*/
void PID_SetTarget(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_POS NewTarget
    );

/*
Resets the position, integration and time
*/
void PID_Reset(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_TIME Time,
    TYPE_ASSERVISSEMENT_PID_INTEGRAL Integral,
    TYPE_ASSERVISSEMENT_PID_POS LastPosition
    );

TYPE_ASSERVISSEMENT_PID_RETURN PID_Tick(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_POS Position,
    TYPE_ASSERVISSEMENT_PID_TIME Time
    );


float tick_to_meter(enum encoder_sel sel, int num_tick);
float tick_to_meter(enum encoder_sel sel, int num_tick);
#define ENCODER_A_TO_METER (1);