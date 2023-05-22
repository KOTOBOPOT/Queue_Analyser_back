# Base image
FROM ubuntu:latest

# Prevents prompts from apt during build
ARG DEBIAN_FRONTEND=noninteractive

# Update and install dependencies
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    build-essential \
    git \
    cmake \
    libsqlite3-dev \
    libboost-all-dev \
    libgtest-dev \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    python3-opencv \
    libopencv-dev && rm -rf /var/lib/apt/lists/*

# Copy project files
WORKDIR /app
COPY . /app

# Build the project
RUN mkdir build && cd build && cmake .. && make

# Set the entry point
CMD ["./build/queueAnalyser"]
