#include <assert.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* aceasta functie va decide cu ce culori va trebui sa coloram
casutele cuvintelor ghicite. Aceasta functie va returna un
numar int de 5 cifre format doar din cifrele 1, 2, 3 cu
semnificatia: 1 - verde, 2 - galben, 3 - negru.
Astfel, daca prima cifra este 1 atunci prima litera
va trebui colorata verde, daca a doua cifra este 2,
atunci a doua casuta va trebui colorata galben si tot asa */
int checkword(char guess[6], char ranword[6]) {
    int i, output = 0, match, j, frecventa[200], used[200], outputv[5];

    for (i = 0; i < 200; i++) {
        frecventa[i] = 0;
        used[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        frecventa[(int)ranword[i]]++;
        outputv[i] = 0;
    }

    /* mai intai decidem ce litere vor fi colorate cu verde
    daca este cazul */
    for (i = 0; i < 5; i++) {
        if (guess[i] == ranword[i] &&
            used[(int)guess[i]] < frecventa[(int)guess[i]]) {
            // cifra 1 simbolizeaza verde;
            outputv[i] = 1;
            used[(int)guess[i]]++;
        }
    }

    /* apoi decidem ce litere din cuvantul inputat de user nu apar
    deloc in cuvantul ce trebuie ghicit, astfel acestea vor trebui
    colorate cu negru */
    for (i = 0; i < 5; i++) {
        match = 0;
        for (j = 0; j < 5; j++) {
            if (guess[i] == ranword[j]) {
                match = 1;
            }
        }
        if (match == 0) {
            // cifra 3 simbolizeaza negru
            outputv[i] = 3;
            used[(int)guess[i]]++;
        }
    }

    /* apoi din literele ramase vom decide care trebuie colorata
    negru si care galben. Stiind frecventa fiecarei litere din
    cuvantul ce trebuie ghicit, precum si cate litere, eventual identice,
    a inputat userul, putem astfel decide daca coloram cuvantul
    cu galben sau negru */
    for (i = 0; i < 5; i++) {
        if (outputv[i] == 0) {
            match = 0;
            for (j = 0; j < 5; j++) {
                if (guess[i] == ranword[j]) {
                    match = 1;
                }
            }
            if (match == 1 && used[(int)guess[i]] < frecventa[(int)guess[i]]) {
                used[(int)guess[i]]++;
                // cifra 2 simbolizeaza galben
                outputv[i] = 2;
            } else {
                used[(int)guess[i]]++;
                // cifra 3 simbolizeaza negru
                outputv[i] = 3;
            }
        }
    }

    output = 0;
    for (i = 0; i < 5; i++) {
        output = 10 * output + outputv[i];
    }

    return output;
}

int main() {
    initscr();
    noecho();
    raw();

    // pentru a face cursorul invizibil
    curs_set(0);

    box(stdscr, 0, 0);

    WINDOW *cell[7][7], *logwindow, *menuwindow;
    int i, j, ybeg, xbeg, randnum, guessover, k, c, guessnumber, q, gamewon;
    int ymax, xmax, menuactive, highlight, choice;
    char cuvinte[27][6], ranword[6], guess[6], menuchoices[2][10];

    strcpy(menuchoices[0], "exit\0");
    strcpy(menuchoices[1], "restart");

    strcpy(cuvinte[0], "arici\0");
    strcpy(cuvinte[1], "atent\0");
    strcpy(cuvinte[2], "baiat\0");
    strcpy(cuvinte[3], "ceata\0");
    strcpy(cuvinte[4], "debut\0");
    strcpy(cuvinte[5], "peste\0");
    strcpy(cuvinte[6], "fixat\0");
    strcpy(cuvinte[7], "hamac\0");
    strcpy(cuvinte[8], "harta\0");
    strcpy(cuvinte[9], "jalon\0");
    strcpy(cuvinte[10], "jucam\0");
    strcpy(cuvinte[11], "lacat\0");
    strcpy(cuvinte[12], "magie\0");
    strcpy(cuvinte[13], "nufar\0");
    strcpy(cuvinte[14], "oaste\0");
    strcpy(cuvinte[15], "perus\0");
    strcpy(cuvinte[16], "rigle\0");
    strcpy(cuvinte[17], "roman\0");
    strcpy(cuvinte[18], "sanie\0");
    strcpy(cuvinte[19], "scris\0");
    strcpy(cuvinte[20], "sonda\0");
    strcpy(cuvinte[21], "texte\0");
    strcpy(cuvinte[22], "tipar\0");
    strcpy(cuvinte[23], "titan\0");
    strcpy(cuvinte[24], "zebra\0");
    strcpy(cuvinte[25], "vapor\0");
    strcpy(cuvinte[26], "vatra\0");

    // permite folosirea culorilor
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(0));

    /*acest infinite loop va permite jocului sa mearga pana
    la nesfarsit, deoarece dupa ce apasam 'restart', dorim
    un joc nou. Singura cale de a iesi din acest loop este
    de a selecta 'exit' din meniul jocului */
    while (1) {
        /*generarea unui numar random si alegerea
        unui cuvant random din lista */
        srand(time(NULL));
        randnum = (rand()) % 27;
        strcpy(ranword, cuvinte[randnum]);

        clear();
        wclear(menuwindow);

        box(stdscr, 0, 0);

        // intializarea casutelor
        for (i = 1; i <= 6; i++) {
            for (j = 1; j <= 5; j++) {
                cell[i][j] = newwin(3, 3, 4 * i - 3, j * 5);
                box(cell[i][j], 0, 0);
                keypad(cell[i][j], true);
            }
        }

        // initializarea loggerului
        logwindow =
            newwin(5, 100, getbegy(cell[6][5]) + getmaxy(cell[6][5]) + 3,
                   getbegx(cell[1][1]));
        box(logwindow, 0, 0);

        // decomenteaza pentru a vedea ce cuvant trebuie ghicit
        // printw("%s", ranword);

        // printeaza titlul jocului
        getmaxyx(stdscr, ymax, xmax);
        mvprintw(0, xmax / 2, "WORDLE");
        refresh();

        for (i = 1; i <= 6; i++) {
            for (j = 1; j <= 5; j++) {
                wrefresh(cell[i][j]);
            }
        }
        wrefresh(logwindow);

        gamewon = 0;
        guessover = 0;
        i = 1;
        j = 1;
        menuactive = 0;
        highlight = 0;

        /* acest for va trata fiecare din cele 6 guessuri pe care
        playerul le are la dispozitie. Daca playerul ghiceste
        cuvantul inainte de a si epuiza cele 6 guessuri
        atunci va iesi din acest for loop */
        for (i = 1; i <= 6 && gamewon == 0; i++) {
            j = 1;
            guessover = 0;
            k = -1;

            /* acest while va fi activ pana cand utilizatorul a
            introdus guessul sau (a apasat pe enter avand
            5 litere) sau daca a deschis meniul (daca a
            apasat tasta ':') */
            while (guessover == 0 && menuactive == 0) {
                if (j < 6) {
                    if (menuactive == 0) {
                        getbegyx(cell[i][j], ybeg, xbeg);
                        move(ybeg + 1, xbeg + 1);
                        c = wgetch(cell[i][j]);

                        wmove(logwindow, 1, 1);
                        wclrtoeol(logwindow);
                        wrefresh(logwindow);

                        move(ybeg + 1, xbeg + 1);
                    }
                } else {
                    if (menuactive == 0) {
                        getbegyx(cell[i][j - 1], ybeg, xbeg);
                        move(ybeg + 1, xbeg + 1);
                        c = wgetch(cell[i][j - 1]);

                        wmove(logwindow, 1, 1);
                        wclrtoeol(logwindow);
                        wrefresh(logwindow);

                        move(ybeg + 1, xbeg + 1);
                    }
                }
                /* daca s a inputat o litera atunci ea va fi scrisa
                in casuta corespunzatoare */
                if ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) &&
                    j < 6 && menuactive == 0) {
                    c = (char)tolower(c);
                    guess[++k] = c;
                    move(ybeg + 1, xbeg + 1);
                    addch((char)c);
                    j++;

                }
                /* daca s a apasat backspace atunci se va scrie
                in casuta precedenta ' '(space) */
                else if (c == KEY_BACKSPACE && menuactive == 0) {
                    if (k > -1) {
                        k--;
                        getbegyx(cell[i][j - 1], ybeg, xbeg);
                        move(ybeg + 1, xbeg + 1);
                        addch(' ');
                        j--;
                    }
                }
                /* daca s a afisat enter verificam daca sunt introduse
                suficiente caractere. Daca sunt, vom apela functia
                de check pentru stringul inputat de user.
                In caz contrar afisam un mesaj corespunzator */
                else if (c == 10 && menuactive == 0) {
                    if (j == 6) {
                        // checkword
                        guessnumber = checkword(guess, ranword);
                        for (q = 5; q >= 1; q--) {
                            getbegyx(cell[i][q], ybeg, xbeg);
                            move(ybeg + 1, xbeg + 1);
                            attron(COLOR_PAIR(guessnumber % 10));
                            addch(guess[q - 1]);
                            attroff(COLOR_PAIR(guessnumber % 10));
                            guessnumber = guessnumber / 10;
                        }

                        guess[5] = '\0';

                        // verificam daca userul a ghicit cuvantul
                        if (strcmp(guess, ranword) == 0) {
                            getbegyx(logwindow, ybeg, xbeg);
                            mvprintw(ybeg + 1, xbeg + 1, "CONGRATS! YOU WON!!");
                            gamewon = 1;
                        }

                        guessover = 1;
                    } else {
                        getbegyx(logwindow, ybeg, xbeg);
                        mvprintw(ybeg + 1, xbeg + 1,
                                 "You must choose a five-letter word");
                    }
                }
                /* Daca userul a apasat tasta ':' atunci variabila menuactive
                va fi folosita pentru a indica initializarea meniului */
                else if (c == ':') {
                    menuactive = 1;
                }

                // dupa fiecare keystroke dam refresh la fiecare window
                if (j < 6) {
                    wrefresh(cell[i][j]);
                    refresh();
                } else if (j == 6) {
                    wrefresh(cell[i][j - 1]);
                    refresh();
                }
            }
        }

        /* Daca s a iesit din for fara sa fi ghicit cuvantul
        inseamna ca userul a pierdut si vom afisa
        un mesaj corespunzator */
        if (gamewon == 0) {
            getbegyx(logwindow, ybeg, xbeg);
            mvprintw(ybeg + 1, xbeg + 1, "You lost! The word was: %s!",
                     ranword);
        }

        /* iesim din forul mare fie pt ca s au terminat guessurile
        fie pt ca am castigat. In oricare dintre cele doua cazuri
         va fi nevoie sa afisam un meniu */

        highlight = 0;
        menuactive = 1;

        // initializare menuwindow
        menuwindow = newwin(5, 40, ymax / 2 - 15, xmax / 2);
        box(menuwindow, 0, 0);
        keypad(menuwindow, true);
        wrefresh(menuwindow);
        refresh();

        while (1) {
            /* afisarea optiunilor de meniu cu selector pentru
            optiunea aferenta */
            for (q = 0; q < 2; q++) {
                if (q == highlight) {
                    wattron(menuwindow, A_REVERSE);
                }
                getbegyx(menuwindow, ybeg, xbeg);
                mvwprintw(menuwindow, 1, 3 + 10 * q, menuchoices[q]);
                wattroff(menuwindow, A_REVERSE);
            }
            choice = wgetch(menuwindow);

            switch (choice) {
                // Selectam optiunea care se afla mai la stanga
                case KEY_LEFT:
                    highlight--;
                    if (highlight == -1) {
                        highlight = 0;
                    }
                    break;

                // Selectam optiunea care se afla mai la dreapta
                case KEY_RIGHT:
                    highlight++;
                    if (highlight == 2) {
                        highlight = 1;
                    }
                    break;
                default:
                    break;
            }
            /* Daca s a apasat enter, atunci o optiune din meniu
            a fost aleasa, motiv pentru care folosim break
            pentru a iesi din cel de al doilea infinite loop */
            if (choice == 10) {
                break;
            }
            wrefresh(menuwindow);
            refresh();
        }

        // Daca s a selectat exit incheiam programul
        if (highlight == 0) {
            endwin();
            exit(0);
        }
        /* Daca s a selectat restart curatam fereastra
        terminalului, lasand infinite loopul de la inceput
        sa repete toti pasii de pana acum */
        else if (highlight == 1) {
            wclear(menuwindow);
            clear();
        }
    }

    getch();
    endwin();
    return 0;
}