class Player
{
	private readonly CHUNGUS:MeshBuilder;
	private id:number;
	private x:number;
	private y:number;
	private o:number;
	private lvl:number;
	private teamName:string; // peut à remplacer vers une reference de team ou OSEF en vrai

	constructor(scene:BABYLON.Scene)
	{
		this.CHUNGUS = new MeshBuilder("chungus.glb", scene);
	}
	public setPos(x:number, y:number)
	{
		this.x = x;
		this.y = y;
	}
	public setOri(o:number)
	{
		this.o = o;
	}
	public setLvl(lvl:number)
	{
		this.lvl = lvl;
	}
}
