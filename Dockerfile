FROM gcc:latest

# Install dependencies
RUN apt update
RUN apt -y install cmake
RUN apt -y install zip
RUN apt -y install nasm

# Install vcpkg
WORKDIR /usr
RUN git clone https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ln -s /usr/vcpkg/vcpkg /usr/bin/vcpkg

# Clone repository
WORKDIR /cppeng
RUN git clone https://github.com/cppengineer/video-detect.git

# Build project and run tests
RUN /cppeng/video-detect/bootstrap.sh

# Run
RUN /cppeng/video-detect/build/bin/video-detect