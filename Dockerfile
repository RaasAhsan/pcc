FROM gcc:9.1
COPY . /usr/src/pcc
WORKDIR /usr/src/pcc
RUN ./compile.sh
CMD ["./a.out"]