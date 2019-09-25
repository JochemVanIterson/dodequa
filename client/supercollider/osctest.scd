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

TempoClock.default.sched(1, {
	"Value is now: ".post; ~freq.postln;
	1; //Herhaal iedere nn seconden
});
