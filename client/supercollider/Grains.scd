// s.boot;
//s.quit;
//s.reboot;
currentEnvironment;

Server.default.options.outDevice_("Built-in Output");

~map = {
	arg value, inMin, inMax, outMin, outMax;
	var deltaIn = inMax - inMin;
	var deltaOut = outMax - outMin;
	var scale = ((value - inMin)/deltaIn);
	scale*deltaOut+outMin;
};

~calcVariables = {
	//-------------- Position --------------//
	~position = ~map.value(~rotatieOrientatie, -100, 100, 0.0, 0.8);
	// (~rotatieOrientatie+100)/200*254;
	//position tussen 0 en 254 adv rotatieOrientatie

	//-------------- Envelope --------------//
	if (~rotatieSnelheid >= 34, {
		~pan = ~map.value(~rotatieSnelheid, -100, 100, 0, 0.8);
		// (~rotatieSnelheid+100)/200*3000;
	},{
		~pan = 0.3;
 	});
	//attack tussen 500 en 3000 ms adv rotatieSnelheid

	if (~snelheid >= 34, {
		~amplitude = ~map.value(~snelheid, -100, 100, 0.0, 1.0);
		// (~snelheid+100)/200*3000;
	},{
		~amplitude = 1.0;
	});
	//decay tussen 500 en 3000 ms adv snelheid

	//-------------- Position Jitter --------------//
	if( (~rotatieOrientatie + ~rotatieSnelheid/2) >= 34,{
		~positionJitter = (~rotatieOrientatie + ~map.value(~rotatieSnelheid, -100, 100, 0, 100)) * 0.001;
		// ~rotatieSnelheid/2+100/200*100;
	},{
		~positionJitter = 5;
	});
	//position jitter tussen 5 en 100

	//-------------- Length --------------//
	if (~rotatieSnelheid/2+100 >=0.2,{
		~length = ~rotatieSnelheid + ~map.value(~rotatieSnelheid, -100, 100, 0.0, 0.9);
		// ~rotatieSnelheidCloud/2+100/200*1000;
	},{
		~length = 0.0;
	});
	//length tussen 1 en 1000

	//-------------- Harmonics --------------//
	~harmonics = ~snelheid + ~map.value(~rotatieSnelheid, -100, 100, 0, 254);
	// ~snelheidCloud/2+100/200*254;
	//harmonics tussen 0 en 254

	//-------------- Galm --------------//
	~stretch = ~rotatieOrientatie + ~map.value(~rotatieSnelheid, -100, 100, 0, 40);
	// ~rotatieOrientatieCloud/2+100/200*6000;
	//galm tussen 0 en 6000

	//-------------- Filters --------------//
	//TODO: getal uit Xline halen
	if (((~rotatieSnelheid + ~snelheid/3+100) >= 1),{
		~filter = {XLine.ar(200, 20000, 1.0, 1.0, 0.0, 0);}
	},{
		~filter = 200;
	});
	// filters tussen 200 en 20000

	//-------------- Pitch --------------//
	if (~rotatieOrientatie+~snelheid/3+100 >= 8,{
		~pitch = ~rotatieOrientatie+~snelheid/3+100/200*4500;
	},{
		~pitch = 180;
	});
};

thisProcess.openUDPPort(3002);
~oscAcc = OSCFunc(
	{ arg msg,time,addr,recvPort;

		~snelheid=msg[1]*msg[2]*msg[3];
	},
	'/serialdata/acc/calc'
);
~oscMag = OSCFunc(
	{ arg msg,time,addr,recvPort;

		~rotatieOrientatieX = msg[1];
		~rotatieOrientatieY = msg[2];
		~rotatieOrientatieZ = msg[3];
		~rotatieOrientatie = msg[1]*msg[2]*msg[3];
	},
	'/serialdata/mag/calc'
);
~oscGyro = OSCFunc(
	{ arg msg,time,addr,recvPort;

		~rotatieSnelheidX = msg[1];
		~rotatieSnelheidY = msg[2];
		~rotatieSnelheidZ = msg[3];
		~rotatieSnelheid = msg[1]*msg[2]*msg[3];
	},
	'/serialdata/gyro/calc'
);

