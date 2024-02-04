#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

bool provjeraKorisnik(const vector<User>&, const string&, const string&, bool&);

void login()
{
    int pokusaj=0, ponovoLoginGreska=0;
    char ponovoLogin;
    string email, password;
    cout<<"\n\t** [BANKA LOGIN] Dobrodosli u sistem banke! **\n\n\t~~ PRIJAVA U SISTEM ~~\n\tUnesite Vas email: ";

    do
    {
        if(pokusaj>0)
        {
            cout<<" Molimo pokusajte ponovo. ("<<pokusaj<<"/3)\n\n\t** [BANKA LOGIN] Dobrodosli u sistem banke! **\n\n\t~~ PRIJAVA U SISTEM ~~\n\tUnesite ponovo Vas email: ";
        }
        cin >> email;
        cout<<"\tUnesite Vasu lozinku: ";
        cin>>password;

        bool permission = false;
        if(provjeraKorisnik(admins, email, password, permission))
        {
            adminPanel();
            pokusaj=0;
            cout<<"\n\t** [BANKA LOGIN]: Dobrodosli ponovo! **\n\n\tDa li se zelite ponovo prijaviti u sistem? (Y/N)\n\tUnos: ";
            do
            {
                if(ponovoLoginGreska>0)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\n\tDa li se zelite ponovo prijaviti u sistem? (Y/N)\n\tUnos: ";
                }
                cin>>ponovoLogin;
                ponovoLoginGreska=1;
            }
            while((ponovoLogin!='Y')&&(ponovoLogin!='y')&&(ponovoLogin!='N')&&(ponovoLogin!='n'));
            if((ponovoLogin=='Y')||(ponovoLogin=='y'))
            {
                ponovoLoginGreska=0;
                cout<<"\n\t** [BANKA LOGIN]: Dobrodosli ponovo! **\n\n\t~~ PRIJAVA U SISTEM ~~\n\tUnesite Vas email: ";
            }
            else
            {
                system("cls");
                cout<<"\n\t** [BANKA LOGIN]: Hvala Vam na koristenju sistema banke! **"<<endl;
                return;
            }
        }
        else if(provjeraKorisnik(users, email, password, permission))
        {
            userPanel();
            pokusaj=0;
            cout<<"\n\t** [BANKA LOGIN]: Dobrodosli ponovo! **\n\n\tDa li se zelite ponovo prijaviti u sistem? (Y/N)\n\tUnos: ";
            do
            {
                if(ponovoLoginGreska>0)
                {
                    system("cls");
                    cout<<"\n\tGRESKA: Molimo unesite 'Y' (Yes) ili 'N' (No)!\n\n\tDa li se zelite ponovo prijaviti u sistem? (Y/N)\n\tUnos: ";
                }
                cin>>ponovoLogin;
                ponovoLoginGreska=1;
            }
            while((ponovoLogin!='Y')&&(ponovoLogin!='y')&&(ponovoLogin!='N')&&(ponovoLogin!='n'));
            if((ponovoLogin=='Y')||(ponovoLogin=='y'))
            {
                ponovoLoginGreska=0;
                cout<<"\n\t** [BANKA LOGIN]: Dobrodosli ponovo! **\n\n\t~~ PRIJAVA U SISTEM ~~\n\tUnesite Vas email: ";
            }
            else
            {
                system("cls");
                cout<<"\n\t** [BANKA LOGIN]: Hvala Vam na koristenju sistema banke! **"<<endl;
                return;
            }
        }
        else
        {
            system("cls");
            cout<<"\n\tGRESKA: Pogresan email ili lozinka!";
            pokusaj++;
        }
    }
    while(pokusaj<=2);

    system("cls");
    cout<<"\n\tFATAL GRESKA: Pogresan unos podataka (3/3)! Molimo pokusajte kasnije."<<endl;
    return;
}

bool provjeraKorisnik(const vector<User>& users, const string& email, const string& password, bool& permission)
{
    for(const auto& user : users)
    {
        if((user.email==email)&&(user.password == password))
        {
            permission=user.permission;
            prijavljenJMBG=user.jmbg;
            return true;
        }
    }
    return false;
}

#endif // LOGIN_H_INCLUDED
