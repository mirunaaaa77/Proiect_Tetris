Un joc Tetris complet implementat în limbajul C, cu interfață grafică în terminal folosind biblioteca ncurses. 
Include mecanici clasice de joc plus un sistem original de Piese Instabile cu efect de explozie.

# Clonează sau descarcă proiectul
cd proiect/

# Compilează
make all

# Rulează
./final

# Curăță fișierele compilate
make clean

# Cum se joacă
Piesele geometrice (Tetrominoes) cad din partea de sus a tablei de joc (20×10).
Scopul este să completezi rânduri orizontale pentru a le elimina și a obține puncte.
Jocul se termină când piesele ajung la marginea superioară.

← sau A Mută piesa la stânga
→ sau D Mută piesa la dreapta
↑ sau W Rotește piesa (sens orar)
↓ sau S Coboară piesa mai repede
SPACE Hard Drop — coboară instant
P Pauză / Reluare 
Q sau ESCI eșire din joc


La fiecare 10 piese apare un Tetromino Instabil, marcat vizual prin culoarea albă.
Dacă un rând este completat folosind cel puțin un bloc instabil, se produce o undă de șoc:

Toți vecinii 3×3 ai blocului instabil sunt distruși

Nivelul crește la fiecare 10 linii eliminate.
Odată cu nivelul, crește și viteza de cădere a pieselor.

# Structura Proiectului

proiect/
├── main.c          Punct de intrare

├── board.c         Logica tablei de joc
├── board.h

├── tetromino.c     Piese, rotație, mișcare
├── tetromino.h
├── renderer.c      Desenarea pe ecran (ncurses)
├── renderer.h

├── input.c         Gestionarea tastaturii
├── input.h

├── game.c          Game loop, scor, nivel
├── game.h
└── Makefile
Fiecare bloc distrus aduce 50 de puncte bonus
