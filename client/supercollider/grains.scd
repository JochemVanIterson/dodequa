// s.boot;
// s.reboot;
currentEnvironment;

~map = {
	arg value, inMin, inMax, outMin, outMax;
	var deltaIn = inMax - inMin;
	var deltaOut = outMax - outMin;
	var scale = ((value - inMin)/deltaIn);
	scale*deltaOut+outMin;
};

~calcVariables = {
	//-------------- Position --------------//
	~position = ~map.value(~rotatieOrientatie, -100, 100, 0, 254);
	// (~rotatieOrientatie+100)/200*254;
	//position tussen 0 en 254 adv rotatieOrientatie

	//-------------- Envelope --------------//
	if (~rotatieSnelheid >= 34, {
		~attack = ~map.value(~rotatieSnelheid, -100, 100, 0, 3000);
		// (~rotatieSnelheid+100)/200*3000;
	},{
		~attack = 500;
 	});
	//attack tussen 500 en 3000 ms adv rotatieSnelheid

	if (~snelheid >= 34, {
		~decay = ~map.value(~snelheid, -100, 100, 0, 3000);
		// (~snelheid+100)/200*3000;
	},{
		~decay = 500;
	});
	//decay tussen 500 en 3000 ms adv snelheid

	//-------------- Position Jitter --------------//
	if( (~rotatieOrientatie + ~rotatieSnelheid/2) >= 34,{
		~positionJitter = ~rotatieOrientatie + ~map.value(~rotatieSnelheid, -100, 100, 0, 100);
		// ~rotatieSnelheid/2+100/200*100;
	},{
		~positionJitter = 5;
	});
	//position jitter tussen 5 en 100

	//-------------- Length --------------//
	if (~rotatieSnelheid+~rotatieSnelheidCloud/2+100 >=0.2,{
		~length = ~rotatieSnelheid + ~map.value(~rotatieSnelheidCloud, -100, 100, 0, 1000);
		// ~rotatieSnelheidCloud/2+100/200*1000;
	},{
		~length = 1;
	});
	//length tussen 1 en 1000

	//-------------- Harmonics --------------//
	~harmonics = ~snelheid + ~map.value(~rotatieSnelheid, -100, 100, 0, 254);
	// ~snelheidCloud/2+100/200*254;
	//harmonics tussen 0 en 254

	//-------------- Galm --------------//
	~galm = ~rotatieOrientatie + ~map.value(~rotatieSnelheid, -100, 100, 0, 6000);
	// ~rotatieOrientatieCloud/2+100/200*6000;
	//galm tussen 0 en 6000

	//-------------- Filters --------------//
	//TODO: getal uit Xline halen
	if ((~rotatieSnelheid+~snelheidCloud+~snelheid/3+100 >= 1),{
		~filter = {XLine.ar(200, 20000, 1.0, 1.0, 0.0, 0);}
	},{
		~filter = 200;
	});
	// filters tussen 200 en 20000

	//-------------- Pitch --------------//
	if (~rotatieOrientatie+~snelheid-~rotatieOrientatieCloud+~snelheidCloud/3+100 >= 8,{
		~pitch = ~rotatieOrientatie+~snelheid-~rotatieOrientatieCloud+~snelheidCloud/3+100/200*4500;
	},{
		~pitch = 180;
	});
};

thisProcess.openUDPPort(3002);
~oscAcc = OSCFunc(
	{ arg msg,time,addr,recvPort;
		msg.postln;
		~snelheid=msg[1]*msg[2]*msg[3];
	},
	'/serialdata/acc/calc'
);
~oscMag = OSCFunc(
	{ arg msg,time,addr,recvPort;
		msg.postln;
		~rotatieOrientatieX = msg[1];
		~rotatieOrientatieY = msg[2];
		~rotatieOrientatieZ = msg[3];
		~rotatieOrientatie = msg[1]*msg[2]*msg[3];
	},
	'/serialdata/mag/calc'
);
~oscGyro = OSCFunc(
	{ arg msg,time,addr,recvPort;
		msg.postln;
		~rotatieSnelheidX = msg[1];
		~rotatieSnelheidY = msg[2];
		~rotatieSnelheidZ = msg[3];
		~rotatieSnelheid = msg[1]*msg[2]*msg[3];
	},
	'/serialdata/gyro/calc'
);
~oscButtons = OSCFunc(
	{ arg msg,time,addr,recvPort;
		msg.postln;
		~buttonOne = msg[1];
		~buttonTwo = msg[2];
		~buttonThree = msg[3];
		~buttonFour = msg[4];
	},
	'/serialdata/buttons'
);



