class SocketManager
{
	private socket = io();
	private game:Game;
	
	constructor(game:Game)
	{
		this.game = game;
		this.socket.emit("data", "GRAPHICAL");
	}
}