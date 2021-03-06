////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Server ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

global.statusTotal = 2;
global.statusIndex = 1;
global.tools = require('./scripts/tools.js');

// ---------------------------- Import libraries ---------------------------- //
tools.statusPrinter(statusIndex++, "Loading modules");
global.socketio = require('socket.io');
global.fs = require('fs');

global.socketHandler = require('./scripts/socketHandler.js');

// ---------------------------------- Vars ---------------------------------- //
tools.statusPrinter(statusIndex++, "Init Vars");
// -------- Get arguments -------- //
process.argv.splice(0,2);
global.argv = require('minimist')(process.argv);
global.debug = argv.debug || argv.d;

global.appConfig={}

if(fs.existsSync('./config.json')){
  appConfig = require('./config.json');
} else {
  console.log(chalk.red("File 'config.js' doesn't exist, exiting programm"));
  return;
}
if(debug) console.log("appConfig", appConfig);

// ---------------------------- Socket listener ----------------------------- //
tools.statusPrinter(statusIndex++, "Init Socket.IO");
socketHandler.init();

console.log(chalk.cyan('      Setup Completed'));
