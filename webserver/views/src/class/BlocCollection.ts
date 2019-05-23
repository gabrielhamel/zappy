class BlocCollection
{
	public static readonly ID_STRING:string = "blocInstance";
	private static readonly TYPE_COLORS:Array<BABYLON.Color3> = [
		new BABYLON.Color3(0, 0.6, 0),
	];
	private static readonly HEIGHTS:Array<number> = [0.05];
	private static createdInstances:number = 0;
	private blocs:Array<BABYLON.Mesh> = new Array<BABYLON.Mesh>();

	constructor(scene:BABYLON.Scene)
	{
		let cur:BABYLON.Mesh;
		let material:BABYLON.StandardMaterial;
		let id:number;
	
		for (let i:number = 0, len = BlocCollection.TYPE_COLORS.length; i < len; i++) {
			id = this.blocs.length;
			cur = BABYLON.MeshBuilder.CreateBox("originalBloc" + id, {size: 1}, scene);
			material = new BABYLON.StandardMaterial("blocMaterial" + id, scene);
			material.diffuseColor = BlocCollection.TYPE_COLORS[i];
			cur.material = material;
			cur.isVisible = false;
			this.blocs.push(cur);
		}
	}

	public getInstance = (type:number):BABYLON.InstancedMesh =>
	{
		let id:string = BlocCollection.ID_STRING + BlocCollection.createdInstances;
		let output:BABYLON.InstancedMesh;
		
		BlocCollection.createdInstances++;
		output = this.blocs[type].createInstance(id);
		output.position.y = BlocCollection.HEIGHTS[type];
		output.isVisible = true;
		return (output);
	}
}