[[Robotics]]

> "On fait ca en 6h" Xavier 07/02/2022

https://drive.google.com/drive/folders/1BlVbMFdLxmj6kDDD5jHrfZRzBOPHhF0q
# Intro
Reboot du projet point de vue elec autour de plaque de prototypage. Design modulaire original trop ambitieux.
# Meetings
## 26/06/2024
- Test ultrason
	- trigger generation [[Circee Robot]]works
	- trigger + measurmeent doesnt work when tested on debugger: random measurements
		- measurement multiplexed doesnt work cause the trigger gpio is not free and prevent us from measuring (on the same fucking gpio)
	- the normal HC SR04 works with our current code
	- breakpoints in interrupt routine fucks measurement !
	- To use the cursed the HCSR04 it seems (from the arduino official lib) to reconfigure the whole ass same pin every single time you want to get or receive a measurement
## 23/07/2024
- Soldered new connector on battery
### TODO
- [ ] Need to make cable of the battery charger
- [ ] Xavier
	- [x] order cable
	- [ ] panne fer a souder
- [ ] Bea buy
	- [ ] lighter
	- [x] scotch double face
	- [x] Third hand (for soldering)

## 22/08/2024
- design support plaque a trou
	- 165 mm x 54mm x 10 mm

## 10/02/2024
- check fit support étage
	- [x] Improve design
	- [x] to be printed by Xav

## 07/11/2024
- https://lastminuteengineers.com/drv8833-arduino-tutorial/
- https://www.ti.com/lit/ds/symlink/drv8833.pdf?ts=1730959853798&ref_url=https%253A%252F%252Fwww.ti.com%252Fmotor-drivers%252Fproducts.html

## 12/12/2024
### last meeting
- debug uart
- review pinmap (and actually save it)
## today
- [ ] encoder uart test
- [ ] do the wiring on the prototyping plate

## 07/01/2024
### TODO
- [ ] fix code to actually use position and not distances
- [ ] finish regulation loop
	- [ ] add pos_to_duty
- systick is in ms might be a problem for precision
### TODO
- [ ] Low level motor code to be updated for 2 pins operation
- [x] Crist: Ramener PLA
- [x] Xav: Imprimer les supports avec differents remplissages,tester le fit

## 18/06/2025
- Il y a 2 versions d'asser sur le repo
	- une version asser en position de chaque moteur qui marche
	- une ébauche de la version delta theta non fonctionnel avec pb structurels
### TODO
- spécifier le code de l'asservissement différentiel delta theta
- rédaction du code

# Elec
## Pont en H : DRV8833
![[Pasted image 20241128192446.png]]

# Odometrie / Asservissement
![[asservissement_des_masses.png]]

https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
https://www.pm-robotix.eu/2022/02/02/asservissement-et-pilotage-de-robot-autonome/


# TODO
- [ ] Test/debug debug usart for print

# moteur data

1400 tick per revolution
entre 90 et 155 rpm à 6Vcc
donc à 90 rpm 90 r/m x 1400 t/r = 2100 t/s = 2.1 t/ms

Periode = 20 ms

(Mesure/Periode) x 255/2.1 = Duty

# USART
- picocom

# Programmation
## Openocd
  - version 0.12.0 can't flash the stm32F3 but 0.11.0 is known to work
### [[Ultrasonic sensor]]

#### Input capture setup bug
- ~~La configuration du pin est mauvaise et ne fait pas d'input capture, le compteur actuellement ne fait que compter normalement. Est ce que l'on rate quelque chose au niveau de la lecture de valeur (potentielle génération d'interrupt a faire ?)~~

- ~~Piégé dans l'interrupt, on rentre mais ne sort pas~~
- Fixed !
- Code to be cleaned
### Actual debug
[[GDB debugging STM32]]


# Méca
Bed size ender 3 = 220 \* 220 mm

## visserie

  - \[x\] vis M4
  - \[x\] écrou M4 - \[ \] visse orientation moteur taille \>6 mais \<8,
    m7 peut être ?
  - \[ \] rondelle élévation roue folle 1cm ==\> design + impression
  - \[ \] maj design, distance entre les trous trop grande, trou taille
    ok, taille

disque ok

  - \[x\] cristiano - dremel couper les tige filetées
      - \[ \] xav - accès fablab

## Plaque base Dimension: 142.725 \* 73 mm


