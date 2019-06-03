import Server from "./class/Server"

const PORT:number = parseInt(process.argv[2]);
const SERVER_PORT:number = parseInt(process.argv[3]);
let server:Server;

if (!isNaN(PORT) && !isNaN(SERVER_PORT) && PORT > 1024)
	server = new Server(PORT, SERVER_PORT);