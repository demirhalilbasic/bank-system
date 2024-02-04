#ifndef ADMINRACUNI_H_INCLUDED
#define ADMINRACUNI_H_INCLUDED

void adminRacuni()
{
    int unos;
    do
    {
        cout<<"\n\t** [BANKA]: Ulogovani ste kao administrator! **\n\t~~ Nalazite se u root/pristup racunima podmeniju ~~\n";
        cout<<"\n\t[ADMIN PANEL] Unesite zeljenu opciju:\n\t1. Kreiranje novog racuna\n\t2. Izmjena postojeceg racuna\n\t3. Pregled racuna u bazi\n\t4. Brisanje racuna iz baze\n\t5. Nazad\n\n\tUnos: ";
        cin>>unos;
        switch(unos)
        {
            case 1: {
                system("cls");
                cout<<"\n\t[KREIRANJE NOVOG RACUNA]\n\n\tOdaberite zeljeni tip racuna za kreiranje. (1 - Tekuci racun, 2 - Stedni racun)\n\tUnos: ";
                int tipRacuna;
                cin>>tipRacuna;

                if(tipRacuna==1)
                {
                    int provjeraCuvanjeGreska=0;
                    char provjeraCuvanje;
                    cout<<"\n\tZapoceli ste sa kreiranjem novog tekuceg racuna. Slijedite daljnje upute."<<endl;
                    TekuciRacun noviTekuci;
                    noviTekuci.unosTekuci();
                    do
                    {
                        if(provjeraCuvanjeGreska!=0)
                        {
                            cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\t  Unos: ";
                        }
                        cin>>provjeraCuvanje;
                        provjeraCuvanjeGreska=1;
                    }
                    while((provjeraCuvanje!='Y')&&(provjeraCuvanje!='y')&&(provjeraCuvanje!='N')&&(provjeraCuvanje!='n'));
                    if((provjeraCuvanje=='Y')||(provjeraCuvanje=='y'))
                    {
                        tekuciRacuni.push_back(noviTekuci);
                        cout<<"\n\t  Pohranjivanje podataka u toku..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[KREIRANJE NOVOG RACUNA] Novi tekuci racun uspjesno unesen u bazu."<<endl;
                    }
                    else
                    {
                        cout<<"\n\t  Odustajanje od pohrane podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[KREIRANJE NOVOG RACUNA] Odustali ste od kreiranja novog tekuceg racuna."<<endl;
                    }
                }
                else if(tipRacuna==2)
                {
                    int provjeraCuvanjeGreska=0;
                    char provjeraCuvanje;
                    cout<<"\n\tZapoceli ste sa kreiranjem novog stednog racuna. Slijedite daljnje upute."<<endl;
                    StedniRacun noviStedni;
                    noviStedni.unosStedni();
                    do
                    {
                        if(provjeraCuvanjeGreska!=0)
                        {
                            cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\t  Unos: ";
                        }
                        cin>>provjeraCuvanje;
                        provjeraCuvanjeGreska=1;
                    }
                    while((provjeraCuvanje!='Y')&&(provjeraCuvanje!='y')&&(provjeraCuvanje!='N')&&(provjeraCuvanje!='n'));
                    if((provjeraCuvanje=='Y')||(provjeraCuvanje=='y'))
                    {
                        stedniRacuni.push_back(noviStedni);
                        cout<<"\n\t  Pohranjivanje podataka u toku..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[KREIRANJE NOVOG RACUNA] Novi stedni racun uspjesno unesen u bazu."<<endl;
                    }
                    else
                    {
                        cout<<"\n\t  Odustajanje od pohrane podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[KREIRANJE NOVOG RACUNA] Odustali ste od kreiranja novog stednog racuna."<<endl;
                    }
                }
                else
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Odabrani tip racuna nepostojeci!"<<endl;
                }
                break;
            }
            case 2: {
                system("cls");
                cout<<"\n\t[IZMJENA RACUNA]\n\n\tUnesite broj racuna kako biste izmijenili zeljene podatke.\n\tUnos: ";
                string brojKarticeIzmjena;
                cin >> brojKarticeIzmjena;
                cout<<"\n\t  Pretraga racuna u bazi podataka..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                bool pronadjen = false;
                for(auto& tekuci : tekuciRacuni)
                {
                    if(tekuci.getBrojKartice()==brojKarticeIzmjena)
                    {
                        int odabirOpcije;
                        time_t t = time(0);
                        tm* now = localtime(&t);
                        cout<<"\n\t[IZMJENA RACUNA]: Nalog je uspjesno pronadjen u bazi podataka.\n\t_________________________________________________\n\t| 1. Broj racuna: "<<tekuci.getBrojKartice()<<"\t\t|\n\t|    Vrsta racuna: Tekuci\t\t\t|\n\t| 2. Datum isteka (mjesec/godina): "<<tekuci.getDatumIstekaKartice()<<"\t|\n\t| 3. Stanje: "<<tekuci.getStanjeRacuna()<<" KM\t\t\t\t|\n\t| 4. Dozvoljeno prekoracenje: "<<tekuci.getDozvoljenoPrekoracenje()<<".00 KM\t|\n\t| 5. CVV (Card Verification Value): "<<tekuci.getCVV()<<"\t\t|\n\t| 6. PIN kod: "<<tekuci.getPinKod()<<"\t\t\t\t|\n\t|    Pristup Log:\t\t\t\t|\n\t|    ";
                        cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite broj opcije koju zelite izmijeniti: ";
                        cin>>odabirOpcije;
                        switch(odabirOpcije)
                        {
                            case 1: {
                                string brojKartice;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI broj racuna za ovaj nalog.\n\tUnos: ";
                                cin>>brojKartice;
                                tekuci.setBrojKartice(brojKartice);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali broj racuna. Novi broj racuna naloga: "<<brojKartice<<endl;
                                break;
                            }
                            case 2: {
                                string mjesec, godina;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI datum isteka za ovaj nalog.\n\tUnesite mjesec isteka (01-12): ";
                                cin>>mjesec;
                                cout<<"\n\tUnesite godinu isteka (dvoznamenkasti format; 2026 -> 26): ";
                                cin>>godina;
                                mjesec+='/';
                                mjesec+=godina;
                                tekuci.setDatumIstekaKartice(mjesec);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali datum isteka racuna. Novi datum isteka naloga: "<<mjesec<<endl;
                                break;
                            }
                            case 3: {
                                float stanjeRacuna;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVO stanje (iznos) za ovaj nalog u KM.\n\tUnos: ";
                                cin>>stanjeRacuna;
                                tekuci.setStanjeRacuna(stanjeRacuna);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali iznos na racunu. Novo stanje naloga: "<<stanjeRacuna<<" KM."<<endl;
                                break;
                            }
                            case 4: {
                                int dozvoljenoPrekoracenje;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVO dozvoljeno prekoracenje za ovaj nalog u KM.\n\tUnos: ";
                                cin>>dozvoljenoPrekoracenje;
                                tekuci.setDozvoljenoPrekoracenje(dozvoljenoPrekoracenje);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali dozvoljeno prekoracenje racuna.\n\tNovo dozvoljeno prekoracenje naloga: "<<dozvoljenoPrekoracenje<<".00 KM."<<endl;
                                break;
                            }
                            case 5: {
                                string cvv;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI 3-znamenkasti CVV (Card Verification Value) za ovaj nalog.\n\tUnos: ";
                                cin>>cvv;
                                tekuci.setCVV(cvv);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali CVV racuna. Novi CVV naloga: "<<cvv<<endl;
                                break;
                            }
                            case 6: {
                                string pin;
                                cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI 4-znamenkasti PIN kod (bankovne kartice) za ovaj nalog.\n\tUnos: ";
                                cin>>pin;
                                tekuci.setPinKod(pin);
                                cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali PIN kod racuna. Novi PIN kod naloga: "<<pin<<endl;
                                break;
                            }
                            default: {
                                system("cls");
                                cout<<"\n\tGRESKA: Odabrana opcija podatka nepostojeca!"<<endl;
                                break;
                            }
                        }
                        pronadjen=true;
                        break;
                    }
                }

                if(!pronadjen)
                {
                    for(auto& stedni : stedniRacuni)
                    {
                        if(stedni.getBrojKartice()==brojKarticeIzmjena)
                        {
                            int odabirOpcije;
                            time_t t = time(0);
                            tm* now = localtime(&t);
                            cout<<"\n\t[IZMJENA RACUNA]: Nalog je uspjesno pronadjen u bazi podataka.\n\t_________________________________________________\n\t| 1. Broj racuna: "<<stedni.getBrojKartice()<<"\t\t|\n\t|    Vrsta racuna: Stedni\t\t\t|\n\t| 2. Datum isteka (mjesec/godina): "<<stedni.getDatumIstekaKartice()<<"\t|\n\t| 3. Stanje: "<<stedni.getStanjeRacuna()<<" KM\t\t\t\t|\n\t| 4. Dozvoljeno prekoracenje: "<<stedni.getDozvoljenoPrekoracenje()<<".00 KM\t|\n\t| 5. CVV (Card Verification Value): "<<stedni.getCVV()<<"\t\t|\n\t| 6. PIN kod: "<<stedni.getPinKod()<<"\t\t\t\t|\n\t|    Pristup Log:\t\t\t\t|\n\t|    ";
                            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite broj opcije koju zelite izmijeniti: ";
                            cin>>odabirOpcije;
                            switch(odabirOpcije)
                            {
                                case 1: {
                                    string brojKartice;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI broj racuna za ovaj nalog.\n\tUnos: ";
                                    cin>>brojKartice;
                                    stedni.setBrojKartice(brojKartice);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali broj racuna. Novi broj racuna naloga: "<<brojKartice<<endl;
                                    break;
                                }
                                case 2: {
                                    string mjesec, godina;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI datum isteka za ovaj nalog.\n\tUnesite mjesec isteka (01-12): ";
                                    cin>>mjesec;
                                    cout<<"\n\tUnesite godinu isteka (dvoznamenkasti format; 2026 -> 26): ";
                                    cin>>godina;
                                    mjesec+='/';
                                    mjesec+=godina;
                                    stedni.setDatumIstekaKartice(mjesec);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali datum isteka racuna. Novi datum isteka naloga: "<<mjesec<<endl;
                                    break;
                                }
                                case 3: {
                                    float stanjeRacuna;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVO stanje (iznos) za ovaj nalog u KM.\n\tUnos: ";
                                    cin>>stanjeRacuna;
                                    stedni.setStanjeRacuna(stanjeRacuna);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali iznos na racunu. Novo stanje naloga: "<<stanjeRacuna<<" KM."<<endl;
                                    break;
                                }
                                case 4: {
                                    int dozvoljenoPrekoracenje;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVO dozvoljeno prekoracenje za ovaj nalog u KM.\n\tUnos: ";
                                    cin>>dozvoljenoPrekoracenje;
                                    stedni.setDozvoljenoPrekoracenje(dozvoljenoPrekoracenje);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali dozvoljeno prekoracenje racuna.\n\tNovo dozvoljeno prekoracenje naloga: "<<dozvoljenoPrekoracenje<<".00 KM."<<endl;
                                    break;
                                }
                                case 5: {
                                    string cvv;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI 3-znamenkasti CVV (Card Verification Value) za ovaj nalog.\n\tUnos: ";
                                    cin>>cvv;
                                    stedni.setCVV(cvv);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali CVV racuna. Novi CVV naloga: "<<cvv<<endl;
                                    break;
                                }
                                case 6: {
                                    string pin;
                                    cout<<"\n\t[IZMJENA RACUNA]: Unesite NOVI 4-znamenkasti PIN kod (bankovne kartice) za ovaj nalog.\n\tUnos: ";
                                    cin>>pin;
                                    stedni.setPinKod(pin);
                                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                                    this_thread::sleep_for(std::chrono::seconds(2));
                                    system("cls");
                                    cout<<"\n\t[IZMJENA RACUNA]: Uspjesno ste azurirali PIN kod racuna. Novi PIN kod naloga: "<<pin<<endl;
                                    break;
                                }
                                default: {
                                    system("cls");
                                    cout<<"\n\tGRESKA: Odabrana opcija podatka nepostojeca!"<<endl;
                                    break;
                                }
                            }
                            pronadjen=true;
                            break;
                        }
                    }
                }

                if(!pronadjen)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Nijedan racun u bazi ne odgovara broju: "<<brojKarticeIzmjena<<endl;
                }
                break;
            }
            case 3: {
                system("cls");
                cout<<"\n\t[PRETRAGA RACUNA]\n\n\tUnesite broj racuna kako biste zapoceli pretragu.\n\tUnos: ";
                string brojKarticePregled;
                cin>>brojKarticePregled;
                cout<<"\n\t  Pretraga racuna u bazi podataka..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                bool pronadjen = false;
                for(const auto& tekuci : tekuciRacuni)
                {
                    if(tekuci.getBrojKartice()==brojKarticePregled)
                    {
                        time_t t = time(0);
                        tm* now = localtime(&t);
                        cout<<"\n\t[PRETRAGA RACUNA]: Nalog je uspjesno pronadjen u bazi podataka.\n\t_________________________________________\n\t| Broj racuna: "<<tekuci.getBrojKartice()<<"\t\t|\n\t| Vrsta racuna: Tekuci\t\t\t|\n\t| Datum isteka (mjesec/godina): "<<tekuci.getDatumIstekaKartice()<<"\t|\n\t| Stanje: "<<tekuci.getStanjeRacuna()<<" KM\t\t\t|\n\t| Dozvoljeno prekoracenje: "<<tekuci.getDozvoljenoPrekoracenje()<<".00 KM\t|\n\t| CVV (Card Verification Value): "<<tekuci.getCVV()<<"\t|\n\t| PIN kod: "<<tekuci.getPinKod()<<"\t\t\t\t|\n\t| Pristup Log:\t\t\t\t|\n\t| ";
                        cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                        cout<<"\n\t  Pritisnite bilo koju tipku za povratak u administratorski meni."<<endl;
                        _getch();
                        system("cls");
                        pronadjen=true;
                        break;
                    }
                }

                if(!pronadjen)
                {
                    for(const auto& stedni : stedniRacuni)
                    {
                        if(stedni.getBrojKartice()==brojKarticePregled)
                        {
                            time_t t = time(0);
                            tm* now = localtime(&t);
                            cout<<"\n\t[PRETRAGA RACUNA]: Nalog je uspjesno pronadjen u bazi podataka.\n\t_________________________________________\n\t| Broj racuna: "<<stedni.getBrojKartice()<<"\t\t|\n\t| Vrsta racuna: Stedni\t\t\t|\n\t| Datum isteka (mjesec/godina): "<<stedni.getDatumIstekaKartice()<<"\t|\n\t| Stanje: "<<stedni.getStanjeRacuna()<<" KM\t\t\t|\n\t| Dozvoljeno prekoracenje: "<<stedni.getDozvoljenoPrekoracenje()<<".00 KM\t|\n\t| CVV (Card Verification Value): "<<stedni.getCVV()<<"\t|\n\t| PIN kod: "<<stedni.getPinKod()<<"\t\t\t\t|\n\t| Pristup Log:\t\t\t\t|\n\t| ";
                            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                            cout<<"\n\t  Pritisnite bilo koju tipku za povratak u administratorski meni."<<endl;
                            _getch();
                            system("cls");
                            pronadjen=true;
                            break;
                        }
                    }
                }

                if(!pronadjen)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Nijedan racun u bazi ne odgovara broju: "<<brojKarticePregled<<endl;
                }
                break;
            }
            case 4: {
                system("cls");
                cout<<"\n\t[BRISANJE RACUNA]\n\n\tUnesite broj racuna kako biste zapoceli proces brisanja.\n\tUnos: ";
                string brojKarticeBrisanje;
                cin >> brojKarticeBrisanje;
                cout<<"\n\t  Pretraga racuna u bazi podataka..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                bool pronadjen = false;
                for(auto& tekuci : tekuciRacuni)
                {
                    if(tekuci.getBrojKartice()==brojKarticeBrisanje)
                    {
                        pronadjen=true;
                        string pin;
                        cout<<"\n\tUnesite PIN kod racuna kako biste nastavili sa brisanjem.\n\tUnos: ";
                        cin>>pin;

                        if(tekuci.getPinKod()!=pin)
                        {
                            system("cls");
                            cout<<"\n\tGRESKA: Pogresan PIN kod racuna!"<<endl;
                        }
                        else
                        {
                            auto itTekuci = remove_if(tekuciRacuni.begin(), tekuciRacuni.end(), [brojKarticeBrisanje](const TekuciRacun& tekuci)
                            {
                                return tekuci.getBrojKartice() == brojKarticeBrisanje;
                            });
                            tekuciRacuni.erase(itTekuci, tekuciRacuni.end());
                            cout<<"\n\t  Brisanje tekuceg racuna iz baze podataka..."<<endl;
                            this_thread::sleep_for(std::chrono::seconds(2));
                            system("cls");
                            cout<<"\n\t[BRISANJE RACUNA]: Uspjesno ste izbrisali tekuci racun iz baze podataka. Broj izbrisanog racuna: "<<brojKarticeBrisanje<<endl;
                        }
                    }
                }

                if(!pronadjen)
                {
                    for(auto& stedni : stedniRacuni)
                    {
                        if(stedni.getBrojKartice()==brojKarticeBrisanje)
                        {
                            pronadjen=true;
                            string pin;
                            cout<<"\n\tUnesite PIN kod racuna kako biste nastavili sa brisanjem.\n\tUnos: ";
                            cin>>pin;

                            if(stedni.getPinKod()!=pin)
                            {
                                system("cls");
                                cout<<"\n\tGRESKA: Pogresan PIN kod racuna!"<<endl;
                            }
                            else
                            {
                                auto itStedni = remove_if(stedniRacuni.begin(), stedniRacuni.end(), [brojKarticeBrisanje](const StedniRacun& stedni)
                                {
                                    return stedni.getBrojKartice() == brojKarticeBrisanje;
                                });
                                stedniRacuni.erase(itStedni, stedniRacuni.end());
                                cout<<"\n\t  Brisanje stednog racuna iz baze podataka..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[BRISANJE RACUNA]: Uspjesno ste izbrisali stedni racun iz baze podataka. Broj izbrisanog racuna: "<<brojKarticeBrisanje<<endl;
                            }
                        }
                    }
                }

                if(!pronadjen)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Nijedan racun u bazi ne odgovara broju: "<<brojKarticeBrisanje<<endl;
                }
                break;
            }
            case 5:
                system("cls");
                cout<<"\n\tNAZAD: Vratili ste se u root meni!"<<endl;
                break;
            default:
                system("cls");
                cout<<"\n\tGRESKA: Odabrana opcija nepostojeca!"<<endl;
                break;
        }
    }
    while(unos!=5);
}

#endif // ADMINRACUNI_H_INCLUDED
