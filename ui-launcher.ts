import { spawn } from "child_process";
import usage from "pidusage";

const port = "8080";

const cnakedProcess = spawn(`./cnaked-test-bin`);
cnakedProcess.stdout.on("data", console.log);
cnakedProcess.stderr.on("data", console.log);

async function printUsage() {
  try {
    const currentUsage = await usage(cnakedProcess.pid);
    console.log(cnakedProcess.pid);
  } catch (e) {
    console.log(e);
  }
}

setInterval(async () => {
  printUsage();
}, 500);
