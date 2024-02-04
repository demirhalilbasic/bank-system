#ifndef KORISNICI_H_INCLUDED
#define KORISNICI_H_INCLUDED

struct User
{
    string email;
    string password;
    bool permission;
    string brojKartice;
    string jmbg;
    string ime;
    string prezime;
};

vector<User> admins =
    {
        {"aldina@example.com", "aldina", true, "0", "1234567891234", "Aldina", "Huskic"},
        {"demir@example.com", "demir", true, "0", "2345678912345", "Demir", "Halilbasic"}
    };

vector<User> users =
    {
        {"korisnik@example.com", "korisnik", false, "1234567891234567", "3456789123456", "Mujo", "Mujic"},
        {"korisnik2@example.com", "korisnik2", false, "2345678912345678", "4567891234567", "Marko", "Markovic"}
    };

string prijavljenJMBG="0";

void unosNovogKorisnika()
{
    User newUser;
    int provjeraCuvanjeGreska=0;
    char provjeraCuvanje;
    string status="Nepoznato";

    system("cls");
    cout<<"\n\t[KREIRANJE NOVOG KORISNIKA]\n\n\tUnesite status korisnika. (0 - Korisnik, 1 - Administrator)\n\tUnos: ";
    cin >> newUser.permission;

    if(newUser.permission)
    {
        cout<<"\n\tUnesite email administratora. (koristi se prilikom logina u sistem)\n\tUnos: ";
        cin >> newUser.email;
        cout<<"\n\tUnesite password administratora. (koristi se prilikom logina u sistem)\n\tUnos: ";
        cin >> newUser.password;
        cout<<"\n\tUnesite JMBG korisnika. (13-znamenkasti kod)\n\tUnos: ";
        cin >> newUser.jmbg;
        cout<<"\n\tUnesite ime administratora.\n\tUnos: ";
        cin >> newUser.ime;
        cout<<"\n\tUnesite prezime administratora.\n\tUnos: ";
        cin >> newUser.prezime;
        newUser.brojKartice="0";
        status="Administrator";
    }
    else
    {
        cout<<"\n\tUnesite email korisnika. (koristi se prilikom logina u sistem)\n\tUnos: ";
        cin >> newUser.email;
        cout<<"\n\tUnesite password korisnika. (koristi se prilikom logina u sistem)\n\tUnos: ";
        cin >> newUser.password;
        cout<<"\n\tUnesite broj racuna sa kojim zelite povezati korisnicki nalog. (Koristite '0' ako ne zelite sada povezati)\n\tNapomena: Korinicki nalog je moguce povezati sa racunom naknadno.\n\tUnos: ";
        cin >> newUser.brojKartice;
        cout<<"\n\tUnesite JMBG korisnika. (13-znamenkasti kod)\n\tUnos: ";
        cin >> newUser.jmbg;
        cout<<"\n\tUnesite ime korisnika.\n\tUnos: ";
        cin >> newUser.ime;
        cout<<"\n\tUnesite prezime korisnika.\n\tUnos: ";
        cin >> newUser.prezime;
        status="Korisnik";
    }

    cout<<"\n\t  Podaci se pripremaju za pohranu..."<<endl;
    this_thread::sleep_for(std::chrono::seconds(3));
    system("cls");
    time_t t = time(0);
    tm* now = localtime(&t);

    if(newUser.brojKartice=="0")
    {
        cout<<"\n\t[KREIRANJE NOVOG KORISNIKA]: Da li zelite sacuvati kreirani nalog sa sljedecim podacima? (Y/N)\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<newUser.email<<"\n\t| Password: "<<newUser.password<<"\n\t| Status: "<<status<<"\n\t| Broj povezanog racuna: Nalog nije povezan\n\t| JMBG: "<<newUser.jmbg<<"\n\t| Ime: "<<newUser.ime<<"\n\t| Prezime: "<<newUser.prezime<<"\n\t| ";
        cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unos: ";
    }
    else
    {
        cout<<"\n\t[KREIRANJE NOVOG KORISNIKA]: Da li zelite sacuvati kreirani nalog sa sljedecim podacima? (Y/N)\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<newUser.email<<"\n\t| Password: "<<newUser.password<<"\n\t| Status: "<<status<<"\n\t| Broj povezanog racuna: "<<newUser.brojKartice<<"\n\t| JMBG: "<<newUser.jmbg<<"\n\t| Ime: "<<newUser.ime<<"\n\t| Prezime: "<<newUser.prezime<<"\n\t| ";
        cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unos: ";
    }

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
        if (newUser.permission)
        {
            admins.push_back(newUser);
        }
        else
        {
            users.push_back(newUser);
        }
        cout<<"\n\t  Pohranjivanje podataka u toku..."<<endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        cout<<"\n\t[KREIRANJE NOVOG KORISNIKA] Novi korisnicki nalog uspjesno unesen u bazu."<<endl;
    }
    else
    {
        cout<<"\n\t  Odustajanje od pohrane podataka..."<<endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        cout<<"\n\t[KREIRANJE NOVOG KORISNIKA] Odustali ste od kreiranja novog korisnickog naloga."<<endl;
    }
}

