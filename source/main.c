// Test iniziale: schermo colorato + suono sul canale 1 del Game Boy
#define REG16(a) (*(volatile unsigned short*)(a))
#define VRAM ((volatile unsigned short*)0x06000000)

#define REG_DISPCNT   REG16(0x04000000)
#define REG_VCOUNT    REG16(0x04000006)
#define REG_KEYINPUT  REG16(0x04000130)
#define REG_SND1_SWEEP REG16(0x04000060)
#define REG_SND1_ENV   REG16(0x04000062)
#define REG_SND1_FREQ  REG16(0x04000064)
#define REG_SNDCNT_L   REG16(0x04000080)
#define REG_SNDCNT_H   REG16(0x04000082)
#define REG_SNDCNT_X   REG16(0x04000084)

#define KEY_A 1
#define KEY_B 2

static void riempi(unsigned short colore) {
    for (int i = 0; i < 240 * 160; i++) VRAM[i] = colore;
}

static void aspetta_vblank(void) {
    while (REG_VCOUNT >= 160) {}
    while (REG_VCOUNT < 160) {}
}

static void suona(unsigned short freq) {
    REG_SND1_SWEEP = 0;
    REG_SND1_ENV = 0xF380;            // volume massimo, onda 50%, dissolvenza
    REG_SND1_FREQ = 0x8000 | freq;    // bit 15 = fai partire la nota
}

int main(void) {
    REG_DISPCNT = 0x0403;             // modalità grafica 3
    REG_SNDCNT_X = 0x0080;            // accendi l'audio
    REG_SNDCNT_L = 0xFF77;            // volume e canali
    REG_SNDCNT_H = 0x0002;            // volume canali Game Boy

    riempi(0x2000);                   // blu scuro

    unsigned short prima = 0;
    while (1) {
        aspetta_vblank();
        unsigned short premuti = ~REG_KEYINPUT;
        unsigned short nuovi = premuti & ~prima;

        if (nuovi & KEY_A) { suona(1750); riempi(0x03E0); }  // La, verde
        if (nuovi & KEY_B) { suona(1849); riempi(0x001F); }  // Mi, rosso

        prima = premuti;
    }
    return 0;
}
