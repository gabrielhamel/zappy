class Team
{
	public readonly NAME:string;
	private players:Array<Player> = new Array<Player>();

	constructor(name:string)
	{
		this.NAME = name;
	}

	public addPlayer(player:Player)
	{
		this.players.push(player);
	}
}