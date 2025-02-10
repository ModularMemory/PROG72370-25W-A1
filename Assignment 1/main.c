#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "queue.h"
#include "user.h"

// The length of random user usernames
#define RANDOM_USER_USERNAME_LEN 25

// There are 10 numbers and 26 letters
#define NUMBER_COUNT 10
#define LETTER_COUNT 26

/// <summary>
/// Generates a random number inclusively between min_incl and max_excl - 1
/// </summary>
static unsigned int rand_range(unsigned int min_incl, unsigned int max_excl) {
    assert(min_incl < max_excl);
    return rand() % (max_excl - min_incl) + min_incl;
}

/// <summary>
/// Generates a random number or letter
/// </summary>
static char get_random_alphanumeric(void) {
    char c = (char)rand_range(0, NUMBER_COUNT + LETTER_COUNT * 2); // 0-9, A-Z, a-z

    if (c < NUMBER_COUNT) {
        return c + '0'; // Within 0-9, number
    }

    c -= NUMBER_COUNT;

    if (c < LETTER_COUNT) {
        return c + 'A'; // Within 10-35, uppercase letter
    }

    c -= LETTER_COUNT;

    return c + 'a'; // >= 36, lowercase letter
}

/// <summary>
/// Creates a user struct with random statistics
/// </summary>
static user_t create_random_user(void) {
    // Ensure that the random user username length fits in the username struct
    assert(RANDOM_USER_USERNAME_LEN < USERNAME_LEN);

    // Create a random name
    char name[USERNAME_LEN] = { 0 };
    for (int i = 0; i < RANDOM_USER_USERNAME_LEN; i++) {
        name[i] = get_random_alphanumeric();
    }

    unsigned int level = rand_range(1, 61); // 1-60
    user_faction_t faction = (user_faction_t)rand_range(RED, GREEN + 1); // red, blue, green

    return create_user(name, level, faction);
}

/// <summary>
/// Creates and enqueues user_count number of users in the given queue
/// </summary>
static int enqueue_users(Queue queue, int user_count) {
    for (int i = 0; i < user_count; i++) {
        user_t user = create_random_user();
        if (!enqueue(queue, user)) {
            return 1;
        }
    }

    return 0;
}

/// <summary>
/// Returns the string representation of a user faction
/// </summary>
static const char* get_faction_string(user_faction_t faction) {
    switch (faction) {
    case RED:
        return "Red";
    case BLUE:
        return "Blue";
    case GREEN:
        return "Green";
    }

    return "Invalid faction";
}

int main(int argc, char** argv) {
    // Check if user count param is passed
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <user_count>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get user count from arg
    int user_count = atoi(argv[1]);
    printf("Generating %d users...\n", user_count);

    // Seed rng
    srand(time(NULL));

    Queue queue = create_queue();

    // Enqueue random users
    if (enqueue_users(queue, user_count) != 0) {
        fprintf(stderr, "Error: Failed to enqueue users.\n");
        exit(EXIT_FAILURE);
    }

    // Dequeue users
    while (!is_queue_empty(queue)) {
        user_t user = dequeue(queue);

        const char* faction_string = get_faction_string(user.faction);

        printf("Dequeued %s - Level %2u - %5s faction\n", user.name, user.level, faction_string);
    }

    destroy_queue(queue);
}