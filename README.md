# Introduktion
Mexec är ett program som simulerar en så kallad pipeline i skalet ”bash”. Det en pipeline gör
är att via n olika processer skapar en kedja där en process utdata blir den andra processens
indata. En sådan kedja skapar möjligheten att hantera data med hjälp av ett kommando för att
sedan hantera dess utdata med nästa kommando.

## Användning
Kompilera programmet via 'Makefile' där funktionerna make och clean är definerade.
Programmet kräver GCC.
Programmet kräver en indata (.txt) fil med giltiga Linux/Unix-kommandon, separerade mha radbrytning.


Exempel på indata-fil :
```bash
# Filnamn: Exempel.txt

# Nedanstående fil skulle lista alla filer i katalogen och skickat det som indata till grep "pattern".
ls -l
grep "pattern"

# Det är en exakt kopia av Linux/Unix-pipelinen: ls -l | grep "pattern".
```
Starta programmet:
```bash
# Hur du startar programmet.
./mexec [FILNAMN]

# Hur programmet startar med "Exempel.txt"
./mexec Exempel.txt
```
## Systembeskrivning
Kolla "Programbeskrivning.pdf" för beskrivning av programmet.
