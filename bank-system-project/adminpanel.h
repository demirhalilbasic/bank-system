#ifndef ADMINPANEL_H_INCLUDED
#define ADMINPANEL_H_INCLUDED

void adminPanel()
{
    int unos, pristupOpciji=0;
    system("cls");
    cout<<"\n\t** [BANKA]: Uspjesno ste se ulogovali kao administrator, dobrodosli! **\n";
    do
    {
        if(pristupOpciji!=0)
        {
            cout<<"\n\t** [BANKA]: Ulogovani ste kao administrator! **\n";
        }
        cout<<"\n\t[ADMIN PANEL] Unesite zeljenu opciju:\n\t1. Pristup racunima u bazi\n\t2. Pristup korisnickim informacijama\n\t3. Logout\n\n\tUnos: ";
        cin>>unos;
        pristupOpciji=1;
        switch(unos)
        {
            case 1:
                system("cls");
                adminRacuni();
                break;
            case 2:
                system("cls");
                adminKorisnici();
                break;
            case 3:
                system("cls");
                cout<<"\n\tLOGOUT: Uspjesno ste se izlogovali iz sistema!"<<endl;
                break;
            default:
                system("cls");
                cout<<"\n\tGRESKA: Odabrana opcija nepostojeca!"<<endl;
                break;
        }
    }
    while(unos!=3);
}

#endif // ADMINPANEL_H_INCLUDED
