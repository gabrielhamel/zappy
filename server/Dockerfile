FROM gcc:9.2.0
WORKDIR /usr/src/zappy
COPY . server/
COPY Makefile .
RUN make zappy_server
CMD ["./zappy_server", "-p", "8080", "-x", "30", "-y", "30", "-n", "team1", "team2", "-c", "2", "-f", "1"]
