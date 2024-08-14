FROM debian:bookworm

WORKDIR /minishell

COPY ./ /minishell/

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    gdb \
    make \
    libc-dev \
    vim \
    git \
    pkg-config \
    cmake \
    autoconf \
    automake \
    valgrind \
    libreadline-dev

CMD [ "sh", "-c", "make fclean && make && ./minishell" ]