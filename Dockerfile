FROM gcc:latest

# Install dependencies
RUN apt-get update
RUN apt-get -y install cmake

# Install FFMPEG dependencies
RUN apt-get -y install libavcodec-dev
RUN apt-get -y install libavformat-dev
RUN apt-get -y install libavutil-dev
RUN apt-get -y install libswscale-dev

# Install OpenCV dependencies
RUN apt-get -y install libopencv-dev

# Install GoogleTest dependencies
RUN apt-get -y install libgtest-dev
RUN apt-get -y install libgmock-dev

# Install code quality dependencies
RUN apt-get -y install pip
RUN pip install cpplint

# Install development dependencies
RUN apt-get -y install clang-format
RUN apt-get -y install gdb

# Copy all files in repository into image
WORKDIR /cppeng/video-detect
COPY . .

# Build project and run tests
WORKDIR /cppeng/video-detect/build
RUN cmake -DBUILD_TESTS=ON -DCHECK_STYLES=ON -DCMAKE_BUILD_TYPE=Release ..
RUN make
RUN make test

# Run
CMD /cppeng/video-detect/build/bin/video-detect
