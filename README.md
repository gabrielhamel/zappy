# zappy
Build:
  server and ia: "make"
  documentation: "make documentation"
 Launch
  server: ./zappy_server -p <port> -x <map-width> -y <map-height> -n <team-name1> ... -c <max-player-in-team> -f <server-speed>
    example: ./zappy_server -p 8080 -x 30 -y 30 -n team1 team2 -c 2 -f 7
