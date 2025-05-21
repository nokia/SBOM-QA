#!/bin/bash

set -e

# Check if the script is run as root
if [[ $EUID -ne 0 ]]; then
    echo "This script requires sudo privileges. Restarting with sudo..."
    exec sudo "$0" "$@"
fi

apt update
apt-get -qq install -y --no-install-recommends \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    libqt6widgets6 \
    libqt6charts6 \
    libqt6charts6-dev \
    libqt6opengl6 \
    libqt6opengl6-dev \
    libxcb-xinerama0-dev \
    '^libxcb.*-dev' \
    libgles2-mesa-dev \
    libx11-xcb-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxrender-dev \
    libxi-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev
