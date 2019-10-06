const SerialPort = require('serialport')
const ByteLength = require('@serialport/parser-byte-length')

module.exports = class {
  constructor(startIn, stopIn, startOut, stopOut){
    this.matchIn  = [startIn,  stopIn];
    this.matchOut = [startOut, stopOut];
  }
  open(){
    let self = this;
    this.port = new SerialPort(appConfig.serial.port, {
      baudRate: appConfig.serial.baud,
      autoOpen: false
    });
    this.port.open(function (err) {
      if (err) {
        console.log(chalk.red('Error opening port: ', err.message));
        return process.exit();
      }
    })
    setTimeout(function(){
      self.serialWrite(30, 100);
    }, 1000)

    this.parser = this.port.pipe(new ByteLength({length: 5}))
    this.parser.on('data', function(buf){
      console.log("buf", buf);
      if(self.serialMatch(buf)){
        // Accelerometer
        if(self.serialIDMatch(buf, 100)){ //Accelerometer X
          console.log("accx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 101)){ //Accelerometer Y
          console.log("accy", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 102)){ //Accelerometer Z
          console.log("accz", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 103)){ //Accelerometer raw X
          console.log("raccx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 104)){ //Accelerometer raw Y
          console.log("raccy", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 105)){ //Accelerometer raw Z
          console.log("raccz", self.serialCalc(buf));
        } else

        // Gyro
        if(self.serialIDMatch(buf, 110)){ //Gyro X
          console.log("gyrx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 111)){ //Gyro Y
          console.log("gyry", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 112)){ //Gyro Z
          console.log("gyrz", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 113)){ //Gyro raw X
          console.log("rgyrx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 114)){ //Gyro raw Y
          console.log("rgyry", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 115)){ //Gyro raw Z
          console.log("rgyrz", self.serialCalc(buf));
        } else

        // Magneto
        if(self.serialIDMatch(buf, 120)){ //Magneto X
          console.log("magx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 121)){ //Magneto Y
          console.log("magy", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 122)){ //Magneto Z
          console.log("magz", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 123)){ //Magneto raw X
          console.log("rmagx", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 124)){ //Magneto raw Y
          console.log("rmagy", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 125)){ //Magneto raw Z
          console.log("rmagz", self.serialCalc(buf));
        } else

        // Button
        if(self.serialIDMatch(buf, 130)){ //Button 1
          console.log("button1", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 131)){ //Button 2
          console.log("button2", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 132)){ //Button 3
          console.log("button3", self.serialCalc(buf));
        } else if(self.serialIDMatch(buf, 133)){ //Button 4
          console.log("button4", self.serialCalc(buf));
        }
      }
    }); // will have 4 bytes per data event
  }
  serialMatch(buf){
    let bufferValues = buf.toJSON().data;
    return (bufferValues[0]==this.matchIn[0]) && (bufferValues[4]==this.matchIn[1]);
  }
  serialIDMatch(buf, id){
    let bufferValues = buf.toJSON().data;
    return bufferValues[1]==id;
  }
  serialCalc(buf){
    let bufferValues = buf.toJSON().data;
    return bufferValues[2]*256+bufferValues[3];
  }
  serialWrite(id, data){
    var buf = new Buffer.alloc(5);
    buf.writeUInt8(this.matchOut[0], 0);
    buf.writeUInt8(id, 1);
    buf.writeUInt8(Math.floor(data/256), 2);
    buf.writeUInt8(data%256, 3);
    buf.writeUInt8(this.matchOut[1], 4);
    console.log(buf);
    this.port.write(buf, function(err) {
      if (err) {
        console.log('Error on write: ', err.message)
      }
    })
  }
  list(callback){
    SerialPort.list().then(
      ports => {
        if(callback!=undefined) callback(ports)
      },
      err => {
        console.error(err)
        if(callback!=undefined) callback(err)
      }
    )
  }
}
