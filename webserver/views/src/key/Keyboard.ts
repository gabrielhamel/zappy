class Keyboard
{
	private static readonly KEYS_LEFT:Array<number> = [37, 81];
	private static readonly KEYS_UP:Array<number> = [38, 90];
	private static readonly KEYS_RIGHT:Array<number> = [39, 68];
	private static readonly KEYS_DOWN:Array<number> = [40, 83];
	public static readonly LEFT = 0;
	public static readonly UP = 1;
	public static readonly RIGHT = 2;
	public static readonly DOWN = 3;
	private keys:Array<Key> = new Array<Key>();

	constructor()
	{
		this.keys.push(new Key(Keyboard.KEYS_LEFT));
		this.keys.push(new Key(Keyboard.KEYS_UP));
		this.keys.push(new Key(Keyboard.KEYS_RIGHT));
		this.keys.push(new Key(Keyboard.KEYS_DOWN));
		window.addEventListener("keydown", this.manageKeyEvents);
		window.addEventListener("keyup", this.manageKeyEvents);
	}

	private manageKeyEvents = (key:KeyboardEvent):void =>
	{
		for (let i:number = this.keys.length - 1; i >= 0; i--) {
			this.keys[i].setState(key);
		}
	}
	public getKey(id:number):boolean
	{
		if (id < 0 || id >= this.keys.length)
			return (false);
		return (this.keys[id].getState());
	}
}