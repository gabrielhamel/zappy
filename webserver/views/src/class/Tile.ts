class Tile
{
	private static nb:number = 0;
	private static spriteManager:BABYLON.SpriteManager = null;
	private stats:Map<string, number> = new Map<string, number>();
	private position:BABYLON.Vector2;

	constructor(food:number, linemate:number, deraumere:number, sibur:number, mendiane:number, phiras:number, thystame:number, scene:BABYLON.Scene)
	{
		this.stats.set("food", food);
		this.stats.set("linemate", linemate);
		this.stats.set("deraumere", deraumere);
		this.stats.set("sibur", sibur);
		this.stats.set("mendiane", mendiane);
		this.stats.set("phiras", phiras);
		this.stats.set("thystame", thystame);
		if (!Tile.spriteManager)
			Tile.spriteManager = new BABYLON.SpriteManager("spriteManager" + Tile.nb, "/assets/resources.png", 5000, 16, scene);
		Tile.nb++;
	}

	private generate(nb:number, type:number)
	{
		const ID:string = "tile" + Tile.nb + "-" + type;
		let sprite:BABYLON.Sprite;
	
		for (let i:number = 0; i < nb; i++) {
			sprite = new BABYLON.Sprite(ID, Tile.spriteManager);
			sprite.cellIndex = type;
			sprite.isPickable = false;
			sprite.position.x = this.position.x + Math.random();
			sprite.position.y = 0.75;
			sprite.position.z = this.position.y + Math.random();
			sprite.size = 0.5;
		}
	}
	
	public initialise(x:number, y:number)
	{
		const ENTRIES:Array<string> = new Array<string>(
			"food", "linemate", "deraumere", "sibur",
			"mendiane", "phiras", "thystame"
		);

		this.position = new BABYLON.Vector2(x, y);
		for (let i:number = ENTRIES.length - 1; i >= 0; i--) {
			this.generate(this.stats.get(ENTRIES[i]), i);
		}
	}
}