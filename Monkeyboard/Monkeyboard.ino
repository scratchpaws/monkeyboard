#include "TrinketHidCombo.h"
#include <EEPROM.h>

#define SRAND_LOW 100
#define SRAND_HIGH 101

#define MOUSE_WINDOW_SIZE 256

#define UPPERS_LEN 26
#define LOWERS_LEN 26
#define NUMS_LEN 10
#define SPECIAL_LEN 9

int last_srand = 0;
int global_mouse_x = 0;
int global_mouse_y = 0;
int need_upper = 1;

static const char *uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char *lowers = "abcdefghijklmnopqrstuvwxyz";
static const char *nums = "0123456789";
static const char *special = ".,-!();:?";

void setup() {
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(5, INPUT);

    TrinketHidCombo.begin();

    update_srand();
    srand(last_srand);
}

void loop() {
    TrinketHidCombo.poll();
    int action;
    action = get_rand(10);
    if (action >= 5) {
        mouse_movement();
    } else {
        keyboard_action();
    }
    int action_delay;
    action_delay = get_rand(1000);
    delay_with_poll(action_delay);
}

void mouse_movement() {
    int mouse_direct;
    mouse_direct = get_rand(9);
    int move_count = get_rand(100);
    int i;
    char x, y;
    x = 0;
    y = 0;

    switch (mouse_direct) {
    case 0:
        x = 0;
        y = -1;
        break;
    case 1:
        x = 1;
        y = -1;
        break;
    case 2:
        x = 1;
        y = 0;
        break;
    case 3:
        x = 1;
        y = 1;
        break;
    case 4:
        x = 0;
        y = 1;
        break;
    case 5:
        x = -1;
        y = 1;
        break;
    case 6:
        x = -1;
        y = 0;
        break;
    case 7:
        x = -1;
        y = -1;
        break;
    default:
        return;
    }
    for (i = 0; i < move_count; i++) {
        if (global_mouse_x + x > MOUSE_WINDOW_SIZE
                || global_mouse_x + x < -1 * (MOUSE_WINDOW_SIZE)
                || global_mouse_y + y > MOUSE_WINDOW_SIZE
                || global_mouse_y + y < -1 * (MOUSE_WINDOW_SIZE)) {
            continue;
        }
        TrinketHidCombo.mouseMove(x, y, 0);
        global_mouse_x += x;
        global_mouse_y += y;
        delay(10);
    }

    int rnd;
    rnd = get_rand(100);
    if (rnd >= 90) {
        TrinketHidCombo.mouseMove(0, 0, 1);
        delay(10);
        TrinketHidCombo.mouseMove(0, 0, 0);
        int action_delay;
        action_delay = get_rand(100);
        delay_with_poll(action_delay);
        TrinketHidCombo.pressKey(0, KEYCODE_END);
        delay(10);
        TrinketHidCombo.print(" ");
    }
}

void keyboard_action() {

    int rnd;
    rnd = get_rand(100);
    if (rnd >= 90) {
        TrinketHidCombo.pressKey(0, KEYCODE_ENTER);
        need_upper = 1;
    }

    int word_length;
    int i;
    word_length = get_rand(15) + 1;
    char c[2];
    c[1] = '\0';

    int numbers_mode;
    rnd = get_rand(100);
    if (rnd >= 90) {
        numbers_mode = 1;
    } else {
        numbers_mode = 0;
    }

    for (i = 0; i < word_length; i++) {
        if (numbers_mode) {
            c[0] = nums[get_rand(NUMS_LEN)];
            need_upper = 0;
        } else {
            if (i == 0) {
                rnd = get_rand(100);
                if (rnd >= 90 || need_upper) {
                    c[0] = uppers[get_rand(UPPERS_LEN)];
                    need_upper = 0;
                } else {
                    c[0] = lowers[get_rand(LOWERS_LEN)];
                }
            } else {
                c[0] = lowers[get_rand(LOWERS_LEN)];
            }
        }
        TrinketHidCombo.print(c);

        int enter_sleep;
        enter_sleep = 30 + get_rand(200);
        delay_with_poll(enter_sleep);
    }

    rnd = get_rand(100);
    if (rnd >= 90) {
        c[0] = special[get_rand(SPECIAL_LEN)];
        TrinketHidCombo.print(c);
        if (c[0] == '.' || c[0] == '?' || c[0] == '!') {
            need_upper = 1;
        }

        int enter_sleep;
        enter_sleep = 30 + get_rand(100);
        delay_with_poll(enter_sleep);
    }

    TrinketHidCombo.print(" ");
}

void delay_with_poll(int delay_ms) {
    int count;
    int i;
    count = delay_ms / 10;
    for (i = 0; i < count; i++) {
        delay(10);
        TrinketHidCombo.poll();
    }
}

int get_rand(int max_excluded) {
    return (rand() ^ analogRead(5)) % max_excluded;
}

char get_rand_chr(int max_excluded) {
    return (char)(get_rand(max_excluded));
}

void update_srand() {
    int low = EEPROM.read(SRAND_LOW);
    int high = EEPROM.read(SRAND_HIGH);
    int loaded = word(high, low);
    last_srand ^= loaded;
    //last_srand ^= (int)(timing_diff);
    loaded = analogRead(5);
    low = lowByte(last_srand);
    high = highByte(last_srand);
    EEPROM.write(SRAND_LOW, low);
    EEPROM.write(SRAND_HIGH, high);
}
