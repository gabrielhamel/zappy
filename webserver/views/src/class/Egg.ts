class Egg
{
	private readonly EGG:MeshBuilder;
	private id:number;
	private x:number;
	private y:number;
	private teamName:string;
	private maturity:boolean = false;

	constructor(id: number, x:number, y:number, teamName:string, scene:BABYLON.Scene)
	{
		this.x = x;
		this.y = y;
		this.teamName = teamName;
		this.EGG = new MeshBuilder("chungus.glb", scene);
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
