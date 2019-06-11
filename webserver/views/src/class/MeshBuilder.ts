class MeshBuilder
{
	private readonly ID:string;
	private mesh:BABYLON.Mesh;
	private nbClones:number = 0;

	constructor(modelName:string, scene:BABYLON.Scene)
	{
		this.ID = modelName;
		BABYLON.SceneLoader.ImportMesh("", "/assets/", modelName, scene, this.load);
	}

	private load = (meshes:Array<BABYLON.Mesh>) =>
	{
		this.mesh = meshes[0];
		this.mesh.scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
		this.mesh.position.y = 0.5;
		this.mesh.isVisible = false;
	}

	public getInstance():BABYLON.AbstractMesh
	{
		let output:BABYLON.AbstractMesh;

		output = this.mesh.createInstance(this.ID + this.nbClones);
		output.isVisible = true;
		this.nbClones++;
		return (output);
	}
}