void izmjenaPodataka()
{
    int pronadjen=0;
    string targetJMBG;
    system("cls");
    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]\n\n\tUnesite JMBG korisnika kako biste izmijenili zeljene podatke.\n\tUnos: ";
    cin >> targetJMBG;
    cout<<"\n\t  Pretraga naloga u bazi podataka..."<<endl;
    this_thread::sleep_for(std::chrono::seconds(2));

    for (auto& admin : admins)
    {
        if (admin.jmbg == targetJMBG)
        {
            string newValue;
            pronadjen=1;
            time_t t = time(0);
            tm* now = localtime(&t);
            cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| 1. Email: "<<admin.email<<"\n\t| 2. Password: "<<admin.password<<"\n\t|    Status: Administrator\n\t|    Broj povezanog racuna: Nalog nije povezan\n\t| 3. JMBG: "<<admin.jmbg<<"\n\t| 4. Ime: "<<admin.ime<<"\n\t| 5. Prezime: "<<admin.prezime<<"\n\t|    Pristup Log:\n\t|    ";
            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite broj opcije koju zelite izmijeniti: ";
            int choice;
            cin >> choice;

            switch (choice)
            {
                case 1: {
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI email za ovaj nalog.\n\tUnos: ";
                    cin>>newValue;
                    admin.email = newValue;
                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali email. Novi email: "<<admin.email<<endl;
                    break;
                }
                case 2: {
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI password za ovaj nalog.\n\tUnos: ";
                    cin>>newValue;
                    admin.password = newValue;
                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali password. Novi password: "<<admin.password<<endl;
                    break;
                }
                case 3: {
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI JMBG za ovaj nalog.\n\tUnos: ";
                    cin>>newValue;
                    admin.jmbg = newValue;
                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali JMBG. Novi JMBG: "<<admin.jmbg<<endl;
                    break;
                }
                case 4: {
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVO ime korisnika naloga.\n\tUnos: ";
                    cin>>newValue;
                    admin.ime = newValue;
                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali ime korisnika naloga. Novo ime: "<<admin.ime<<endl;
                    break;
                }
                case 5: {
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVO prezime korisnika naloga.\n\tUnos: ";
                    cin>>newValue;
                    admin.prezime = newValue;
                    cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                    this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali prezime korisnika naloga. Novo ime: "<<admin.prezime<<endl;
                    break;
                }
                default: {
                    system("cls");
                    cout<<"\n\tGRESKA: Odabrana opcija podatka nepostojeca!"<<endl;
                    break;
                }
            }
        }
    }

    if(pronadjen==0)
    {
        for (auto& user : users)
        {
            if (user.jmbg == targetJMBG)
            {
                string newValue;
                pronadjen=1;
                time_t t = time(0);
                tm* now = localtime(&t);
                cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| 1. Email: "<<user.email<<"\n\t| 2. Password: "<<user.password<<"\n\t|    Status: Korisnik\n\t| 3. Broj povezanog racuna: "<<user.brojKartice<<"\n\t| 4. JMBG: "<<user.jmbg<<"\n\t| 5. Ime: "<<user.ime<<"\n\t| 6. Prezime: "<<user.prezime<<"\n\t|    Pristup Log:\n\t|    ";
                cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n\t  Unesite broj opcije koju zelite izmijeniti: ";
                int choice;
                cin >> choice;

                switch (choice)
                {
                    case 1: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI email za ovaj nalog.\n\tUnos: ";
                        cin>>newValue;
                        user.email = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali email. Novi email: "<<user.email<<endl;
                        break;
                    }
                    case 2: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI password za ovaj nalog.\n\tUnos: ";
                        cin>>newValue;
                        user.password = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali password. Novi password: "<<user.password<<endl;
                        break;
                    }
                    case 3: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI broj racuna koji povezujete sa korisnickim nalogom.\n\tUnos: ";
                        cin>>newValue;
                        user.brojKartice = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        if(user.brojKartice=="0")
                        {
                            cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste raskinuli vezu naloga sa korisnickim racunom."<<endl;
                        }
                        else
                        {
                            cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste povezali korisnicki nalog sa brojem racuna: "<<user.brojKartice<<endl;
                        }
                        break;
                    }
                    case 4: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVI JMBG za ovaj nalog.\n\tUnos: ";
                        cin>>newValue;
                        user.jmbg = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali JMBG. Novi JMBG: "<<user.jmbg<<endl;
                        break;
                    }
                    case 5: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVO ime korisnika naloga.\n\tUnos: ";
                        cin>>newValue;
                        user.ime = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali ime korisnika naloga. Novo ime: "<<user.ime<<endl;
                        break;
                    }
                    case 6: {
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Unesite NOVO prezime korisnika naloga.\n\tUnos: ";
                        cin>>newValue;
                        user.prezime = newValue;
                        cout<<"\n\t  Spremanje izmijenjenih podataka..."<<endl;
                        this_thread::sleep_for(std::chrono::seconds(2));
                        system("cls");
                        cout<<"\n\t[IZMJENA KORISNICKIH PODATAKA]: Uspjesno ste azurirali prezime korisnika naloga. Novo ime: "<<user.prezime<<endl;
                        break;
                    }
                    default: {
                        system("cls");
                        cout<<"\n\tGRESKA: Odabrana opcija podatka nepostojeca!"<<endl;
                        break;
                    }
                }
            }
        }
    }

    if(pronadjen==0)
    {
        system("cls");
        cout<<"\n\tGRESKA: Ne postoji korisnik u bazi sa JMBG: "<<targetJMBG<<endl;
    }
}

