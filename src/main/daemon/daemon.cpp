//
// Created by dgomez on 28/09/17.
//

#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#include <syslog.h>
#include "daemon.h"

void Daemon::start_logs() {
    // Set log level
    setlogmask(LOG_UPTO(LOG_NOTICE));

    // Logs PID with no delay, and identity the log as sys daemon
    openlog(this->get_daemon_name(),  LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
}

void Daemon::start_session()  {

    pid_t sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

}

void Daemon::fork_process() {

    pid_t pid = fork(); // Fork process

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
}

void Daemon::initialize() {

    this->fork_process();

    // Reset umask (bitmask to change file permissions)
    // this allows that the process can access any file created
    umask(0);

    this->start_logs();

    this->start_session();

    // Change pwd to root
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    syslog(LOG_NOTICE, "Started %s daemon.", this->get_daemon_name());

}

void Daemon::start() {

    this->initialize();
    this->process();
    closelog();
}
