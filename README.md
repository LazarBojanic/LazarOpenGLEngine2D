Lazar Bojanić 116/21 RN - Prvi domaći iz računarske grafike

Biblioteke i dll-ovi se nalaze na sledećem repozitorijumu: https://github.com/LazarBojanic/LazarOpenGLEngineOOP

Projekat je rađen u Microsoft Visual Studiu 2022 (x64)

Ovde stavljam upozorenje za epilepsiju za svaki slučaj.

Biblioteke u upotrebi:
GLFW - OpenGL kontekst,
Glad - OpenGL funkcije,
stbi_image - učitavanje tekstura,
glm - biblioteka za matematiku,
irrKlang - zvuk.

Uputstvo:
1. Kopirati dll-ove iz foldera dlls iz repozitorijuma u x64/Debug ili x64/Release u zavisnoti od željene konfiguracije.
2. Skinuti libraries folder sa repozitorijuma i staviti ga u root folder projekta pored assets,src...
2. Build-ovati projekat u Visual Studiu i pokrenuti.

Igra ima nekoliko GameState-ova:
SCREEN_SAVER,
TRANSITION_TO_ACTIVE,
ACTIVE,
WIN,
LOSS.

Kontrole:
SCREEN_SAVER{
    B - Započni igru,
    R - Recentriraj dvd logo.
},
ACTIVE{
    Left Arrow/A - pomeranje dvd-a ulevo,
    Right Arrow/D - pomeranje dvd-a udesno,
    Space - pucanje lasera.
},
LOSS{
    R - Restartuj igru.
}.

Podešavanja igre:
U Game.cpp, u funkciji initVariables, mogu da se podese parametri igre, kao što su broj neprijatelja po koloni i redu (numberOfEnemiesPerLine, numberOfEnemyLines), i bool singleLaser koji određuje da li koristi jedan ili više lasera.