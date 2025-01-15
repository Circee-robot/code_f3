#include "include/pid.h"

void PID_SetParameters(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_PARAM InP,
    TYPE_ASSERVISSEMENT_PID_PARAM InI,
    TYPE_ASSERVISSEMENT_PID_PARAM InD,
    TYPE_ASSERVISSEMENT_PID_INTEGRAL InAbsIMax
)
{
    PID->P = InP;
    PID->I = InI;
    PID->D = InD;
    PID->AbsIMax = InAbsIMax;
    if (PID->Integration > InAbsIMax)
    {
        PID->Integration = InAbsIMax;
    }
    else if (PID->Integration < -InAbsIMax)
    {
        PID->Integration = -InAbsIMax;
    }
}

void PID_SetTarget(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_POS NewTarget
){
    PID->Target = NewTarget;
}

void PID_Reset(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_INTEGRAL Integral,
    TYPE_ASSERVISSEMENT_PID_POS LastPosition,
    TYPE_ASSERVISSEMENT_PID_POS LastValue
){
    PID->Integration = Integral;
    PID->LastPosition = LastPosition;
    PID->LastValue = LastValue;
}

TYPE_ASSERVISSEMENT_PID_RETURN PID_Tick(
    PID_Data* PID,
    TYPE_ASSERVISSEMENT_PID_POS Position
)
{
    TYPE_ASSERVISSEMENT_PID_POS DeltaPos = PID->Target - Position;
    TYPE_ASSERVISSEMENT_PID_DERIVATIVE Derivative = (Position - PID->LastPosition);
    PID->Integration += DeltaPos;
    if (PID->Integration > PID->AbsIMax)
    {
        PID->Integration = PID->AbsIMax;
    }
    else if (PID->Integration < -PID->AbsIMax)
    {
        PID->Integration = -PID->AbsIMax;
    }
    TYPE_ASSERVISSEMENT_PID_RETURN value = PID->P * DeltaPos + PID->I * PID->Integration + PID->D * Derivative;
    float speed = (value - PID->LastValue);

    PID->LastPosition = Position;
    PID->LastValue = value;
    return speed;
}

double meter_to_tick(
    enum encoder_sel sel,
    float meter
){
    double factor;
    switch(sel){
        case ENCODER_A:
            factor = ENCODER_A_TO_METER;
            break;
    }
    return meter * factor;
}

double pos_to_duty(enum encoder_sel sel, double pos){
    double factor;
    switch(sel){
        case ENCODER_A:
            factor = ENCODER_A_TO_METER;
            break;
    }
    return pos * factor;
}

int main(){
    PID_Data pid_a,pid_b;

    PID_SetParameters(
        &pid_a,
        PID_A_PROPORTIONAL,
        PID_A_INTEGRAL,
        PID_A_DERIVATIVE,
        PID_ABSIMAX
    );
    PID_SetParameters(
        &pid_b,
        PID_B_PROPORTIONAL,
        PID_B_INTEGRAL,
        PID_B_DERIVATIVE,
        PID_ABSIMAX
    );

    int encoder_a_tick_prev = 0;
    int encoder_a_pos = 0;
    float motor_a_input;
    enum motor_state motor_a_dir;

    // Boucle d'asservissement
    while(1){
        encoder_a_pos += encoder_update(ENCODER_A,&encoder_a_tick_prev);
        motor_a_input = PID_Tick(&pid_a, encoder_a_pos);

        // Direction switch
        if (motor_a_input >= 0) {
            motor_a_dir = FORWARD;
        } else {
            motor_a_input = motor_a_input * (-1);
            motor_a_dir = BACKWARD;
        }
        motor_set(MOTOR_A, motor_a_input, motor_a_dir);

        delay_ms(100);
    }

    return 0;
}