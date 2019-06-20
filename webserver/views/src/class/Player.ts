class Player
{
	private skin:BABYLON.AbstractMesh;
	private id:number;
	private x:number;
	private y:number;
	private o:number;
	private lvl:number;
	private teamName:string; // peut à remplacer vers une reference de team ou OSEF en vrai
	private bag:Array<number> = new Array<number>();
	private message: string = "";
	private incanting: boolean = false;
	private laying: boolean = false;


	constructor(id:number, teamName:string, skin:BABYLON.AbstractMesh, scene:BABYLON.Scene)
	{
		this.id = id;
		this.teamName = teamName;
		this.skin = skin;
		for (let i:number = 0; i < 7; i++)
			this.bag.push(0);
	}

	public setPos(x:number, y:number):void
	{
		this.x = x;
		this.y = y;
		this.skin.position = new BABYLON.Vector3(x, 0.5, y);
	}
	public setOri(o:number):void
	{
		this.o = o;
		this.skin.rotation.y = Math.PI / 2 * (o - 1);
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
	public setLayingState(state:boolean):void
	{
		this.laying = state;
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
	public isLaying():boolean
	{
		return (this.laying);
	}
	public drop(item:number):void
	{
		this.bag[item]--;
	}
	public take(item:number):void
	{
		this.bag[item]--;
	}
}