~oscButtons = OSCFunc(
	{ arg msg,time,addr,recvPort;
		s.waitForBoot({
			if ((msg[1] == 1), {
				{
					var length=0.7, startPos=0.4, timestretch=2, overlap=3;
					10.do{
						s.sendBundle(0.2, [\s_new, \miniGrain, -1, 1, 1, \bufnum, b.bufnum
							, \startPos
							, (startPos+~positionJitter.rand2)*b.sampleRate
							, \rate, [0, 12, 24].choose.midiratio
							, \length, length
							, \pan, 0.2.rand2
							, \amp, (1/overlap).sqrt * 0.4
						]);
						(length/overlap).wait;
						startPos=(length/timestretch/overlap+startPos)%b.duration;
					}
				}.fork;
			});

			if ((msg[2] == 1), {
				{
					var length=0.5, startPos=0.4, timestretch=2, overlap=2;
					100.do{
						s.sendBundle(0.2, [\s_new, \miniGrain, -1, 1, 1, \bufnum, b.bufnum
							, \startPos
							, (startPos+~positionJitter.rand2)*b.sampleRate
							, \rate, [5, 7].choose.midiratio
							, \length, length
							, \pan, 0.2.rand2
							, \amp, (1/overlap).sqrt * 0.2
						]);
						(length/overlap).wait;
						startPos=(length/timestretch/overlap+startPos)%b.duration;
					}
				}.fork;
			});

			if ((msg[3] == 1), {
				{
					var length=0.5, startPos=0.4, timestretch=2, overlap=2;
					50.do{
						s.sendBundle(0.2, [\s_new, \miniGrain, -1, 1, 1, \bufnum, b.bufnum
							, \startPos
							, (startPos+~positionJitter.rand2)*b.sampleRate
							, \rate, [10, 14].choose.midiratio
							, \length, length
							, \pan, 0.2.rand2
							, \amp, (1/overlap).sqrt * 0.2
						]);
						(length/overlap).wait;
						startPos=(length/timestretch/overlap+startPos)%b.duration;
					}
				}.fork;
			});

			if ((msg[4] == 1), {
				{
					var length=0.5, startPos=0.4, timestretch=2, overlap=2;
					500.do{
						s.sendBundle(0.2, [\s_new, \miniGrain, -1, 1, 1, \bufnum, b.bufnum
							, \startPos
							, (startPos+~positionJitter.rand2)*b.sampleRate
							, \rate, [-36, -29].choose.midiratio
							, \length, length
							, \pan, 0.2.rand2
							, \amp, (1/overlap).sqrt * 0.5
						]);
						(length/overlap).wait;
						startPos=(length/timestretch/overlap+startPos)%b.duration;
					}
				}.fork;
			});
		});
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

~position = 0;
~pan = 0.2;
~amplitude = 1.0;
~positionJitter = 5;
~length = 1;
~harmonics = 0;
~stretch = 2;
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
s.waitForBoot({
	"Wait completed".postln;
	s.scope;
	~grainPath = File.getcwd +/+ "GranSample2_L48.wav";
	// ~grainPath = "/Users/jochem/stack/HKU/Jaar 3/Blok 3/CSD/dodequa/client/supercollider/GranSample2_L48.wav";

	b = Buffer.read(s, ~grainPath, 0, -1, {
		SynthDef(\Grain, {
			arg rate=1.0, amp=0.5, startPos=0.0, pan=0.0, length=0.1, bufnum, filterfrequency=440;
			var env=EnvGen.kr(Env.sine(length, amp), doneAction:2);
			var grain=PlayBuf.ar(1, bufnum, rate, 1, startPos)*env;

			//Out.ar(0, Pan2.ar(grain, pan));
			Out.ar(0, LPF.ar(Pan2.ar(grain, pan), filterfrequency, 1, 0));
		}).add;


		SynthDef(\miniGrain, {
			arg rate=1.0, amp=0.5, startPos=0.0, pan=0.0, length=0.1, bufnum;
			var env=EnvGen.kr(Env.sine(length, amp), doneAction:2);
			var grain=PlayBuf.ar(1, bufnum, rate, 1, startPos)*env;

			//Out.ar(0, Pan2.ar(grain, pan));
			Out.ar(0, Pan2.ar(grain, pan));
		}).add;


		{
			var length=~length, startPos=~position, timestretch=~stretch, overlap=9;
			inf.do{
				s.sendBundle(0.2, [\s_new, \Grain, -1, 1, 1, \bufnum, b.bufnum
					, \startPos
					, (startPos+~positionJitter.rand2) * b.sampleRate
					, \rate, [-48, -24, -12, 0, 12].choose.midiratio
					, \length, length
					, \pan, ~pan.rand2
					, \amp, (1/overlap).sqrt
					// , \amp, (1/overlap).sqrt * ~amplitude
					// , \filterfrequency, ~filter
					, \filterfrequency, 2000
				]);
				(length/overlap).wait;
				startPos=(length/timestretch/overlap+startPos)%b.duration;
			}
		}.fork;
	});
});
