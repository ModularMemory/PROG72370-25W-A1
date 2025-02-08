#include <string.h>

#include "user.h"

user_t create_user(char name[USERNAME_LEN], unsigned int level, user_faction_t faction) {
    user_t user = { 0 };

    strncpy_s(user.name, USERNAME_LEN, name, USERNAME_LEN);
    user.level = level;
    user.faction = faction;

    return user;
}