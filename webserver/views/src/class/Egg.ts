class Egg
{
	private skin:BerkMesh;
	private id:number;
	private x:number;
	private y:number;
	private teamName:string;
	private maturity:boolean = false;

	constructor(id: number, x:number, y:number, teamName:string, skin:BerkMesh, scene:BABYLON.Scene)
	{
		this.x = x;
		this.y = y;
		this.teamName = teamName;
		this.skin = skin;
		this.skin.setPosition(new BABYLON.Vector3(x, 0.5, y));
	}

	public setMaturity(maturity:boolean):void
	{
		this.maturity = maturity;
	}
	public getId():number
	{
		return (this.id);
	}
	public getMaturity():boolean
	{
		return (this.maturity);
	}
}
