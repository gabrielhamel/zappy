class Infobox
{
	private tileInfos:HTMLElement = document.getElementById("tileInfos");

	constructor()
	{
		
	}

	public updateTile(tile:Tile)
	{
		let list:HTMLCollectionOf<HTMLElement> = this.tileInfos.getElementsByTagName("span");
		let datas:Array<number> = tile.getRawDatas();

		for (let i:number = datas.length - 1; i >= 0; i--) {
			list[i * 2 + 1].textContent = "" + datas[i];
		}
	}
}