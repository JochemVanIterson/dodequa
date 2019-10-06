exports.init = function(){
  let url = `http://${appConfig.socket.url}:${appConfig.socket.port}`;
  var socket = socketio_client.connect(url, {
    reconnection: true
  });

  socket.on('connect', function () {
    console.log('connected to '+url);
    socket.on('clouddata', function (data) {
      console.log('message from the server:', data);
    });

    socket.on('clientEvent', function (data) {
      console.log('message from the server:', data);
      oscHandler.send("/serialdata/acc/calc", [0., 0., data]);
    });
  });
}
