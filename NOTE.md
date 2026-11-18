# GBA Tracker - Note di progetto

## Obiettivo
ROM per Game Boy Advance in stile LSDj, con interfaccia più intuitiva.
Chi sviluppa: principiante assoluto, lavora solo da Android (browser + app mGBA).
Claude scrive il codice, l'utente incolla i file su GitHub e prova la ROM.

## Come si lavora (flusso)
1. Claude fornisce i file di codice.
2. Si incollano nel repository GitHub (Add file / modifica file esistente).
3. GitHub Actions compila da solo (workflow "Build GBA").
4. Si scarica lo zip da Actions -> ultimo run verde -> Artifacts -> rom.
5. Si estrae game.gba e si prova con mGBA su Android.
6. Se la compilazione fallisce (❌), si incolla a Claude il testo dell'errore.

## Struttura del repository
- source/main.c            codice della ROM
- .github/workflows/main.yml   compilazione automatica (devkitARM, container devkitpro/devkitarm)
- NOTE.md                  questo file

## Decisioni prese
- Interfaccia ibrida: vista sequencer a step (griglia, piano roll) per scrivere
  + pannello comandi stile tracker (Vibrato, Slide, Arpeggio, Taglia nota, ecc.)
  + vista lista verticale stile tracker degli stessi dati (si cambia con Select).
- Stessi dati per tutte le viste: ogni step ha nota, strumento, volume,
  comando (tipo + valore) e offset di tempo.
- Note fuori griglia: offset di tempo per step (circa da -12 a +12 tick) e swing.
  Il sequencer deve avere più tick per step fin da subito.
- Effetti (distorsione, bitcrusher, chorus, riverbero grezzo): NON applicabili
  ai canali PSG del Game Boy, che vanno direttamente al mixer. Servono voci
  generate in software e inviate via Direct Sound.
- Ordine consigliato: prima PSG per avere subito un risultato, poi motore
  software con gli effetti. (Scelta finale ancora da confermare.)

## Controlli previsti
- D-pad: muove il cursore
- A: mette/toglie nota; A + su/giù: cambia altezza
- L/R: cambia canale
- Start: play/stop
- Select: cambia vista

## Tappe
- [x] Tappa 0: ROM di test (schermo colorato + nota su canale 1 con A/B).
      Compilazione GitHub e prova su mGBA funzionanti.
- [ ] Tappa 1: modalità tile, font incluso nel codice, griglia a 16 step
      con cursore, note, riproduzione in loop su un canale square,
      dati già predisposti per comandi e offset di tempo.
- [ ] Tappa 2: pannello comandi (Vibrato, Slide, Arpeggio, Taglia nota).
- [ ] Tappa 3: vista lista stile tracker.
- [ ] Tappa 4: altri canali (square 2, wave, noise), strumenti, salvataggio.
- [ ] Tappa 5: motore audio software ed effetti (distorsione, chorus, riverbero).

## Stato attuale
Tappa 0 completata. Prossimo passo: tappa 1.

## Promemoria tecnici
- Le ROM scaricate da Actions (Artifacts) scadono dopo circa 90 giorni:
  basta rilanciare Actions -> Build GBA -> Run workflow.
- Il salvataggio su cartuccia vera (SRAM/Flash) va deciso presto.
- mGBA su Android va bene per i test, meglio provare anche su hardware vero.
