var osc = require("osc");

var udpPort;
exports.init = function(){
  udpPort = new osc.UDPPort({
    localAddress: "0.0.0.0",
    localPort: appConfig.osc.inPort,
    metadata: true
  });

  // Open the socket.
  udpPort.open();

  // When the port is read, send an OSC message to, say, SuperCollider
  udpPort.on("ready", function () {
    console.log(chalk.cyan('OSC port created'));
  });
}
exports.send = function(address, dataArray){
  if(udpPort==undefined)return;
  let data = [];
  for(key in dataArray){
    let itm = dataArray[key];
    let type = "";
    if((typeof itm == "number") && (itm % 1 === 0)){ // Int
      type = "i";
    } else if((typeof itm == "number") && (itm % 1 !== 0)){ // Float
      type = "f";
    } else if(typeof itm == "string"){
      type = "s";
    } else if(typeof itm == "boolean"){
      type = "b";
    }
    data.push({
      type: type,
      value: itm
    })
  }
  console.log("data", data)
  udpPort.send({
      address: address,
      args: data
    }, appConfig.osc.address, appConfig.osc.outPort);
}
exports.udpPort = udpPort;
