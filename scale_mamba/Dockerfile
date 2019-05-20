FROM alpine:latest
RUN apk update && apk add --update git build-base

RUN mkdir /src
WORKDIR /src

RUN git clone https://github.com/KULeuven-COSIC/SCALE-MAMBA.git

# Installing MPIR
RUN apk add curl
RUN apk add yasm
RUN apk add m4

RUN mkdir -p /src/local
WORKDIR /src/local
RUN curl -O http://mpir.org/mpir-3.0.0.tar.bz2
RUN tar xf mpir-3.0.0.tar.bz2
WORKDIR /src/local/mpir-3.0.0
RUN ./configure --enable-cxx --prefix="/src/local/mpir"
RUN make
RUN make check
RUN make install

# Installing OpenSSL
RUN apk add perl
RUN apk add linux-headers
RUN apk add libexecinfo-dev

WORKDIR /src/local
RUN git clone https://github.com/weidai11/cryptopp.git
WORKDIR /src/local/cryptopp
RUN make
RUN make test
RUN make install

WORKDIR /src/local
RUN curl -O https://www.openssl.org/source/openssl-1.1.0j.tar.gz
RUN tar -xf openssl-1.1.0j.tar.gz
WORKDIR /src/local/openssl-1.1.0j
RUN ./config --prefix="/src/local/openssl"
RUN make
RUN make install

# Export OpenSSL paths
ENV PATH="/src/local/openssl/bin/:${PATH}"
ENV C_INCLUDE_PATH="/src/local/openssl/include/:${C_INCLUDE_PATH}"
ENV CPLUS_INCLUDE_PATH="/src/local/openssl/include/:${CPLUS_INCLUDE_PATH}"
ENV LIBRARY_PATH="/src/local/openssl/lib/:${LIBRARY_PATH}"
ENV LD_LIBRARY_PATH="/src/local/openssl/lib/:${LD_LIBRARY_PATH}"
# Export MPIR paths
ENV PATH="/src/local/mpir/bin/:${PATH}"
ENV tC_INCLUDE_PATH="/src/local/mpir/include/:${C_INCLUDE_PATH}"
ENV CPLUS_INCLUDE_PATH="/src/local/mpir/include/:${CPLUS_INCLUDE_PATH}"
ENV LIBRARY_PATH="/src/local/mpir/lib/:${LIBRARY_PATH}"
ENV LD_LIBRARY_PATH="/src/local/mpir/lib/:${LD_LIBRARY_PATH}"

# Configure
WORKDIR /src/SCALE-MAMBA
RUN cp CONFIG CONFIG.mine
RUN echo "ROOT = /src/SCALE-MAMBA" >> CONFIG.mine
RUN echo "OSSL = /src/local/openssl" >> CONFIG.mine

# Optional changes to compile flags
# Optional changes to config.h

RUN make progs
RUN apk add python

# Section 3.4 Idiot's Installation
RUN cp Auto-Test-Data/Cert-Store/* Cert-Store/
RUN cp Auto-Test-Data/1/* Data/

#
# BUILD: docker build -t scale-mamba -f Dockerfile .
# RUN: docker run --rm -it scale-mamba
#
#./compile.py Programs/tutorial
#./Player.x 0 Programs/tutorial &
#./Player.x 1 Programs/tutorial &
#./Player.x 2 Programs/tutorial &

