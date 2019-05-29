import Server from "./class/Server"

const PORT:number = parseInt(process.argv[2]);
let server:Server;

if (!isNaN(PORT) && PORT > 1024)
	server = new Server(PORT);