class Tchat
{
	private msgs:Array<HTMLLIElement> = new Array<HTMLLIElement>();

	constructor()
	{
	}

	public addMessage(msg:string):void
	{
		let newMsg = document.createElement("li");
		newMsg.textContent = msg;
		newMsg.classList.add("test");
	}
}
