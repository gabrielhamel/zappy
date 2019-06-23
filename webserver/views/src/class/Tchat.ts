class Tchat
{
	private msgs:Array<HTMLLIElement> = new Array<HTMLLIElement>();

	constructor()
	{
	}

	public addMessage(teamName:string, id:string, msg:string):void
	{
		var tchat:HTMLUListElement = document.getElementById("tchat-list") as HTMLUListElement;
		var newMsg = document.createElement("li");
		newMsg.innerHTML = "<strong> [" + teamName + " - " + id + "]</strong> " + msg;
		tchat.append(newMsg);

		let msgs:HTMLCollectionOf<HTMLLIElement> = tchat.getElementsByTagName("li");
		if (msgs.length > 8) {
			msgs[2].classList.add("fade-out-second-last");
		}
		if (msgs.length > 9) {
			msgs[1].classList.add("fade-out");
			msgs[1].classList.remove("fade-out-second-last");
		}
		if (msgs.length > 10)
			msgs[0].remove();
	}
}
