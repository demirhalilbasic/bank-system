#ifndef USERKREDITI_H_INCLUDED
#define USERKREDITI_H_INCLUDED

class Kredit {

    private:
        string brojRacuna;
        int brojKredita;
        int idKredita;
        float iznosKredita;
        int trajanjeKredita;
        float mjesecnaRata;
        float kamata;

    public:
        Kredit():
            brojRacuna("0000000000000000"),
            brojKredita(0),
            idKredita(0),
            iznosKredita(0.00),
            trajanjeKredita(0),
            mjesecnaRata(0.00),
            kamata(0.00) {}

        void izracunajMjesecnuRatu() {
            mjesecnaRata = (iznosKredita + iznosKredita * kamata) / trajanjeKredita;
        }

        void prikaziInformacije() const {
            time_t t = time(0);
            tm* now = localtime(&t);
            cout<<"\n\t[KREDITNE INFORMACIJE]: Kreditne informacije pronadjene u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| ID kredita: "<<idKredita<<"\n\t| Ukupan (pocetni) iznos kredita: "<<iznosKredita<<" KM\n\t| Preostalo rata za isplatu (mjeseci): "<<trajanjeKredita<<"\n\t| Kamata: "<<kamata*100<<" %\n\t| Iznos mjesecne rate kredita: "<<mjesecnaRata<<" KM\n\t| Pristup Log:\n\t| ";
            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
        }

        int dodajNovogKlijenta(int kdk, string brojProslijedjenogRacuna) {
            cin >> iznosKredita;
            if((kdk/3)*10<iznosKredita)
            {
                system("cls");
                cout<<"\n\tGRESKA: Zeljeni iznos kredita prevazilazi Vase platezne mogucnosti!"<<endl;
                return 0;
            }
            else if((iznosKredita<1000)||(iznosKredita>100000))
            {
                system("cls");
                cout<<"\n\tGRESKA: Molimo Vas da se sluzite dozvoljenim rasponom kredita od 1 000 KM do 100 000 KM!"<<endl;
                return 0;
            }

            do
            {
                cout<<"\n\tUnesite zeljenu duzinu trajanja kredita (u mjesecima).\n\tMinimalan broj mjeseci: 1, Maksimalan broj mjeseci: 240 (20 godina)\n\tUnos: ";
                cin >> trajanjeKredita;
            }
            while((trajanjeKredita<=0)||(trajanjeKredita>240));

            if (trajanjeKredita <= 12) {
                kamata = 0.05;
            } else {
                kamata = 0.08;
            }
            izracunajMjesecnuRatu();

            brojRacuna=brojProslijedjenogRacuna;
            brojKredita++;
            idKredita = brojKredita;
            cout<<"\n\t  Na Vas iznos primjenjuje se kamatna stopa u iznosu od "<<kamata*100<<" %..."<<endl;
            this_thread::sleep_for(std::chrono::seconds(2));
            cout<<"\n\t  Biljezenje kreditne aktivnosti u bazi..."<<endl;
            this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
            cout<<"\n\t[IZDAVANJE KREDITA]: Uspjesno Vam je izdat kredit u iznosu od: "<<iznosKredita<<" KM.\n\tKredit Vam je izdat na period od "<<trajanjeKredita<<" mjeseci."<<endl;
            for(auto& tekuci : tekuciRacuni)
            {
                if(tekuci.getBrojKartice()==brojRacuna)
                {
                    tekuci.dodajStanjeRacuna(iznosKredita);
                    tekuci.biljeziTransakciju("BANKA (Kredit)", brojRacuna, iznosKredita);
                }
            }
            return 1;
        }

        string getBrojRacuna() { return brojRacuna; }
        int getBrojKredita() { return brojKredita; }
        int getIdKredita() const { return idKredita; }
        float getIznosKredita() const { return iznosKredita; }
        int getTrajanjeKredita() const { return trajanjeKredita; }
        float getKamata() const { return kamata; }
        float getMjesecnaRata() const { return mjesecnaRata; }

        void setBrojRacuna(string broj) { brojRacuna = broj; }
        void minusTrajanjeKredita(int trajanje) { trajanjeKredita -= trajanje; }

};

vector<Kredit> krediti;

