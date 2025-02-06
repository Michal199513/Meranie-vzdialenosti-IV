# Senzor vzdialenosti s ESP 32 alebo inteligentné monitorovanie vyprázdnenia nádoby
Cieľom projektu je ukázať, akým spôsobom dokáže ultrazvukový snímač monitorovať vzdialenosť a kde v bežnom živote môžeme takéto zapojenie využiť. Súčasťou projektu je aj ukážka konkrétneho využitia v bežnom živote pre zásobník peliet na elektrický kotol.

Zapojenie využíva ultrazvukový snímač vzdialenosti HC-SR04, ktorý môže byť namontovaný napríklad na veku nádoby. Tento senzor sa pozerá na obsah nádoby. Nepretržite meria vzdialenosť medzi krytom nádoby a daným obsahom. Keď sa začne postupne míňať a následne bude klesať, vzdialenosť od veka sa zvýši. Postupným rozsvecovaním jednotlivých LED diód (najkratšia vzdialenosť svieti jedna zelená dióda, pri najväčšej svietia všetky spolu so zvukovým signálom), nám zriadenie dáva znamenie o vyprázdnení nádoby. Samotná aplikácia pre konkrétny zásobník či nádobu, musí byť prispôsobená na danú veľkosť použitej nádoby a použitý obsah v nej. 
Zapojenie a jednotlivé zariadenia môžeme testovať a pozorovať po pripojení dosky k Arduino IDE prostrediu cez USB kábel. Meranú vzdialenosť môžeme vidieť na Serial Monitore aj s následnou vizuálnou a zvukovou identifikáciou pomocou jednotlivých LED spolu s generátorom zvuku, ktoré sa riadia podmienkami nastavenými v zdrojovom kóde programu.
Pre ukážku konkrétnej aplikácie uvádzam odkaz na webovú stránku a video, kde bol tento projekt použitý práve na Monitorovanie zásobníka peliet pre elektrický kotol spolu s prepojením na  ECO HOME domáceho asistenta. Odkaz dostupný tu: https://www.tastethecode.com/making-a-pellet-level-monitor-with-hc-sr04-and-esp8266 ale aj priamo na Youtube: 
https://www.youtube.com/watch?v=yUSwj1SOXVQ&t=1s

Hardvérové vybavenie a elektronické súčiastky
•	Mikrokontrolér ESP32 – WROOM- DA – Module, čip ESP32-D0WD-V3
•	Ultrazvukový senzor HC-SR04
•	Farebné LED (červená, žltá, zelená 3ks)
•	Rezistor s odporom 220 Ohmov pre každú LED
•	Generátor zvuku: aktívny piezoelektrický bzučiak (active buzzer) pre alarm alebo signalizáciu, pri napájaní buzzer pípa frekvenciou približne 2300 Hz
•	USB kábel, prepojovacie káble, BreadBoard

Mikrokontrolér ESP32 – WROOM- DA – Module, čip ESP32-D0WD-V3
Zariadenie je riadené ESP32 - WROOM – DA – Module čip ESP32-D0WD-V3.  Ide o malú a funkčnú vývojovú dosku, ktorú je možné naprogramovať pomocou Arduino IDE, ako aj ESPHome pre neskoršie použitie s Home Assistant. Táto doska je vybavená:
•	32-bitovým dvojjadrovým procesorom Xtensa® LX6.
•	Maximálnou frekvenciou 240 MHz
•	SRAM s veľkosťou 520 kB 
•	ROM s veľkosťou 448 kB
•	16 KB SRAM v RTC
•	2.4 GHz Wi-Fi + Bluetooth® + Bluetooth LE module Built around ESP32 series of SoCs

Ultrazvukový senzor HC-SR04
Ultrazvukový senzor na meranie vzdialenosti, detekčná vzdialenosť od 1 cm do 3 m s presnosťou na 0.3 cm
Špecifikácie:
•	Napájacie napätie 3.8 – 5.5 V
•	Maximálny prúd 8 mA
•	Frekvencia ultrazvuku 40 kHz
•	Maximálna vzdialenosť 3 m
•	Minimálna vzdialenosť 1 cm
•	Trigger puls 10 mikrosekúnd
•	Uhol detekcie 15°
Využíva veľmi vysokofrekvenčné zvukové vlny, ktoré sú vysielané jedným z prevodníkov, odrazené späť od prekážky pred ním a následne prijímané druhým. Meraním času potrebného na to, aby sa tieto zvukové vlny dostali od a k senzoru, potom vypočíta vzdialenosť medzi ním a čímkoľvek, čo je pred ním. Keď poznáme vzdialenosť, môžeme zmerať vzdialenosti plnej a prázdnej nádrže a môžeme túto vzdialenosť zmapovať. 
Vysielač vysiela po dobu 10 mikrosekúnd zvuk s frekvenciou 40KHz. Pre ľudské ucho je tento zvuk nepočuteľný, keďže človek dokáže zachytiť zvuk do frekvencie 20KHz. Tento zvuk sa šíri vzduchom a ak narazí na prekážku, odrazí sa od nej a cestuje naspäť do prijímača. Pre potreby programovania je nutné sledovať čas a vzdialenosť objektu od ultrazvukového senzora. Zvuk sa v stálom prostredí šíri rýchlosťou 343 m/s. Senzor však meria čas v mikrosekundách, musíme teda rýchlosť premeniť na premeniť na mikrosekundy. Konštantu rýchlosti teda zmeníme na 343 / 1 000 000 = 0.000343 m/µs. Vzdialenosť chceme merať v centimetroch, preto konštantu upravíme vynásobením 100. Do kódu použijeme upravenú konštantu 0.0343, pričom ju vydelíme číslom 2, keďže senzor ráta dráhu na ceste k prekážke a súčasne od prekážky.

