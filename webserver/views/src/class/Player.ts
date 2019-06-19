class Player
{
	private readonly CHUNGUS:MeshBuilder;
	private id:number;
	private x:number;
	private y:number;
	private o:number;
	private lvl:number;
	private teamName:string; // peut à remplacer vers une reference de team ou OSEF en vrai
	private bag:Array<number> = new Array<number>();
	private message: string = "";
	private incanting: boolean = false;

	constructor(scene:BABYLON.Scene)
	{
		this.CHUNGUS = new MeshBuilder("chungus.glb", scene);
		for (let i:number = 0; i < 7; i++)
			this.bag.push(0);
	}

	public setPos(x:number, y:number):void
	{
		this.x = x;
		this.y = y;
	}
	public setOri(o:number):void
	{
		this.o = o;
	}
	public setLvl(lvl:number):void
	{
		this.lvl = lvl;
	}
	public setBag(food:number, linemate:number, deraumere:number, sibur:number, mendiane:number, phiras:number, thystame:number):void
	{
		this.bag[0] = food;
		this.bag[1] = linemate;
		this.bag[2] = deraumere;
		this.bag[3] = sibur;
		this.bag[4] = mendiane;
		this.bag[5] = phiras;
		this.bag[6] = thystame;
	}
	public setMessage(message:string):void
	{
		this.message = message;
	}
	public getId():number
	{
		return (this.id);
	}
	public getX():number
	{
		return (this.id);
	}
	public getY():number
	{
		return (this.id);
	}
	public getTeamName():string
	{
		return (this.teamName);
	}
	public drop(item:number):void
	{
		this.bag[item]--;
	}
}
