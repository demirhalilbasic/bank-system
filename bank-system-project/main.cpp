/*
| Projekat sistema banke                                |
| Predmet: Programski jezici i programiranje            |
| Na projektu radili: Aldina Huskic, Demir Halilbasic   |
| Studenti II godine                                    |
| Smijer IT / IR                                        |
| Datum pocetka: 11.11.2023.                            |
| Datum zavrsetka: 23.11.2023.                          |
| IPI Akademija Tuzla                                   |
*/

// INPUT, OUTPUT, IZRAZI, KONTROLNE STRUKTURE
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// GENERISANJE NASUMICNOG BROJA
#include <random>

// MANIPULACIJA VREMENA
#include <ctime>
#include <iomanip>
#include <sstream>

// DELAY, KORISNICKO ISKUSTVO
#include <chrono>
#include <thread>
#include <conio.h>

// NAMESPACE
using namespace std;

// HEADER FAJLOVI
#include "racuni.h"
#include "korisnici.h"
#include "adminracuni.h"
#include "adminkorisnici.h"
#include "userkrediti.h"
#include "userpanel.h"
#include "adminpanel.h"
#include "login.h"

int main()
{
    load_baza();
    login();
    return 0;
}
