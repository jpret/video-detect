FROM gcc:latest

# Install dependencies
RUN apt update
RUN apt -y install cmake

# Install FFMPEG dependencies
RUN apt -y install libavcodec-dev
RUN apt -y install libavformat-dev
RUN apt -y install libavutil-dev
RUN apt -y install libswscale-dev

# Install OpenCV dependencies
RUN apt -y install libopencv-dev

# Install GoogleTest dependencies
RUN apt -y install libgtest-dev
RUN apt -y install libgmock-dev

# Clone repository
WORKDIR /cppeng
RUN git clone https://github.com/cppengineer/video-detect.git

# TEMPORARY
WORKDIR /cppeng/video-detect
RUN git checkout origin/development/main

# Build project and run tests
WORKDIR /cppeng/video-detect/build
RUN cmake -DBUILD_TESTS=ON ..
RUN make
RUN make test

# Run
CMD /cppeng/video-detect/build/bin/video-detect