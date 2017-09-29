//
// Created by dgomez on 28/09/17.
//

#ifndef KEYLOGD_DAEMON_H
#define KEYLOGD_DAEMON_H

class Daemon {
public:
    void start(); // Start the daemon, initialize it and run the defined process

protected:
    virtual void process() = 0; // Defines daemon functionality
    virtual const char* get_daemon_name() = 0;
    void initialize(); // Initialize Daemon process
private:
    void start_logs();
    void fork_process();
    void start_session();

};

#endif //KEYLOGD_DAEMON_H
