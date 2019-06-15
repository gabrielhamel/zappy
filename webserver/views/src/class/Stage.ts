class Stage
{
	private readonly CANVAS:HTMLCanvasElement;
	private readonly CHUNGUS:MeshBuilder;
	private readonly SCENE:BABYLON.Scene;
	private blocs:Array<BABYLON.InstancedMesh> = new Array<BABYLON.InstancedMesh>();
	private blocCollection:BlocCollection;
	private infobox:Infobox = new Infobox();
	private light:BABYLON.HemisphericLight;
	private selected:BABYLON.AbstractMesh;
	private tiles:Array<Tile> = new Array<Tile>();

	constructor(scene:BABYLON.Scene)
	{
		let lightDir = new BABYLON.Vector3(0, 1, 0);

		this.CHUNGUS = new MeshBuilder("chungus.glb", scene);
		this.CANVAS = scene.getEngine().getRenderingCanvas();
		this.SCENE = scene;
		this.blocCollection = new BlocCollection(scene);

		this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
		this.light.diffuse = new BABYLON.Color3(1, 1, 1);
		this.light.specular = new BABYLON.Color3(0, 0, 0);

		this.CANVAS.addEventListener("pointerdown", this.onPointerDown);
	}

	private onPointerDown = (event:PointerEvent):void =>
	{
		let picked:BABYLON.PickingInfo = this.SCENE.pick(event.clientX, event.clientY);
		let pos:BABYLON.Vector3;
		let tile:Tile;

		if (!picked || !picked.hit)
			return;
		pos = picked.pickedMesh.position;
		picked.pickedMesh.position.y -= 0.1;
		tile = this.findTileByPosition(new BABYLON.Vector2(pos.x, pos.z));
		if (tile)
			this.infobox.updateTile(tile);
		if (this.selected)
			this.selected.position.y += 0.1;
		this.selected = picked.pickedMesh;
	}
	private findTileByPosition(position:BABYLON.Vector2):Tile
	{
		return (this.tiles.find((tile:Tile) => {
			return (position.equals(tile.getPosition()));
		}));
	}

	public addTile(datas:Array<string>)
	{
		let tile:Tile;
		let stats:Array<number> = new Array<number>();
		let index:number;

		if (this.updateTile(datas))
			return;
		for (let i:number = 3; i < datas.length; i++) {
			stats.push(parseInt(datas[i]));
		}
		tile = new Tile(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], this.SCENE);
		tile.initialise(parseInt(datas[1]), parseInt(datas[2]));
		tile.startAnimations(this.SCENE);
		this.tiles.push(tile);
	}
	public createGround(width:number, height:number):void
	{
		let cur:BABYLON.InstancedMesh;

		for (let i:number = width - 1; i >= 0; i--) {
			for (let j:number = height - 1; j >= 0; j--) {
				cur = this.blocCollection.getInstance(0);
				cur.position.x = i;
				cur.position.z = j;
				this.blocs.push(cur);
			}
		}
	}
	public updateTile(datas:Array<string>):boolean
	{
		let position:BABYLON.Vector2 = new BABYLON.Vector2(parseInt(datas[1]), parseInt(datas[2]));
		let stats:Array<number> = new Array<number>();
		let tile:Tile;

		tile = this.tiles.find((tile:Tile) => {
			return (position.equals(tile.getPosition()));
		});
		if (!tile)
			return (false);
		for (let i:number = 3; i < datas.length; i++) {
			stats.push(parseInt(datas[i]));
		}
		tile.update(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6]);
		return (true);
	}
	public render():void
	{

	}
}