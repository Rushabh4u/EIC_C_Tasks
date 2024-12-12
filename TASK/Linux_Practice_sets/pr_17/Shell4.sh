#!/bin/bash

# Load the configuration file
source ./config.cfg

# Logging function
log() {
    if [ "$LOGGING" = true ]; then
        echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> "$LOG_FILE"
    fi
}

# Example actions in the script
do_something() {
    log "Starting the do_something function."
    # Simulate some work
    sleep 1
    log "Finished the do_something function."
}

do_another_thing() {
    log "Starting the do_another_thing function."
    # Simulate some work
    sleep 1
    log "Finished the do_another_thing function."
}

# Main script execution
log "Script execution started."
do_something
do_another_thing
log "Script execution finished."

