FROM ubuntu:20.04

RUN apt-get update
RUN DEBIAN_FRONTEND='noninteractive' apt-get install -y git gcc g++ cmake libcurl4-openssl-dev zlib1g zlib1g-dev libssl-dev zip

WORKDIR /usr/src
RUN git clone https://github.com/awslabs/aws-lambda-cpp.git
RUN mkdir aws-lambda-cpp/build
WORKDIR /usr/src/aws-lambda-cpp/build
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
RUN make && make install

WORKDIR /usr/src
RUN git clone https://github.com/aws/aws-sdk-cpp.git
RUN mkdir aws-sdk-cpp/build
WORKDIR /usr/src/aws-sdk-cpp/build
RUN cmake .. -DBUILD_SHARED_LIBS=OFF -DBUILD_ONLY="dynamodb"
RUN make && make install

WORKDIR /usr/src
RUN git clone https://github.com/open-source-parsers/jsoncpp.git
RUN mkdir jsoncpp/build
WORKDIR /usr/src/jsoncpp/build
RUN cmake .. -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF
RUN make && make install

WORKDIR /usr/src
RUN mkdir my-src
RUN echo "#!/bin/bash\ncd my-src/build && cmake .. && make && make aws-lambda-package-hello" > /entry.sh
RUN chmod +x /entry.sh

RUN gcc -v
RUN cmake -version

CMD /entry.sh