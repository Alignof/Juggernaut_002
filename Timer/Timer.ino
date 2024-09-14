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

#define CHALLENGES_NUM 5
extern struct Challenge RedOrBlue;
extern struct Challenge FourLights;
extern struct Challenge InvisibleLight;
extern struct Challenge CutAndPush;
extern struct Challenge TMP;
struct Challenge *challenges[CHALLENGES_NUM] = {
    &RedOrBlue,
    &FourLights,
    &InvisibleLight,
    &CutAndPush,
    &TMP,
};
