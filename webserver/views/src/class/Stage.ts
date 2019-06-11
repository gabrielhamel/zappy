class Stage
{
	private selectedObject:BABYLON.AbstractMesh;
	private canvas:HTMLCanvasElement;
	private light:BABYLON.HemisphericLight;
	private scene:BABYLON.Scene;
	private blocs:Array<BABYLON.InstancedMesh> = new Array<BABYLON.InstancedMesh>();
	private socketManager:SocketManager;
	private blocCollection:BlocCollection;
	private model:BABYLON.AbstractMesh;
	private tiles:Array<Tile> = new Array<Tile>();

	constructor(socketManager:SocketManager, scene:BABYLON.Scene)
	{
		let lightDir = new BABYLON.Vector3(0, 1, 0);

		this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
		this.scene = scene;
		this.canvas = scene.getEngine().getRenderingCanvas();
		this.socketManager = socketManager;
		this.blocCollection = new BlocCollection(scene);

		this.light.diffuse = new BABYLON.Color3(1, 1, 1);
		this.light.specular = new BABYLON.Color3(0, 0, 0);

		BABYLON.SceneLoader.LoadAssetContainer("/assets/", "chungus.glb", scene, (container:BABYLON.AssetContainer) =>
		{
			this.model = container.meshes[0];
			this.model.scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
			this.model.position.y = 0.5;
			container.addAllToScene();
		});
		window.addEventListener("pointerdown", this.onPointerDown);
	}

	private onPointerDown = (event:PointerEvent):void =>
	{
		let picked:BABYLON.PickingInfo = this.scene.pick(event.clientX, event.clientY);
	}

	public addTile(datas:Array<string>)
	{
		const cur:number = this.tiles.length;
		let tile:Tile;
		let stats:Array<number> = new Array<number>();

		for (let i:number = 3; i < datas.length; i++) {
			stats.push(parseInt(datas[i]));
		}
		tile = new Tile(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], this.scene);
		tile.initialise(cur % Game.size.x, ~~(cur / Game.size.x));
		this.tiles.push(tile);
	}
	public createGround(width:number, height:number):void
	{
		let cur:BABYLON.InstancedMesh;

		for (let i:number = width; i >= 0; i--) {
			for (let j:number = height; j >= 0; j--) {
				cur = this.blocCollection.getInstance(0);
				cur.position.x = i;
				cur.position.z = j;
				this.blocs.push(cur);
			}
		}
	}
	public render():void
	{

	}
}