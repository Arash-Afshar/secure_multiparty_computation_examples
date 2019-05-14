FROM alpine:latest AS BASE
RUN apk update && apk add --update git build-base cmake linux-headers

RUN mkdir /src
WORKDIR /src

RUN git clone --recursive https://github.com/osu-crypto/libOTe.git
WORKDIR /src/libOTe/cryptoTools/thirdparty/linux
RUN sh boost.get
RUN apk add --update bash
RUN sh miracl.get


WORKDIR /src/libOTe
RUN cmake . -DENABLE_MIRACL=ON
RUN make

RUN mkdir -p /src/libOTe/weather_ot_user
RUN mkdir -p /src/libOTe/weather_ot_server
COPY user /src/libOTe/weather_ot_user
COPY server /src/libOTe/weather_ot_server
RUN echo "add_subdirectory(weather_ot_user)" >> /src/libOTe/CMakeLists.txt
RUN echo "add_subdirectory(weather_ot_server)" >> /src/libOTe/CMakeLists.txt

RUN cmake . -DENABLE_MIRACL=ON
RUN make