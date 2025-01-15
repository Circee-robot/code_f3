#include "include/pid.h"

void PID_SetParameters(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_PARAM InP, TYPE_ASSERVISSEMENT_PID_PARAM InI, TYPE_ASSERVISSEMENT_PID_PARAM InD, TYPE_ASSERVISSEMENT_PID_INTEGRAL InAbsIMax)
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

void PID_SetTarget(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_POS NewTarget)
{
    PID->Target = NewTarget;
}

void PID_Reset(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_TIME Time, TYPE_ASSERVISSEMENT_PID_INTEGRAL Integral, TYPE_ASSERVISSEMENT_PID_POS LastValue)
{
    PID->LastTime = Time;
    PID->Integration = Integral;
    PID->LastValue = LastValue;
}

TYPE_ASSERVISSEMENT_PID_RETURN PID_Tick(PID_Data* PID, TYPE_ASSERVISSEMENT_PID_POS Position, TYPE_ASSERVISSEMENT_PID_TIME Time)
{
    TYPE_ASSERVISSEMENT_PID_POS DeltaPos = PID->Target - Position;
    TYPE_ASSERVISSEMENT_PID_TIME DeltaTime = Time - PID->LastTime;
    TYPE_ASSERVISSEMENT_PID_DERIVATIVE Derivative = (Position - PID->LastValue) / DeltaTime;
    PID->Integration += DeltaPos * DeltaTime;
    if (PID->Integration > PID->AbsIMax)
    {
        PID->Integration = PID->AbsIMax;
    }
    else if (PID->Integration < -PID->AbsIMax)
    {
        PID->Integration = -PID->AbsIMax;
    }
    TYPE_ASSERVISSEMENT_PID_RETURN value = PID->P * DeltaPos + PID->I * PID->Integration + PID->D * Derivative;
    PID->LastTime = Time;
    PID->LastValue = Position;
    return value;
}

double tick_to_meter(enum encoder_sel sel, int num_tick){
    double factor;
    switch(sel){
        case ENCODER_A:
            factor = ENCODER_A_TO_METER;
            break;
    }
    return num_tick * factor;
}

double pos_to_duty(enum encoder_sel sel, double pos){
    double factor;
    switch(sel){
        case ENCODER_A:
            factor = ENCODER_A_TO_METER;
            break;
    }
    return num_tick * factor;
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

    int encoder_a_count = 0;
    int encoder_b_count = 0;
    int tick_a = 0;
    double dist_a = 0;
    double pos_a = 0;
    uint32_t current_tick_ms;

    // Boucle d'asservissement
    while(1){

        tick_a = encoder_update(ENCODER_A,&encoder_a_count);
        dist_a = tick_to_meter(ENCODER_A, tick_a);

        current_tick_ms = clock_get_systicks();
        PID_Tick(&pid_a, dist_a, current_tick_ms);

        delay_ms(100);
    }

    return 0;
}