FROM gcc:latest

# Install dependencies
RUN apt update
RUN apt -y install zip
RUN apt -y install nasm
RUN apt -y install cmake

# Install vcpkg
WORKDIR /usr
RUN git clone https://github.com/Microsoft/vcpkg.git
RUN /usr/vcpkg/vcpkg/bootstrap-vcpkg.sh
RUN /usr/vcpkg/vcpkg integrate install
RUN ln -s /usr/vcpkg/vcpkg /usr/bin/vcpkg

# Clone repository
WORKDIR /cppeng
RUN git clone https://github.com/cppengineer/video-detect.git

# TEMPORARY
WORKDIR /cppeng/video-detect
RUN git checkout origin/development/main

# Build project and run tests
RUN /cppeng/video-detect/bootstrap.sh

# Run
CMD /cppeng/video-detect/build/bin/video-detect