# Fallen Angel

The fallen angel is easily my longest running project going back to at least 2015. It's gone through many iterations but it's still the same Ship of Theseus to me. The electronics in particular have been refactored many times as I learn more electrical engineering.

The hardware has held up suspiciously well after a few early failures. I may revisit that at some point but I'm not sure I could do much better with my current skills and tools.

[Photos](https://photos.app.goo.gl/zDN6f2SJvbBqM53Y8) Videos soon to come.

## Design

* Frame and armature made out of 1/2" PVC tubing.
  * PVC is lightweight, and what it lacks in rigidity it makes up for in durability and workability.
  * Aluminum tube linkages
  * The real magic sauce is the joints - By heating and flattening the ends of the pipe then drilling an hole and clamping with washers and nylock nuts, you can get fairly smooth movement in one plane with nearly no unwanted lateral movement!
* **144 RGBW leds** per wing, for a total of 1,152 individually controllable light-emitting elements.
  * That's a theoretical maximum of 23A current draw, but that would be with all four colors and no resistance. Actual current draw rarely exceeds 10A.
* **8 FOOT WINGSPAN** fully open, collapses to just 2'4" wide
  * Luckily I'm 6'6 and the wings are about head height when open so they go over most people's heads!
* Opens and closes in **less than 3 seconds**. This was a tough requirement but super important: slow wings are so, so sad.
  * 12v 5A (60W!) high-speed linear actuator with 22 lbs (10 kgs) of force
  * Lights turn on as the wings open and vice-versa
  * Soft-start and soft-stop using feedback from 150mm linear position sensor
  * Hard-wired manual control for emergencies (the two amber buttons on the motor controller)
* Fully modular electronics - separate battery, controller, wing control, and light control modules.
  * All clear covers - I want to see the pretty wires!
* New for 2024 - **Waterproof electronics**! ~~No more~~ Less fear of firey death in a rainstorm!
  * Deutsch automotive connectors between modules
* 77Wh power supply can run with typical use for 4-6 hours
   * 3S 7000mAh LiPo model aircraft battery
   * 30A Battery Management System
   * Fun Fact: the battery is rated at 120C discharge, which would be 840 amps. Which would require wires as thick as my wrists. *sigh* Marketing.
* Remote controlled with 4-button keyfob (power, up, down, light mode)
  * Keyfob is easily concealed but also easy to operate by touch. Kind of the keystone to this thing.
  * Don't even ask how annoying the RF module is, requiring *exactly* 5 volts of *pristine* power. But I haven't found anything else that comes close to the convenience and simplicity.
* Hand-dyed synthetic "feathers" ('cause real feathers are a huge f*cking mess)
* Air-dry foam clay and acrylic paint for boney effect
* TRS connection for additional accessory, such as a fire halo (see photos)
* Controlled by Arduino Mega 256
  * Programmed in "Wiring" - the default Arduino language which is the love child of C++ and Python with a lobotomy
* Many lights and displays in the electronics because I like them
  * Voltage and current displays for 12v and 5v power supplies
  * 4-digit display for... whatever. Currently the readout from the position sensor.
  * (psst... don't tell anyone, but the bi-color LED matrix on the control module is just for fun. It displays random patterns because it reminds me of the control panels of early computers)
 
Arguably the greatest accomplishment of the whole project is the power supply. I need to be able to safely - and portably - deliver up to 15v at 15A.
For safety margin, the power supply was designed to deliver 30A continuously, that's 360 fricking watts strapped to my back!
And it needs to do this for several hours at a time - I planned for 4-6 hours of continuous usage (depending on how often I actuate the wings).
The battery is a model aircraft battery as these are designed for very high current output. They are made without protection circuits (to increase the odds of a safe landing) so I added a Battery Management System (BMS) that protects against under-and-over voltage and over current, monitors the temperature, balances the cells, and even makes it easy to charge (with a GIANT power brick).
All that, and it's waterproof. Yeah, I'm proud of it!