void pregledPodataka()
{
    int pronadjen=0;
    string targetJMBG;
    system("cls");
    cout<<"\n\t[PRETRAGA KORISNICKOG NALOGA]\n\n\tUnesite JMBG korisnika kako biste zapoceli pretragu.\n\tUnos: ";
    cin >> targetJMBG;
    cout<<"\n\t  Pretraga naloga u bazi podataka..."<<endl;
    this_thread::sleep_for(std::chrono::seconds(2));

    for (const auto& admin : admins)
    {
        if (admin.jmbg == targetJMBG)
        {
            pronadjen=1;
            time_t t = time(0);
            tm* now = localtime(&t);
            cout<<"\n\t[PRETRAGA KORISNICKOG NALOGA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<admin.email<<"\n\t| Password: "<<admin.password<<"\n\t| Status: Administrator\n\t| Broj povezanog racuna: Nalog nije povezan\n\t| JMBG: "<<admin.jmbg<<"\n\t| Ime: "<<admin.ime<<"\n\t| Prezime: "<<admin.prezime<<"\n\t| Pristup Log:\n\t| ";
            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
            cout<<"\n\t  Pritisnite bilo koju tipku za povratak u administratorski meni."<<endl;
            _getch();
            system("cls");
        }
    }

    if(pronadjen==0)
    {
        for (const auto& user : users)
        {
            if (user.jmbg == targetJMBG)
            {
                pronadjen=1;
                time_t t = time(0);
                tm* now = localtime(&t);
                if(user.brojKartice=="0")
                {
                    cout<<"\n\t[PRETRAGA KORISNICKOG NALOGA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<user.email<<"\n\t| Password: "<<user.password<<"\n\t| Status: Korisnik\n\t| Broj povezanog racuna: Nalog nije povezan\n\t| JMBG: "<<user.jmbg<<"\n\t| Ime: "<<user.ime<<"\n\t| Prezime: "<<user.prezime<<"\n\t| Pristup Log:\n\t| ";
                    cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                }
                else
                {
                    cout<<"\n\t[PRETRAGA KORISNICKOG NALOGA]: Nalog je uspjesno pronadjen u bazi podataka.\n\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t| Email: "<<user.email<<"\n\t| Password: "<<user.password<<"\n\t| Status: Korisnik\n\t| Broj povezanog racuna: "<<user.brojKartice<<"\n\t| JMBG: "<<user.jmbg<<"\n\t| Ime: "<<user.ime<<"\n\t| Prezime: "<<user.prezime<<"\n\t| Pristup Log:\n\t| ";
                    cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                }
                cout<<"\n\t  Pritisnite bilo koju tipku za povratak u administratorski meni."<<endl;
                _getch();
                system("cls");
            }
        }
    }

    if(pronadjen==0)
    {
        system("cls");
        cout<<"\n\tGRESKA: Ne postoji korisnik u bazi sa JMBG: "<<targetJMBG<<endl;
    }
}

void brisanjeKorisnika()
{
    int pronadjen=0;
    string targetJMBG;
    system("cls");
    cout<<"\n\t[BRISANJE KORISNICKOG NALOGA]\n\n\tUnesite JMBG korisnika kako biste zapoceli proces brisanja.\n\tUnos: ";
    cin >> targetJMBG;
    cout<<"\n\t  Pretraga naloga u bazi podataka..."<<endl;
    this_thread::sleep_for(std::chrono::seconds(2));

    for (auto it = admins.begin(); it != admins.end(); ++it)
    {
        if (it->jmbg == targetJMBG)
        {
            pronadjen=1;
            it = admins.erase(it);
            --it;
            cout<<"\n\t  Brisanje administratorskog naloga iz baze podataka..."<<endl;
            this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
            cout<<"\n\t[BRISANJE RACUNA]: Uspjesno ste izbrisali administratorski nalog iz baze podataka. Broj izbrisanog naloga: "<<targetJMBG<<endl;
        }
    }

    if(pronadjen==0)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if (it->jmbg == targetJMBG)
            {
                pronadjen=1;
                it = users.erase(it);
                --it;
                cout<<"\n\t  Brisanje korisnickog naloga iz baze podataka..."<<endl;
                this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");
                cout<<"\n\t[BRISANJE RACUNA]: Uspjesno ste izbrisali korisnicki nalog iz baze podataka. Broj izbrisanog naloga: "<<targetJMBG<<endl;
            }
        }
    }

    if(pronadjen==0)
    {
        system("cls");
        cout<<"\n\tGRESKA: Ne postoji korisnik u bazi sa JMBG: "<<targetJMBG<<endl;
    }
}

#endif // KORISNICI_H_INCLUDED
