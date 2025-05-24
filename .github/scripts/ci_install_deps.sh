#!/bin/bash
set -e

echo "Installing CI dependencies..."

sudo apt-get update
sudo apt-get install -y cmake g++ ninja-build

echo "CI dependencies installed."
