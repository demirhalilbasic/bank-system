#ifndef USERPANEL_H_INCLUDED
#define USERPANEL_H_INCLUDED

void userPanel()
{
    int unos, pristupOpciji=0;
    system("cls");
    cout<<"\n\t** [BANKA]: Uspjesno ste se ulogovali kao korisnik, dobrodosli! **\n";
    do
    {
        if(pristupOpciji!=0)
        {
            cout<<"\n\t** [BANKA]: Ulogovani ste kao korisnik! **\n";
        }
        cout<<"\n\t[KORISNICKI PANEL] Unesite zeljenu opciju:\n\t1. Transfer sredstava\n\t2. Historija transakcija\n\t3. Kreditne mogucnosti\n\t4. Detalji o korisnickom nalogu/racunu\n\t5. Logout\n\n\tUnos: ";
        cin>>unos;
        pristupOpciji=1;
        switch(unos)
        {
            case 1: {
                bool provjeraPovezanRacun=false, racunJeStedni=false;
                float stanjeRacuna=0.00, oduzmiIznos=0.00;
                string brojRacunaPrijem, brojRacunaSlanje="0";

                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacunaSlanje=user.brojKartice;
                        for(auto& tekuci : tekuciRacuni)
                        {
                            if(tekuci.getBrojKartice()==brojRacunaSlanje)
                            {
                                stanjeRacuna=tekuci.getStanjeRacuna()+tekuci.getDozvoljenoPrekoracenje();
                                provjeraPovezanRacun=true;
                            }
                        }
                        for(auto& stedni : stedniRacuni)
                        {
                            if(stedni.getBrojKartice()==brojRacunaSlanje)
                            {
                                racunJeStedni=true;
                            }
                        }
                    }
                }

                if(racunJeStedni==true)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Transfer sredstava iskljucivo je moguce realizovati sa tekuceg racuna.\n\t** Za vise informacija, molimo Vas obratite se administraciji. **"<<endl;
                    break;
                }

                if(provjeraPovezanRacun==false)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Vas korisnicki nalog nije povezan ni sa jednim racunom!\n\t** Ukoliko smatrate da nesto nije u redu, molimo Vas obratite se administraciji. **"<<endl;
                    break;
                }

                system("cls");
                cout<<"\n\t[TRANSFER SREDSTAVA]\n\n\tUnesite broj racuna na koji zelite izvrsiti transakciju.\n\tUnos: ";
                cin>>brojRacunaPrijem;
                cout<<"\n\t  Pretraga racuna u bazi podataka..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                if(brojRacunaPrijem==brojRacunaSlanje)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Ne mozete sami sebi prebaciti sredstva!"<<endl;
                    break;
                }

                bool pronadjen = false;
                for(auto& tekuci : tekuciRacuni)
                {
                    if(tekuci.getBrojKartice()==brojRacunaPrijem)
                    {
                        float iznos;
                        pronadjen=true;
                        int odabirOpcije;
                        time_t t = time(0);
                        tm* now = localtime(&t);

                        if(stanjeRacuna<=0.00)
                        {
                            system("cls");
                            cout<<"\n\tGRESKA: Ne raspolazete sredstvima na racunu kako biste obavili transakciju!"<<endl;
                            break;
                        }
                        else
                        {
                            cout<<"\n\t[TRANSFER SREDSTAVA]: Racun je uspjesno pronadjen u bazi podataka.\n\t_________________________________________________\n\t| Broj racuna: "<<tekuci.getBrojKartice()<<"\n\t| Vrsta racuna: Tekuci\n\t| Stanje Vaseg racuna: "<<stanjeRacuna<<" KM\n\t| Pristup Log: ";
                            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite zeljeni iznos za transfer novca na navedeni racun (u KM): ";
                        }
                        cin>>iznos;
                        if(iznos>stanjeRacuna)
                        {
                            system("cls");
                            cout<<"\n\tGRESKA: Zeljeni iznos transfera ("<<iznos<<" KM) prevazilazi stanje Vaseg racuna ("<<stanjeRacuna<<" KM)!"<<endl;
                            break;
                        }
                        else if(iznos<=0)
                        {
                            system("cls");
                            cout<<"\n\tGRESKA: Zeljeni iznos transfera ("<<iznos<<" KM) nije prihvatljiv!"<<endl;
                            break;
                        }
                        else
                        {
                            tekuci.dodajStanjeRacuna(iznos);
                            oduzmiIznos=iznos;
                            tekuci.biljeziTransakciju(brojRacunaSlanje, tekuci.getBrojKartice(), iznos);
                            cout<<"\n\t  Realizacija transfera sredstava u toku..."<<endl;
                            this_thread::sleep_for(std::chrono::seconds(2));
                            system("cls");
                            cout<<"\n\t[TRANSFER SREDSTAVA]: Uspjesno ste realizovali transfer sredstava na racun broj: "<<tekuci.getBrojKartice()<<"; u iznosu od "<<iznos<<" KM."<<endl;
                        }
                    }
                }

                if(!pronadjen)
                {
                    for(auto& stedni : stedniRacuni)
                    {
                        if(stedni.getBrojKartice()==brojRacunaPrijem)
                        {
                            float iznos;
                            pronadjen=true;
                            int odabirOpcije;
                            time_t t = time(0);
                            tm* now = localtime(&t);

                            if(stanjeRacuna<=0.00)
                            {
                                system("cls");
                                cout<<"\n\tGRESKA: Ne raspolazete sredstvima na racunu kako biste obavili transakciju!"<<endl;
                            }
                            else
                            {
                                cout<<"\n\t[TRANSFER SREDSTAVA]: Racun je uspjesno pronadjen u bazi podataka.\n\t_________________________________________________\n\t| Broj racuna: "<<stedni.getBrojKartice()<<"\n\t| Vrsta racuna: Stedni\n\t| Stanje Vaseg racuna: "<<stanjeRacuna<<" KM\n\t| Pristup Log: ";
                                cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite zeljeni iznos za transfer novca na navedeni racun (u KM): ";
                            }
                            cin>>iznos;
                            if(iznos>stanjeRacuna)
                            {
                                system("cls");
                                cout<<"\n\tGRESKA: Zeljeni iznos transfera ("<<iznos<<" KM) prevazilazi stanje Vaseg racuna ("<<stanjeRacuna<<" KM)!"<<endl;
                                break;
                            }
                            else if(iznos<=0)
                            {
                                system("cls");
                                cout<<"\n\tGRESKA: Zeljeni iznos transfera ("<<iznos<<" KM) nije prihvatljiv!"<<endl;
                                break;
                            }
                            else
                            {
                                stedni.dodajStanjeRacuna(iznos);
                                oduzmiIznos=iznos;
                                stedni.biljeziTransakciju(brojRacunaSlanje, stedni.getBrojKartice(), iznos);
                                cout<<"\n\t  Realizacija transfera sredstava u toku..."<<endl;
                                this_thread::sleep_for(std::chrono::seconds(2));
                                system("cls");
                                cout<<"\n\t[TRANSFER SREDSTAVA]: Uspjesno ste realizovali transfer sredstava na racun broj: "<<stedni.getBrojKartice()<<"; u iznosu od "<<iznos<<" KM."<<endl;
                            }
                        }
                    }
                }

                if(oduzmiIznos!=0.00)
                {
                    for(auto& tekuci : tekuciRacuni)
                    {
                        if(tekuci.getBrojKartice()==brojRacunaSlanje)
                        {
                            tekuci.oduzmiStanjeRacuna(oduzmiIznos);
                        }
                    }
                }

                if(!pronadjen)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Ne postoji racun u bazi dostupan za transakciju. ("<<brojRacunaPrijem<<")"<<endl;
                }
                break;
            }
            case 2: {
                bool postojeTransakcije=false;
                string brojRacunaSlanje="0";
                system("cls");

                cout<<"\n\t  Priprema historije transakcija za prikaz..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                for (auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacunaSlanje=user.brojKartice;
                        for(auto& tekuci : tekuciRacuni)
                        {
                                const vector<Transakcija>& historija = tekuci.getHistorijaTransakcija();
                                for (auto it = historija.rbegin(); it != historija.rend(); ++it)
                                {
                                    const Transakcija& transakcija = *it;
                                    if((transakcija.brojRacunaSlanja==brojRacunaSlanje)||(transakcija.brojRacunaPrijema==brojRacunaSlanje))
                                    {
                                        if(postojeTransakcije==false)
                                        {
                                            cout<<"\n\t[HISTORIJA TRANSAKCIJA]\n"<<endl;
                                        }
                                        postojeTransakcije=true;
                                        cout << "\t["<<transakcija.datumVrijeme<<"] Broj racuna posiljaoca: "<<transakcija.brojRacunaSlanja<<" | Broj racuna primaoca: "<<transakcija.brojRacunaPrijema<<" | Iznos transfera: "<<transakcija.iznosTransfera<<" KM |"<<endl;
                                    }
                                }
                        }
                        for(auto& stedni : stedniRacuni)
                        {
                                const vector<Transakcija>& historija = stedni.getHistorijaTransakcija();
                                for (auto it = historija.rbegin(); it != historija.rend(); ++it)
                                {
                                    const Transakcija& transakcija = *it;
                                    if((transakcija.brojRacunaSlanja==brojRacunaSlanje)||(transakcija.brojRacunaPrijema==brojRacunaSlanje))
                                    {
                                        if(postojeTransakcije==false)
                                        {
                                            cout<<"\n\t[HISTORIJA TRANSAKCIJA]\n"<<endl;
                                        }
                                        postojeTransakcije=true;
                                        cout << "\t["<<transakcija.datumVrijeme<<"] Broj racuna posiljaoca: "<<transakcija.brojRacunaSlanja<<" | Broj racuna primaoca: "<<transakcija.brojRacunaPrijema<<" | Iznos transfera: "<<transakcija.iznosTransfera<<" KM |"<<endl;
                                    }
                                }
                        }
                        break;
                    }
                }

                if(postojeTransakcije==false)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Historija transakcija racuna broj ["<<brojRacunaSlanje<<"] je prazna."<<endl;
                }
                else
                {
                    cout<<"\n\t  Pritisnite bilo koju tipku za povratak u korisnicki meni."<<endl;
                    _getch();
                    system("cls");
                }
                break;
            }
            case 3:
                system("cls");
                opcijeKredita();
                break;
            case 4: {
                system("cls");
                cout<<"\n\t  Priprema korisnickog naloga i racuna za prikaz..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        bool pronadjenRacun=false;
                        string password=user.password;
                        for(int i=0; i<password.length(); i++)
                        {
                            password[i]='*';
                        }
                        time_t t = time(0);
                        tm* now = localtime(&t);
                        if(user.brojKartice=="0")
                        {
                            cout<<"\n\t[DETALJI KORISNICKOG NALOGA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<user.email<<"\n\t| Password: "<<password<<"\n\t| Status: Korisnik\n\t| Broj povezanog racuna: Nalog nije povezan\n\t| JMBG: "<<user.jmbg<<"\n\t| Ime: "<<user.ime<<"\n\t| Prezime: "<<user.prezime<<"\n\t| Pristup Log:\n\t| ";
                            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                        }
                        else
                        {
                            cout<<"\n\t[DETALJI KORISNICKOG NALOGA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<user.email<<"\n\t| Password: "<<password<<"\n\t| Status: Korisnik\n\t| Broj povezanog racuna: "<<user.brojKartice<<"\n\t| JMBG: "<<user.jmbg<<"\n\t| Ime: "<<user.ime<<"\n\t| Prezime: "<<user.prezime<<"\n\t| Pristup Log:\n\t| ";
                            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                        }

                        for(auto& tekuci : tekuciRacuni)
                        {
                            if(tekuci.getBrojKartice()==user.brojKartice)
                            {
                                pronadjenRacun=true;
                                string cvv=tekuci.getCVV(), pin=tekuci.getPinKod();
                                for(int i=0; i<cvv.length(); i++)
                                {
                                    cvv[i]='*';
                                }
                                for(int i=0; i<pin.length(); i++)
                                {
                                    pin[i]='*';
                                }
                                cout<<"\n\t[DETALJI RACUNA]: Vas korisnicki nalog je povezan sa racunom.\n\t_________________________________________\n\t| Broj racuna: "<<tekuci.getBrojKartice()<<"\n\t| Vrsta racuna: Tekuci\n\t| Datum isteka (mjesec/godina): "<<tekuci.getDatumIstekaKartice()<<"\n\t| Stanje: "<<tekuci.getStanjeRacuna()<<" KM\n\t| Dozvoljeno prekoracenje: "<<tekuci.getDozvoljenoPrekoracenje()<<".00 KM\n\t| CVV (Card Verification Value): "<<cvv<<"\n\t| PIN kod: "<<pin<<"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"<<endl;
                            }
                        }

                        if(pronadjenRacun==false)
                        {
                            for(auto& stedni : stedniRacuni)
                            {
                                if(stedni.getBrojKartice()==user.brojKartice)
                                {
                                    pronadjenRacun=true;
                                    string cvv=stedni.getCVV(), pin=stedni.getPinKod();
                                    for(int i=0; i<cvv.length(); i++)
                                    {
                                        cvv[i]='*';
                                    }
                                    for(int i=0; i<pin.length(); i++)
                                    {
                                        pin[i]='*';
                                    }
                                    cout<<"\n\t[DETALJI RACUNA]: Vas korisnicki nalog je povezan sa racunom.\n\t_________________________________________\n\t| Broj racuna: "<<stedni.getBrojKartice()<<"\n\t| Vrsta racuna: Stedni\n\t| Datum isteka (mjesec/godina): "<<stedni.getDatumIstekaKartice()<<"\n\t| Stanje: "<<stedni.getStanjeRacuna()<<" KM\n\t| Dozvoljeno prekoracenje: "<<stedni.getDozvoljenoPrekoracenje()<<".00 KM\n\t| CVV (Card Verification Value): "<<cvv<<"\n\t| PIN kod: "<<pin<<"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"<<endl;
                                }
                            }
                        }

                        if(pronadjenRacun==false)
                        {
                            cout<<"\n\tGRESKA: Vas korisnicki nalog nije povezan ni sa jednim racunom!\n\t** Ukoliko smatrate da nesto nije u redu, molimo Vas obratite se administraciji. **"<<endl;
                        }

                        cout<<"\n\t  Pritisnite bilo koju tipku za povratak u korisnicki meni."<<endl;
                        _getch();
                        system("cls");
                    }
                }
                break;
            }
            case 5:
                system("cls");
                cout<<"\n\tLOGOUT: Uspjesno ste se izlogovali iz sistema!"<<endl;
                break;
            default:
                system("cls");
                cout<<"\n\tGRESKA: Odabrana opcija nepostojeca!"<<endl;
                break;
        }
    }
    while(unos!=5);
}

#endif // USERPANEL_H_INCLUDED
