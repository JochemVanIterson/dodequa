// Setup global environment
currentEnvironment;

// Open OSC port 3002
thisProcess.openUDPPort(3002);

// Receive data 'msg' from address '/serialdata/acc/calc', and set in ~freq
~o = OSCFunc(
	{ arg msg,time,addr,recvPort;
		~freq=msg;
	},
	'/serialdata/acc/calc'
);

// Print data every second
TempoClock.default.sched(1, {
	"Value is now: ".post; ~freq.postln;
	1; //Herhaal iedere nn seconden
});
