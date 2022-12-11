FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive
ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
    apt-get install -y cmake \
    libgtest-dev \
    libgmock-dev \
    build-essential \
    g++-9 \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR  /app

COPY . /app/

ENTRYPOINT ["bash"]
