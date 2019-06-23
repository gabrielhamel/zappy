class Sound
{
	private audio:HTMLAudioElement = document.createElement("audio");
	
	constructor(src:string)
	{
		this.audio.src = src;
		this.audio.setAttribute("preload", "auto");
		this.audio.setAttribute("controls", "none");
		this.audio.style.display = "none";
		document.body.appendChild(this.audio);
	}

	public stop()
	{
		this.audio.pause();
	}
	public play()
	{
		this.audio.currentTime = 0;
		this.audio.play();
	}
}