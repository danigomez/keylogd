//
// Created by dgomez on 29/09/17.
//

#include "keyboard.h"
#include "../utils.h"

#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <cstring>
#include <string>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>


Keyboard::Keyboard() {
    std::string event = this->get_event_device();

    std::string device = "/dev/input/";
    device.append(event);

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

std::string Keyboard::get_event_device() {

    try {

        std::string result = exec("grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event[0-9]+'");
        return result;

    } catch (std::runtime_error &s) {
        syslog(LOG_ERR, "There was an error while getting event device");
        exit(EXIT_FAILURE);
    }


}

uint8_t* Keyboard::get_key_status() {
    static uint8_t keys[KEY_MAX];
    ioctl (this->keyboard_fd, EVIOCGKEY(sizeof keys), &keys);
    return keys;
}
