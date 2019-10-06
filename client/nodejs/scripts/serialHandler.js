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
          console.log("accx", self.serialCalcFloat(buf));
          appData.object.sensor.acc[0] = self.serialCalcFloat(buf);
        } else if(self.serialIDMatch(buf, 101)){ //Accelerometer Y
          console.log("accy", self.serialCalcFloat(buf));
          appData.object.sensor.acc[1] = self.serialCalcFloat(buf);
        } else if(self.serialIDMatch(buf, 102)){ //Accelerometer Z
          console.log("accz", self.serialCalcFloat(buf));
          appData.object.sensor.acc[2] = self.serialCalcFloat(buf);
        } else

        // Gyro
        if(self.serialIDMatch(buf, 110)){ //Gyro X
          console.log("gyrx", self.serialCalcFloat(buf));
          appData.object.sensor.gyro[0] = self.serialCalcFloat(buf);
        } else if(self.serialIDMatch(buf, 111)){ //Gyro Y
          console.log("gyry", self.serialCalcFloat(buf));
          appData.object.sensor.gyro[1] = self.serialCalcFloat(buf);
        } else if(self.serialIDMatch(buf, 112)){ //Gyro Z
          console.log("gyrz", self.serialCalcFloat(buf));
          appData.object.sensor.gyro[2] = self.serialCalcFloat(buf);
        } else

        // Magneto
        if(self.serialIDMatch(buf, 120)){ //Magneto X
          console.log("magx", self.serialCalcFloat(buf));
          appData.object.sensor.mag[0] = self.serialserialCalcFloatCalc(buf);
        } else if(self.serialIDMatch(buf, 121)){ //Magneto Y
          console.log("magy", self.serialCalcFloat(buf));
          appData.object.sensor.mag[1] = self.serialCalcFloat(buf);
        } else if(self.serialIDMatch(buf, 122)){ //Magneto Z
          console.log("magz", self.serialCalcFloat(buf));
          appData.object.sensor.mag[2] = self.serialCalcFloat(buf);
        } else

        // Button
        if(self.serialIDMatch(buf, 130)){ //Button 1
          console.log("button1", self.serialCalcBool(buf));
        } else if(self.serialIDMatch(buf, 131)){ //Button 2
          console.log("button2", self.serialCalcBool(buf));
        } else if(self.serialIDMatch(buf, 132)){ //Button 3
          console.log("button3", self.serialCalcBool(buf));
        } else if(self.serialIDMatch(buf, 133)){ //Button 4
          console.log("button4", self.serialCalcBool(buf));
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
  serialCalcUInt(buf){
    let bufferValues = buf.toJSON().data;
    let value = bufferValues[2]*256+bufferValues[3];
    return value;
  }
  serialCalcInt(buf){
    let bufferValues = buf.toJSON().data;
    let value = bufferValues[2]*256+bufferValues[3];
    value -= 32768;
    return value;
  }
  serialCalcFloat(buf){
    let bufferValues = buf.toJSON().data;
    let value = bufferValues[2]*256+bufferValues[3];
    value -= 32768;
    value /= 100.;
    return value;
  }
  serialCalcBool(buf){
    let bufferValues = buf.toJSON().data;
    return bufferValues[3]!=0;
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
