FROM gcc:latest

# Install dependencies
RUN apt update
RUN apt -y install cmake

# Install vcpkg
WORKDIR /usr
RUN git clone https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ln -s /usr/vcpkg/vcpkg /usr/bin/vcpkg

# Clone repository
WORKDIR /cppeng
RUN git clone https://github.com/cppengineer/video-detect.git

# Build project and run tests
CMD /cppeng/video-detect/bootstrap-tests.sh