#!/bin/bash
# Install script

if [ "$EUID" -ne 0 ]; then 
    echo "error: user must be root."
    exit
fi

echo 'Copying prochotctl -> /usr/bin/prochotctl'
cp ./prochotctl /usr/bin
echo Install complete!