class MeshBuilder
{
	private readonly ID:string;
	private meshes:Array<BABYLON.Mesh>;
	private nbClones:number = 0;
	private onLoad:Function;

	constructor(modelName:string, scene:BABYLON.Scene, onLoad:Function = undefined)
	{
		this.ID = modelName;
		this.onLoad = onLoad;
		BABYLON.SceneLoader.ImportMesh("", "/assets/", modelName, scene, this.load);
	}

	private load = (meshes:Array<BABYLON.Mesh>):void =>
	{
		this.meshes = meshes;
		for (let i:number = this.meshes.length - 1; i >= 0; i--) {
			this.meshes[i].scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
			this.meshes[i].position.y = 0.5;
			this.meshes[i].isVisible = false;
		}
		if (this.onLoad)
			this.onLoad();
	}

	public getInstance():BerkMesh
	{
		let meshes:Array<BABYLON.InstancedMesh> = new Array<BABYLON.InstancedMesh>();

		for (let i:number = this.meshes.length - 1; i >= 0; i--) {
			meshes.push(this.meshes[i].createInstance(this.ID + this.nbClones + "-" + i));
		}
		this.nbClones++;
		return (new BerkMesh(meshes));
	}
}