FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y cmake \
    libgtest-dev \
    build-essential \
    g++-10 \
    git

WORKDIR  /app

COPY . /app/

CMD tail -f /dev/null
