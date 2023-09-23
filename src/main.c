/*
prochotctl v1.0. Copyright (C) GustavoFringGaming 2023.

Purpose:
    This program allows the user to toggle the BD_PROCHOT signal.
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PRGM_VERSION "v1.0"
#define PROCHOT_MSR 0x1FC
#define PROCHOT_ON 0x4005D
#define PROCHOT_OFF 0x4005C

// Controls the cpu prochot msr
void prochot_ctl(int state) {
    // Preliminary: get number of cpus
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

    // Write msr for each cpu
    for(int i = 0; i < number_of_processors; i++) {
        char fn[64];
        sprintf(fn, "/dev/cpu/%d/msr", i);
        int fd = open(fn, O_WRONLY);

        // Write MSR
        uint64_t data;

        if(state == 0) // Turn off
            data = PROCHOT_OFF;
        else // Turn on
            data = PROCHOT_ON;

        // Write msr and complain if it didn't work
        if(pwrite(fd, &data, sizeof data, PROCHOT_MSR) != sizeof(data)) {
            fprintf(stderr, "error: could not write MSR!\n");
            close(fd);
            exit(1);
        }

        close(fd);
    }
}

// Program entry point
int main(int argc, char*argv[]) {
    // Check if we are root
    if(geteuid() != 0) {
        fprintf(stderr, "error: this program must be ran as root.\n");
        return 1;
    }

    // Return usage if no arguments are provided
    if(argc < 2) {
        printf("prochotctl %s.\nUsage: %s <on/off>\n", PRGM_VERSION, argv[0]);
        printf("Small utility to toggle the BD_PROCHOT CPU signal.\n\n");
        return 1;
    }

    // Parse arguments
    if(strncmp(argv[1], "on", 2) == 0) {
        prochot_ctl(1);
        printf("%s\n", "PROCHOT enabled.");
    } else if(strncmp(argv[1], "off", 3) == 0) {
        prochot_ctl(0);
        printf("%s\n", "PROCHOT disabled.");
    } else {
        fprintf(stderr, "error: unknown option \"%s\".\n", argv[1]);
        return 1;
    }

    return 0;
}