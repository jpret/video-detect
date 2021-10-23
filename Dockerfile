FROM gcc:latest

# Install dependencies
RUN apt update
RUN apt -y install cmake

# Clone repository
WORKDIR /cppeng
RUN git clone https://github.com/cppengineer/video-detect.git

# Create a build directory
WORKDIR /cppeng/video-detect/build

# Invoke cmake and compile
RUN cmake ..
RUN make

# Run tests
CMD /cppeng/video-detect/build/src/video-detect