void opcijeKredita()
{
    int unos;
    do
    {
        cout<<"\n\t** [BANKA]: Ulogovani ste kao korisnik! **\n\t~~ Nalazite se u root/kreditne mogucnosti podmeniju ~~\n";
        cout<<"\n\t[KORISNICKI PANEL] Unesite zeljenu opciju:\n\t1. Izdavanje novog kredita\n\t2. Isplata zeljenog broja rata kredita\n\t3. Isplata svih rata kredita\n\t4. Pregled kreditnih informacija\n\t5. Nazad\n\n\tUnos: ";
        cin>>unos;
        switch(unos)
        {
            case 1: {
                bool provjeraPovezanRacun=false, racunJeStedni=false, vecKlijent=false, uMinusu=false;
                int kalkulacijeDozvoleKredita=0, povratna=1;
                string brojRacuna="0";

                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacuna=user.brojKartice;
                        for(auto& tekuci : tekuciRacuni)
                        {
                            if(tekuci.getBrojKartice()==brojRacuna)
                            {
                                if(tekuci.getStanjeRacuna()<0.00)
                                {
                                    if(tekuci.getStanjeRacuna()+tekuci.getDozvoljenoPrekoracenje()<0)
                                    {
                                        uMinusu=true;
                                    }
                                }
                                kalkulacijeDozvoleKredita=tekuci.getDozvoljenoPrekoracenje();
                                provjeraPovezanRacun=true;
                            }
                        }
                        for(auto& stedni : stedniRacuni)
                        {
                            if(stedni.getBrojKartice()==brojRacuna)
                            {
                                racunJeStedni=true;
                            }
                        }
                    }
                }

                for (vector<Kredit>::iterator it = krediti.begin(); it != krediti.end(); ++it)
                {
                    Kredit& k = *it;
                    if (k.getBrojRacuna() == brojRacuna)
                    {
                        vecKlijent=true;
                        break;
                    }
                }

                if(vecKlijent==true)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Vec ste klijent kreditne pogodnosti.\n\t** Prvo otplatite prethodni kredit kako bi pristupili izdavanju novog. **"<<endl;
                }
                else if(racunJeStedni==true)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Kreditne pogodnosti dostupne su iskljucivo za tekuce racune.\n\t** Za vise informacija, molimo Vas obratite se administraciji. **"<<endl;
                }
                else if(provjeraPovezanRacun==false)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Vas korisnicki nalog nije povezan ni sa jednim racunom!\n\t** Ukoliko smatrate da nesto nije u redu, molimo Vas obratite se administraciji. **"<<endl;
                }
                else if(uMinusu==true)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Prekoracili ste dozvoljeni limit, stoga nije moguce zapoceti postupak izdavanja kredita.\n\t** Za vise informacija, molimo Vas obratite se administraciji. **"<<endl;
                }
                else
                {
                    system("cls");
                    cout<<"\n\tZapoceli ste postupak izdavanja novog kredita. Slijedite daljnje upute.\n\t[IZDAVANJE KREDITA]\n\n\tUnesite zeljeni iznos kredita u KM.\n\tUnos: ";
                    Kredit noviKredit;
                    povratna=noviKredit.dodajNovogKlijenta(kalkulacijeDozvoleKredita, brojRacuna);
                    if(povratna!=0)
                    {
                        krediti.push_back(noviKredit);
                    }
                }
                break;
            }
            case 2: {
                string brojRacuna="0";
                bool pronadjen=false;
                system("cls");
                cout<<"\n\t  Priprema kreditnih informacija..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacuna=user.brojKartice;
                        for (Kredit& k : krediti)
                        {
                            if (k.getBrojRacuna() == brojRacuna)
                            {
                                char upitIsplata;
                                int unosMjeseci;
                                pronadjen=true;
                                k.prikaziInformacije();
                                cout<<"\n\t  Koliko rata (mjeseci) zelite isplatiti?\n\t  Unos: ";
                                cin>>unosMjeseci;
                                if(unosMjeseci<=0)
                                {
                                    system("cls");
                                    cout<<"\n\tGRESKA: Minimalan broj rata (mjeseci) za isplatu je 1."<<endl;
                                }
                                else if(unosMjeseci>k.getTrajanjeKredita())
                                {
                                    system("cls");
                                    cout<<"\n\tGRESKA: Maksimalan broj rata (mjeseci) za isplatu je "<<k.getTrajanjeKredita()<<"."<<endl;
                                }
                                else
                                {
                                    float ukupnaRata=unosMjeseci*k.getMjesecnaRata();
                                    cout<<"\n\t  Da li zelite isplatiti sljedeci broj rata: "<<unosMjeseci<<", u ukupnom iznosu od "<<ukupnaRata<<" KM? (Y/N)\n\t  Unos: ";
                                    int upitIsplataGreska=0;
                                    do
                                    {
                                        if(upitIsplataGreska>0)
                                        {
                                            system("cls");
                                            cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\n\tDa li zelite isplatiti sljedeci broj rata: "<<unosMjeseci<<", u ukupnom iznosu od "<<ukupnaRata<<" KM? (Y/N)\n\t  Unos: ";
                                        }
                                        cin>>upitIsplata;
                                        upitIsplataGreska=1;
                                    }
                                    while((upitIsplata!='Y')&&(upitIsplata!='y')&&(upitIsplata!='N')&&(upitIsplata!='n'));
                                    if((upitIsplata=='Y')||(upitIsplata=='y'))
                                    {
                                        upitIsplataGreska=0;
                                        system("cls");
                                        for(auto& tekuci : tekuciRacuni)
                                        {
                                            if(tekuci.getBrojKartice()==brojRacuna)
                                            {
                                                if(tekuci.getStanjeRacuna()+tekuci.getDozvoljenoPrekoracenje()<ukupnaRata)
                                                {
                                                    cout<<"\n\tGRESKA: Isplata rate kredita u iznosu od "<<ukupnaRata<<" KM prevazilazi Vase platezne mogucnosti."<<endl;
                                                }
                                                else
                                                {
                                                    tekuci.oduzmiStanjeRacuna(ukupnaRata);
                                                    tekuci.biljeziTransakciju(brojRacuna, "BANKA (Kredit)", ukupnaRata);
                                                    k.minusTrajanjeKredita(unosMjeseci);
                                                    if(k.getTrajanjeKredita()<=0)
                                                    {
                                                        k.setBrojRacuna("0");
                                                    }
                                                    system("cls");
                                                    cout<<"\n\t  Isplata rate kredita..."<<endl;
                                                    this_thread::sleep_for(std::chrono::seconds(2));
                                                    cout<<"\n\t** [KREDIT ISPLATA]: Uspjesno ste isplatili ratu kredita u iznosu od "<<ukupnaRata<<" KM. **"<<endl;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        cout<<"\n\t** [KREDIT ISPLATA]: Odustali ste od isplate kreditne rate u iznosu od "<<ukupnaRata<<" KM. **"<<endl;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }

                if(pronadjen==false)
                {
                    cout<<"\n\tGRESKA: Prvo morate podici kredit kako biste izvrsili isplatu."<<endl;
                }
                break;
            }
            case 3: {
                string brojRacuna="0";
                bool pronadjen=false;
                system("cls");
                cout<<"\n\t  Priprema kredita za isplatu..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacuna=user.brojKartice;
                        for (Kredit& k : krediti)
                        {
                            if (k.getBrojRacuna() == brojRacuna)
                            {
                                char upitIsplata;
                                pronadjen=true;
                                k.prikaziInformacije();
                                float ukupnaRata=k.getTrajanjeKredita()*k.getMjesecnaRata();
                                cout<<"\n\t  Da li zelite isplatite sve preostale rate, ukupno "<<ukupnaRata<<" KM? (Y/N)\n\t  Unos: ";
                                int upitIsplataGreska=0;
                                do
                                {
                                    if(upitIsplataGreska>0)
                                    {
                                        system("cls");
                                        cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\n\tDa li zelite isplatite sve preostale rate, ukupno "<<ukupnaRata<<" KM? (Y/N)\n\t  Unos: ";
                                    }
                                    cin>>upitIsplata;
                                    upitIsplataGreska=1;
                                }
                                while((upitIsplata!='Y')&&(upitIsplata!='y')&&(upitIsplata!='N')&&(upitIsplata!='n'));
                                if((upitIsplata=='Y')||(upitIsplata=='y'))
                                {
                                    upitIsplataGreska=0;
                                    system("cls");
                                    for(auto& tekuci : tekuciRacuni)
                                    {
                                        if(tekuci.getBrojKartice()==brojRacuna)
                                        {
                                            if(tekuci.getStanjeRacuna()+tekuci.getDozvoljenoPrekoracenje()<ukupnaRata)
                                            {
                                                cout<<"\n\tGRESKA: Ukupna isplata kredita u iznosu od "<<ukupnaRata<<" KM prevazilazi Vase platezne mogucnosti."<<endl;
                                            }
                                            else
                                            {
                                                tekuci.oduzmiStanjeRacuna(ukupnaRata);
                                                tekuci.biljeziTransakciju(brojRacuna, "BANKA (Kredit)", ukupnaRata);
                                                k.setBrojRacuna("0");
                                                system("cls");
                                                cout<<"\n\t  Isplata svih preostalih rata kredita..."<<endl;
                                                this_thread::sleep_for(std::chrono::seconds(2));
                                                cout<<"\n\t** [KREDIT ISPLATA]: Uspjesno ste isplatili Vas kredit u ukupnom iznosu od "<<ukupnaRata<<" KM. **"<<endl;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout<<"\n\t** [KREDIT ISPLATA]: Odustali ste od ukupne isplate kredita u iznosu od "<<ukupnaRata<<" KM. **"<<endl;
                                }
                                break;
                            }
                        }
                    }
                }

                if(pronadjen==false)
                {
                    cout<<"\n\tGRESKA: Prvo morate podici kredit kako biste izvrsili isplatu."<<endl;
                }
                break;
            }
            case 4: {
                string brojRacuna="0";
                bool pronadjen=false;
                system("cls");
                cout<<"\n\t  Priprema kreditnih informacija za prikaz..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));

                for (const auto& user : users)
                {
                    if (user.jmbg == prijavljenJMBG)
                    {
                        brojRacuna=user.brojKartice;
                        for (Kredit& k : krediti)
                        {
                            if (k.getBrojRacuna() == brojRacuna)
                            {
                                pronadjen=true;
                                k.prikaziInformacije();
                                cout<<"\n\t  Pritisnite bilo koju tipku za povratak u korisnicki meni."<<endl;
                                _getch();
                                system("cls");
                                break;
                            }
                        }
                    }
                }

                if(pronadjen==false)
                {
                    cout<<"\n\tGRESKA: Niste klijent kreditne pogodnosti."<<endl;
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

#endif // USERKREDITI_H_INCLUDED
