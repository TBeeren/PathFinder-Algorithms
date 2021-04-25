#ifndef DEFINES_H
#define DEFINES_H

#define TYPE float
#define ACTIONS 3
#define STATES 3
#define MEASUREMENTS 2

enum eActions
{
    ACTION_TRANSLATION_X,
    ACTION_TRANSLATION_Y,
    ACTION_ROTATE
};

enum eStates
{
    STATE_TRANSLATION_X,
    STATE_TRANSLATION_Y,
    STATE_COMPASS
};

enum eMeasurements
{
    MEASUREMENT_ODOMETER,
    MEASUREMENT_COMPASS
};

#endif /*DEFINES_H*/