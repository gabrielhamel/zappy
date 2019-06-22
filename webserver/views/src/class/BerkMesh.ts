class BerkMesh
{
	private readonly MESHES:Array<BABYLON.InstancedMesh>;

	constructor(meshes:Array<BABYLON.InstancedMesh>)
	{
		this.MESHES = meshes;
	}

	public setPosition(position:BABYLON.Vector3)
	{
		for (let i:number = this.MESHES.length - 1; i >= 0; i--)
			this.MESHES[i].position = position;
	}
	public setRotation(angle:number)
	{
		for (let i:number = this.MESHES.length - 1; i >= 0; i--)
			this.MESHES[i].rotation.y = angle;
	}
	public dispose()
	{
		for (let i:number = this.MESHES.length - 1; i >= 0; i--)
			this.MESHES[i].dispose();
	}
}
