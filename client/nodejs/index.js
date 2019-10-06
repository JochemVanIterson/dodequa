////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Client ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

global.statusTotal = 5;
global.statusIndex = 1;
global.tools = require('./scripts/tools.js');

// ---------------------------- Import libraries ---------------------------- //
tools.statusPrinter(statusIndex++, "Loading modules");
global.socketio = require('socket.io');
global.socketio_client = require('socket.io-client');
global.fs = require('fs');

global.socketHandler = require('./scripts/socketHandler.js');
global.SerialHandler = require('./scripts/serialHandler.js');
global.oscHandler = require('./scripts/oscHandler.js');

global.startTime = Date.now();

// ---------------------------------- Vars ---------------------------------- //
tools.statusPrinter(statusIndex++, "Init Vars");
// -------- Get arguments -------- //
process.argv.splice(0,2);
global.argv = require('minimist')(process.argv);
global.debug = argv.debug || argv.d;

global.appConfig={}
global.appData = {
  object:{
    sensor:{
      acc: [0., 0., 0.],
      mag: [0., 0., 0.],
      gyro:[0., 0., 0.]
    },
    buttons:[0, 0, 0, 0]
  },
  cloud:{}
};

if(fs.existsSync('./config.json')){
  appConfig = require('./config.json');
} else {
  console.log(chalk.red("File 'config.js' doesn't exist, exiting programm"));
  return;
}
if(debug) console.log("appConfig", appConfig);

// ---------------------------- Socket handler ----------------------------- //
tools.statusPrinter(statusIndex++, "Init Socket.IO");
if(argv['disable-socket']==undefined){
  socketHandler.init();
} else console.log(chalk.yellow("Socket disabled"));

// ---------------------------- OSC handler ----------------------------- //
tools.statusPrinter(statusIndex++, "Init OSC");
if(argv['disable-osc']==undefined){
  oscHandler.init();
  setInterval(()=>{
    // oscHandler.send("/serialdata/acc/calc", [1., 1., (Date.now()-startTime)/1000.]);
    oscHandler.send("/serialdata/acc/calc", appData.object.sensor.acc);
    oscHandler.send("/serialdata/mag/calc", appData.object.sensor.mag);
    oscHandler.send("/serialdata/gyro/calc", appData.object.sensor.gyro);
  }, 500);
} else console.log(chalk.yellow("OSC disabled"));

// ---------------------------- Serial handler ----------------------------- //
tools.statusPrinter(statusIndex++, "Init Serial");
if(argv['disable-serial']==undefined){
  global.serialdevice = new SerialHandler(252, 100, 101, 251);
  serialdevice.list((response)=>{console.log(response)})
  serialdevice.open();
} else console.log(chalk.yellow("Serial disabled"));
console.log(chalk.cyan('      Setup Completed'));
