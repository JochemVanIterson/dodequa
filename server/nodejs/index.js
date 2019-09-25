////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Server ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

global.statusTotal = 2;
global.statusIndex = 1;
global.tools = require('./scripts/tools.js');

// ---------------------------- Import libraries ---------------------------- //
tools.statusPrinter(statusIndex++, "Loading modules");

// ---------------------------------- Vars ---------------------------------- //
tools.statusPrinter(statusIndex++, "Init Vars");
// -------- Get arguments -------- //
process.argv.splice(0,2);
global.argv = require('minimist')(process.argv);
global.debug = argv.debug || argv.d;

console.log(chalk.cyan('      Setup Completed'));
