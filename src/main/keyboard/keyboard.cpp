//
// Created by dgomez on 29/09/17.
//

#include "keyboard.h"
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <cstring>
#include <string>
#include <cerrno>
#include <cstdlib>

Keyboard::Keyboard() {
    const char* eventName = this->get_event_device();
    std::string device = "/dev/input/";
    device.append(eventName);

    int fd = open(device.c_str(), O_RDONLY);

    if (fd != -1) {
        this->keyboard_fd = fd;
        syslog(LOG_NOTICE, "Opened device %s, fd=%d", device.c_str(), fd);

    } else {
        syslog(LOG_ERR, "There was and error while opening device %s, %s", device.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
}

Keyboard::~Keyboard() {
    int result = close(this->keyboard_fd);

    if (result == -1) {
        syslog(LOG_ERR, "There was an error while closing keyboard descriptor %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

const char* Keyboard::get_event_device() {
    return "event4";
}

uint8_t* Keyboard::get_key_status() {
    static uint8_t keys[KEY_MAX];
    ioctl (this->keyboard_fd, EVIOCGKEY(sizeof keys), &keys);
    return keys;
}
