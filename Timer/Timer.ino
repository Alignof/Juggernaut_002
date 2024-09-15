/*
 * @date		2020 10/31-
 * @code name	Juggernaut
 * @author		Takana Norimasa <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */

#include "control.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

struct Challenge {
    void (* gaming)(void *);
    void (* setup_pin)(void);
    int time_limit;
};

#define CHALLENGES_NUM 8
extern struct Challenge RedOrBlue;
extern struct Challenge FourLights;
extern struct Challenge InvisibleLight;
extern struct Challenge CutAndPush;
extern struct Challenge Distance;
extern struct Challenge FlipSide;
extern struct Challenge EnJoy;
extern struct Challenge TMP;
struct Challenge *challenges[CHALLENGES_NUM] = {
    // 0
    &RedOrBlue,
    // 1
    &FourLights,
    // 2
    &InvisibleLight,
    // 3
    &CutAndPush,
    // 4
    &Distance,
    // 5
    &FlipSide,
    // 6
    &EnJoy,
    // 7
    &TMP,
};
