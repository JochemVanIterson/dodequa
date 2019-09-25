"Environment set".postln;
currentEnvironment;

"Open OSC port".postln;
thisProcess.openUDPPort(3002);
~o = OSCFunc(
	{ arg msg,time,addr,recvPort;
		~freq=msg;
	},
	'/serialdata/acc/calc'
);