//-------------- Variabelen --------------//
~rotatieOrientatie = 34;
~rotatieSnelheid = 34;

~rotatieOrientatieX = 34;
~rotatieOrientatieY = 34;
~rotatieOrientatieZ = 34;

~rotatieSnelheidX = 35;
~rotatieSnelheidY = 35;
~rotatieSnelheidZ = 35;

~snelheid = 75;

~rotatieOrientatieCloud = 20;
~rotatieSnelheidCloud = -58;
~snelheidCloud = 44;

~position = 0;
~attack = 500;
~decay = 500;
~positionJitter = 5;
~length = 1;
~harmonics = 0;
~galm = 0;
~filter = 200;
~pitch = 180;

~buttonOne = 0;
~buttonTwo = 0;
~buttonThree = 0;
~buttonFour = 0;

TempoClock.default.sched(0.1, {
	// "CalcVariables ".postln;
	~calcVariables.value;
	0.1; //Herhaal iedere nn seconden
});

//------------------Audio-------------------//
~g0 = Group.new(s, 0);
~g1 = Group.after(~g0);

~myBus = Bus.audio(s, 2);

~myBus.index;
~myBus.numChannels;

SynthDef(\EffectBus, {
	arg cutoff, multy = 1, add = 0;
	var input, effect;
	input = In.ar(~myBus, 2);

	effect = FreeVerb.ar(LPF.ar(input, 20000, 1, 0), 0.33, 0.5, 0.2, 1.0, 0);

	Out.ar(0, effect);
}).add;

a = Synth(\EffectBus, [\cutoff, 440], ~g1);

b = Buffer.read(s, "C:/Users/Tijs/Desktop/GranSample2_L.wav");

SynthDef(\Grain, {
	arg outch = ~myBus, rate=1.0, amp=0.5, startPos=0.0, pan=0.0, length=0.1, bufnum;
	var env=EnvGen.kr(Env.sine(length, amp), doneAction:2);
	var grain=PlayBuf.ar(1, bufnum, rate, 1, startPos)*env;

	//Out.ar(0, Pan2.ar(grain, pan));
	Out.ar(0, LPF.ar(Pan2.ar(grain, pan), ~filter, 1, 0));
}).add;

r = {Out.ar(0, FreeVerb.ar(In.ar(~myBus, 2), mix: 0.5, room: 0.9, mul: 1.0))}.play;

~filter = 1000;
~filter = 20000;
~filter = 440;

a.set(\cutoff, 20000);
a.set(\cutoff, 440);

s.scope;
~filter.postln;

~startPosDeviation=0.0001;
{
	var length=0.2, startPos=0.2, timestretch=2, overlap=65;
	inf.do{
		s.sendBundle(0.2, [\s_new, \Grain, -1, 1, 1, \bufnum, b.bufnum
			, \startPos
			, (startPos+~startPosDeviation.rand2)*b.sampleRate
			, \rate, [-48, -24, -12, 0, 12].choose.midiratio
			, \length, length
			, \pan, 0.2.rand2
			, \amp, (1/overlap).sqrt
		]);
		(length/overlap).wait;
		startPos=(length/timestretch/overlap+startPos)%b.duration;
	}
}.fork;

// s.quit

//	Out.ar(obs, FreeVerb.ar(LPF.ar(Pan2.ar(grain, pan), 200, 1, 0), 0.33, 0.5, 0.2, 1.0, 0));
