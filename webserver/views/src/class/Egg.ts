class Egg
{
	private readonly EGG:MeshBuilder;
	private id:number;
	private x:number;
	private y:number;
	private teamName:string; // peut à remplacer vers une reference de team ou OSEF en vrai

	constructor(x:number, y:number, teamName:string, scene:BABYLON.Scene)
	{
		this.x = x;
		this.y = y;
		this.teamName = teamName;
		this.EGG = new MeshBuilder("chungus.glb", scene);
	}

	public getId():number
	{
		return (this.id);
	}
}
