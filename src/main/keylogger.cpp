//
// Created by dgomez on 28/09/17.
//

#include "keylogger.h"
#include <syslog.h>
#include <unistd.h>

void Keylogger::process() {
    while (true) {
        syslog(LOG_NOTICE, "This this a test");
        sleep(30);
    }
}

const char* Keylogger::get_daemon_name() {
    return "keylogd";
}