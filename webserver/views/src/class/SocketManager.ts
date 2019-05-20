class SocketManager
{
	public static readonly ADDRESS:string = "127.0.0.1";
	public static readonly PORT:number = 5555;
	private game:Game;
	
	constructor(game:Game)
	{
		this.game = game;
	}
}