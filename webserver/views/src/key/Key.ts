class Key
{
	private codes:Array<number>;
	private isPressed:boolean = false;
	
	constructor(codes:Array<number>)
	{
		this.codes = codes;
	}

	public getState():boolean
	{
		return (this.isPressed);
	}
	public setState = (event:KeyboardEvent):void =>
	{
		for (let i:number = this.codes.length; i >= 0; i--) {
			if (this.codes[i] == event.which) {
				this.isPressed = (event.type == "keydown");
			}
		}
	}
}