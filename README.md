## Zappy is a game where AI evolves by eating food and level up by using stones
### You can read **Game.pdf** and **Graphical Protcol.pdf** to understand the project

## Play on [zappy.gcoding.fr](https://zappy.gcoding.fr)
#### If you want to connect one IA or make your own IA, connect you in tcp at zappy.gcoding.fr:3000
#### Teams avaibles: "team1", "team2"

# IA
## Build
```bash
make zappy_ai
```
## Connect to the server
```bash
./zappy_ai -h <hostname> -p <port> -n <team>
# eg. ./zappy_ai -h zappy.gcoding.fr -p 3000 -n team1
```

# Server
## Build
```bash
make zappy_server
```
## Launch
```bash
./zappy_server -p <port> -x <width> -y <height> -n <team-name> ... -c <max-player-in-team> -f <speed>
# eg. ./zappy_server -p 3000 -f 20 -x 30 -y 30 -n team1 team2 -c 5
```
or
```bash
export ZPY_PORT=8080
export ZPY_WIDTH=20
export ZPY_HEIGHT=20
export ZPY_SPEED=10
export ZPY_NB_CLIENT_TEAM_MAX=5
export ZPY_TEAM_NAMES=Blue:Red:Yellow:Green

./zappy_server
```
# Unit tests
## Build & execute
The build needs [criterion](https://github.com/Snaipe/Criterion) library
```bash
make tests_run
```
You can see the coverage in the report stored in **tests/html/index.html**

# Documentation
The generation needs **doxygen** and **graphviz** commands
```bash
make documentation
```

You can consult Ia documentation in **doc_ia/html/index.html** and the Server documentation in **doc_server/html/index.html**

# Deployment
### There are a graphical webview. There are a relay in socket.io between the game server and the webview to avoid TCP connection in web. To see all deployment you can check all **Dockerfile**