Generátor zvuku: aktívny piezoelektrický bzučiak (active buzzer)
Špecifikácie:
•	Pracovné napätie: 3.5 V – 5.5 V pre 5V verziu, 2.5V – 3.5V pre 3V verziu 
•	Typ: magnetický 
•	Prúd: <25 mA 
•	Frekvencia: 2300 /-500 Hz 
•	Priemer: 12 mm 
•	Výška: 9.5 mm  

Zapojenie na doske BreadBoard - popis komponentov a jednotlivých pinov
Snímač HC-SR04 používa 4 vodiče. Na zabezpečenie napájania je napájací vstup (VCC) pripojený k 5V pinu na doske ESP 32- WROOM- DA a uzemňovací (GND) je pripojený k spoločnému vývodu pre uzemnenie (GND). Ďalšie dva vývody Echo a Trigger, sú pripojené k digitálnemu vstupnému pinu na mikrokontroléri a jeden k výstupnému pinu. Pre vysielací pin Trigger som použil pin 17 nastavený ako výstup, ktorý použijeme na vysielanie zvukových impulzov. Prijímací Pin Echo je pripojený k pinu 16 na mikrokontroléri a pomocou neho prijímame odrazený zvuk, aby sme zistili, ako dlho trvalo, kým sa odrazil späť. Senzor HC-SR04 môže fungovať aj na 3,3V, ale keďže ho máme k dispozícii 5V to nám poskytne oveľa stabilnejšie čítanie a nepoškodí senzor ani mikrokontrolér. LED sú pripojené anódami  (kladná časť) na digitálne piny č. 2, 5, 4, 18 a 19 a katódami  (záporná časť) do spoločného uzemnenia (GND). Pred každou LED je pripojený ochranný rezistor, ktorý slúži na zníženie vstupného napätie 5V na potrebných 1,9 až 2 V pre bezpečné rozsvietenie diód. Piezoelektrický aktívny akustický menič, náš generátor zvuku je zapojený na digitálny pin  č.21 a jeho druhý vývod na uzemnenie (GND). Celé komplet zariadenie je napojené cez USB napájanie 5V.

Zdrojový kód projektu
// HC-SR04, ultazvukovy senzor, nastavenie pinov
const int vysielaciPin = 17;
const int prijimaciPin = 16;
//sirenie zvuku
#define SOUND_VELOCITY 0.034
//#define CM_TO_INCH 0.393701
// definovanie premennych (trvanie, vzdialenost, 5x LED, 1x Generator zvuku)
long trvanie; 
float vzdialenostCm;
int led10cm = 2;
int led15cm = 5;
int led20cm = 4;
int led25cm = 18;
int led35cm = 19;
int gen = 21;

void setup() {
  // Zapnutie seriovej komunikacie pre vypis na obrazovku a nastavanie pinov (vstup/vystup)
  Serial.begin(115200); 
  pinMode(vysielaciPin, OUTPUT);
  pinMode(prijimaciPin, INPUT);
  pinMode(led10cm, OUTPUT);
  pinMode(led15cm, OUTPUT);
  pinMode(led20cm, OUTPUT);
  pinMode(led25cm, OUTPUT);
  pinMode(led35cm, OUTPUT);
  pinMode(gen, OUTPUT);
}

void loop() {
  digitalWrite(vysielaciPin, LOW);
  delayMicroseconds(2);
  digitalWrite(vysielaciPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(vysielaciPin, LOW);
  
  trvanie = pulseIn(prijimaciPin, HIGH);
  
  // Vypocet vzdialenosti / 2
  vzdialenostCm = trvanie * SOUND_VELOCITY/2;
  
  
  // Vypisanie vzdialenosti na monitor
  Serial.print("Vzdialenost (cm): ");
  Serial.println(vzdialenostCm);
  // Podmienky pre vypocet vzdialenosti a rozsvietenie LED, gen.
if (vzdialenostCm <= 10) {
    digitalWrite(led10cm, HIGH); 
    digitalWrite(led15cm, LOW);
    digitalWrite(led20cm, LOW);
    digitalWrite(led25cm, LOW); 
    digitalWrite(led35cm, LOW);   
} else if (vzdialenostCm > 10 && vzdialenostCm <= 15) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH); 
    digitalWrite(led20cm, LOW);  
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 15 && vzdialenostCm <= 20) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH); 
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 20 && vzdialenostCm <= 25) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH); 
    digitalWrite(led25cm, HIGH);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 25 && vzdialenostCm <= 35) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH);
    digitalWrite(led25cm, HIGH);
    digitalWrite(led35cm, HIGH);
    tone (gen, 300,500);
    noTone(gen);  
}
else {
    digitalWrite(led10cm, LOW);
    digitalWrite(led15cm, LOW);
    digitalWrite(led20cm, LOW);
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
}
  delay(1000);
}
