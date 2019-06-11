class Tile
{
	private static readonly Y:number = 0.75;
	private static readonly ANIMATION_BUMP:number = 0.15;
	private static readonly ANIMATION_FPS:number = 10;
	private static nb:number = 0;
	private static spriteManager:BABYLON.SpriteManager = null;
	private stats:Map<string, number> = new Map<string, number>();
	private position:BABYLON.Vector2;
	private animation:BABYLON.Animation;
	private sprites:Array<BABYLON.Sprite> = new Array<BABYLON.Sprite>();

	constructor(food:number, linemate:number, deraumere:number, sibur:number, mendiane:number, phiras:number, thystame:number, scene:BABYLON.Scene)
	{
		let size:number = Game.size.x * Game.size.y * 7;
		
		this.stats.set("food", food);
		this.stats.set("linemate", linemate);
		this.stats.set("deraumere", deraumere);
		this.stats.set("sibur", sibur);
		this.stats.set("mendiane", mendiane);
		this.stats.set("phiras", phiras);
		this.stats.set("thystame", thystame);
		this.createAnimation();
		if (!Tile.spriteManager)
			Tile.spriteManager = new BABYLON.SpriteManager("spriteManager" + Tile.nb, "/assets/resources.png", size, 16, scene);
		Tile.nb++;
	}

	private createAnimation():void
	{
		let keys:Array<any> = new Array<any>();
		let rnd:number = Math.random() * Tile.ANIMATION_BUMP;

		this.animation = new BABYLON.Animation("tileAnimation" + Tile.nb, 
			"position.y", Tile.ANIMATION_FPS, 
			BABYLON.Animation.ANIMATIONTYPE_FLOAT, 
			BABYLON.Animation.ANIMATIONLOOPMODE_CYCLE
		);
		keys.push({
			frame: 0,
			value: Tile.Y
		});
		keys.push({
			frame: Tile.ANIMATION_FPS,
			value: Tile.Y - Tile.ANIMATION_BUMP / 2 + rnd
		});
		keys.push({
			frame: Tile.ANIMATION_FPS * 2,
			value: Tile.Y
		});
		this.animation.setKeys(keys);
	}
	private generate(nb:number, type:number):void
	{
		const ID:string = "tile" + Tile.nb + "-" + type;
		let sprite:BABYLON.Sprite;
	
		for (let i:number = 0; i < nb; i++) {
			sprite = new BABYLON.Sprite(ID, Tile.spriteManager);
			sprite.cellIndex = type;
			sprite.isPickable = false;
			sprite.position.x = this.position.x + Math.random();
			sprite.position.y = Tile.Y;
			sprite.position.z = this.position.y + Math.random();
			sprite.size = 0.5;
			sprite.animations = [];
			sprite.animations.push(this.animation);
			this.sprites.push(sprite);
		}
	}
	
	public initialise(x:number, y:number):void
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
	public startAnimations(scene:BABYLON.Scene):void
	{
		for (let i:number = this.sprites.length - 1; i >= 0; i--) {
			scene.beginAnimation(this.sprites[i], 0, Tile.ANIMATION_FPS * 2, true);
		}
	}
}