//
// Created by dgomez on 29/09/17.
//

#ifndef KEYLOGD_KEYBOARD_H
#define KEYLOGD_KEYBOARD_H

#include <cstdint>

class Keyboard {
public:
    Keyboard();
    ~Keyboard();

    uint8_t* get_key_status(); // Returns current keyboard status
private:
    const char* get_event_device(); // Returns the /dev/input/eventX name for the keyboard
    int keyboard_fd; // File descriptor for keyboard
};

#endif //KEYLOGD_KEYBOARD_H
