# Use an official Ubuntu image as a parent image
FROM ubuntu:latest

# Update and install gcc, g++, make, and valgrind
RUN apt-get update && apt-get install -y \
    libx11-dev \
    libxext-dev \
    zlib1g-dev \
    libbsd-dev \
    git \
    gcc \
    g++ \
    make \
    valgrind

# Set the working directory in the container to /app
WORKDIR /app

# Copy the application code to the container
COPY . /app

# Build MiniLibX
WORKDIR /app/includes/minilibx-linux
RUN make

# Build your application
WORKDIR /app
RUN make

# Start a shell when the Docker container runs
CMD ["/bin/bash"]
