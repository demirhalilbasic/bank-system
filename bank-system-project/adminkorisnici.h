#ifndef ADMINKORISNICI_H_INCLUDED
#define ADMINKORISNICI_H_INCLUDED

void adminKorisnici()
{
    int unos;
    do
    {
        cout<<"\n\t** [BANKA]: Ulogovani ste kao administrator! **\n\t~~ Nalazite se u root/pristup korisnicima podmeniju ~~\n";
        cout<<"\n\t[ADMIN PANEL] Unesite zeljenu opciju:\n\t1. Kreiranje novog korisnika u sistemu\n\t2. Izmjena podataka postojeceg korisnika\n\t3. Pregled podataka korisnika u bazi\n\t4. Brisanje korisnika iz baze\n\t5. Nazad\n\n\tUnos: ";
        cin>>unos;
        switch(unos)
        {
            case 1:
                unosNovogKorisnika();
                break;
            case 2:
                izmjenaPodataka();
                break;
            case 3:
                pregledPodataka();
                break;
            case 4:
                brisanjeKorisnika();
                break;
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

#endif // ADMINKORISNICI_H_INCLUDED
