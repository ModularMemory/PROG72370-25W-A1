#pragma once

/// <summary>
/// A user's faction
/// </summary>
typedef enum {
    RED,
    BLUE,
    GREEN
} user_faction_t;

#define USERNAME_LEN 60

/// <summary>
/// Represents a user
/// </summary>
typedef struct {
    char name[USERNAME_LEN];
    unsigned int level;
    user_faction_t faction;
} user_t;

/// <summary>
/// Creates a new user
/// </summary>
user_t create_user(char name[USERNAME_LEN], unsigned int level, user_faction_t faction);