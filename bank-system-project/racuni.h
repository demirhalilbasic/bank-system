#ifndef RACUNI_H_INCLUDED
#define RACUNI_H_INCLUDED

struct Transakcija {
    string datumVrijeme;
    string brojRacunaSlanja;
    string brojRacunaPrijema;
    float iznosTransfera;
};

class Racun {

    private:
        string brojKartice;
        string datumIstekaKartice;
        float stanjeRacuna;
        int dozvoljenoPrekoracenje;
        string cvv;
        string pinKod;

        vector<Transakcija> historijaTransakcija;

    public:
        Racun():
            brojKartice("0000000000000000"),
            datumIstekaKartice("00/00"),
            stanjeRacuna(0.00),
            dozvoljenoPrekoracenje(static_cast<int>(3*stanjeRacuna)),
            cvv("000"),
            pinKod("0000") {}

    string getBrojKartice() const { return brojKartice; }
    string getDatumIstekaKartice() const { return datumIstekaKartice; }
    float getStanjeRacuna() const { return stanjeRacuna; }
    int getDozvoljenoPrekoracenje() const { return dozvoljenoPrekoracenje; }
    string getCVV() const { return cvv; }
    string getPinKod() const { return pinKod; }

    void setBrojKartice(string broj) { brojKartice = broj; }
    void setDatumIstekaKartice(string datum) { datumIstekaKartice = datum; }
    void setStanjeRacuna(float stanje) { stanjeRacuna = stanje; }
    void dodajStanjeRacuna(float iznos) { stanjeRacuna += iznos; }
    void oduzmiStanjeRacuna(float iznos) { stanjeRacuna -= iznos; }
    void setDozvoljenoPrekoracenje(int dozvoljeno) { dozvoljenoPrekoracenje = dozvoljeno; }
    void setCVV(string cvvCode) { cvv = cvvCode; }
    void setPinKod(string pin) { pinKod = pin; }

    void biljeziTransakciju(const string& brojRacunaSlanja, const string& brojRacunaPrijema, float iznos) {
        Transakcija novaTransakcija;

        time_t t = time(nullptr);
        tm* now = localtime(&t);

        ostringstream oss;
        oss << setw(2) << setfill('0') << now->tm_mday << '/'
            << setw(2) << setfill('0') << now->tm_mon + 1 << ' '
            << setw(2) << setfill('0') << now->tm_hour << ':'
            << setw(2) << setfill('0') << now->tm_min;
        novaTransakcija.datumVrijeme = oss.str();

        novaTransakcija.brojRacunaSlanja = brojRacunaSlanja;
        novaTransakcija.brojRacunaPrijema = brojRacunaPrijema;
        novaTransakcija.iznosTransfera = iznos;

        historijaTransakcija.push_back(novaTransakcija);
    }

    vector<Transakcija> getHistorijaTransakcija() const {
        return historijaTransakcija;
    }

};

class TekuciRacun : public Racun {

    private:
        float mjesecnoPrimanje;

    public:
        void unosTekuci() {
            string brojKartice, brojProtokol;
            mt19937 generator(time(0));
            uniform_int_distribution<int> distribution(0, 9);
            for(int i=0; i<12; i++)
            {
                brojKartice+=to_string(distribution(generator));
            }
            cout<<"\t1. Uspjesno je generisan tekuci racun broj: "<<brojKartice<<""<<endl;
            cout<<"\t   Unesite 4 posljednja protokolna broja kartice: ";
            cin>>brojProtokol;
            brojKartice+=brojProtokol;
            setBrojKartice(brojKartice);

            int datumIsteka;
            string noviDatum;
            time_t t = time(0);
            tm* now = localtime(&t);
            cout<<"\n\t** Uspjesno je kreiran tekuci racun broj: "<<brojKartice<<"\n\n\t2. Koliko godina zelite da nalog traje (pocev od danas): ";
            cin>>datumIsteka;
            now->tm_year+=datumIsteka;
            ostringstream oss;
            oss<<put_time(now, "%m/%y");
            noviDatum=oss.str();
            setDatumIstekaKartice(noviDatum);

            cout<<"\n\t** Uspjesno je podesen datum vazenja kartice. Kartica istice (mjesec/godina): "<<noviDatum<<"\n\n\t** Pocetno stanje tekuceg racuna postavljeno na 0.00 KM.\n\t   Stanje racuna je moguce promijeniti naknadno."<<endl;
            setStanjeRacuna(0.00);

            cout<<"\n\t3. Unesite ukupna mjesecna primanja korisnika u KM. Zaokruziti na dvije decimale: ";
            cin>>mjesecnoPrimanje;
            setDozvoljenoPrekoracenje(static_cast<int>(3*mjesecnoPrimanje));

            cout<<"\n\t** Shodno ukupnom mjesecnom primanju u iznosu od "<<mjesecnoPrimanje<<" KM, tekuci racun\n\t   raspolaze sa mogucim prekoracenjem u iznosu od "<<static_cast<int>(3*mjesecnoPrimanje)<<".00 KM.\n\n\t4. Unesite 3-znamenkasti CVV (Card Verification Value): ";
            string cvv;
            cin>>cvv;
            setCVV(cvv);

            cout<<"\n\t** Uspjesno ste unijeli CVV za bankovnu karticu.\n\n\t5. Unesite 4-znamenkasti PIN kod od racuna (bankovne kartice): ";
            string pin;
            cin>>pin;
            setPinKod(pin);
            cout<<"\n\t** Uspjesno unesen PIN kod za tekuci racun (bankovnu karticu).\n\n\t  Podaci se pripremaju za pohranu..."<<endl;
            this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            t = time(0);
            now = localtime(&t);
            cout<<"\n\t[KREIRANJE NOVOG RACUNA]: Da li zelite sacuvati kreirani nalog sa sljedecim podacima? (Y/N)\n\t_________________________________________\n\t| Broj racuna: "<<brojKartice<<"\t\t|\n\t| Vrsta racuna: Tekuci\t\t\t|\n\t| Datum isteka (mjesec/godina): "<<noviDatum<<"\t|\n\t| Stanje: 0.00 KM\t\t\t|\n\t| Dozvoljeno prekoracenje: "<<static_cast<int>(3*mjesecnoPrimanje)<<".00 KM\t|\n\t| CVV (Card Verification Value): "<<cvv<<"\t|\n\t| PIN kod: "<<pin<<"\t\t\t\t|\n\t| ";
            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t  Unos: ";
        }

};

class StedniRacun : public Racun {

    public:
        void unosStedni() {
            string brojKartice, brojProtokol;
            mt19937 generator(time(0));
            uniform_int_distribution<int> distribution(0, 9);
            for(int i=0; i<12; i++)
            {
                brojKartice+=to_string(distribution(generator));
            }
            cout<<"\t1. Uspjesno je generisan stedni racun broj: "<<brojKartice<<""<<endl;
            cout<<"\t   Unesite 4 posljednja protokolna broja kartice: ";
            cin>>brojProtokol;
            brojKartice+=brojProtokol;
            setBrojKartice(brojKartice);

            int datumIsteka;
            string noviDatum;
            time_t t = std::time(0);
            tm* now = std::localtime(&t);
            cout<<"\n\t** Uspjesno je kreiran stedni racun broj: "<<brojKartice<<"\n\n\t2. Koliko godina zelite da nalog traje (pocev od danas): ";
            cin>>datumIsteka;
            now->tm_year+=datumIsteka;
            ostringstream oss;
            oss<<put_time(now, "%m/%y");
            noviDatum=oss.str();
            setDatumIstekaKartice(noviDatum);

            cout<<"\n\t** Uspjesno je podesen datum vazenja kartice. Kartica istice (mjesec/godina): "<<noviDatum<<"\n\n\t** Pocetno stanje stednog racuna postavljeno na 0.00 KM.\n\t   Stanje racuna je moguce promijeniti naknadno."<<endl;
            setStanjeRacuna(0.00);
            setDozvoljenoPrekoracenje(0);

            cout<<"\n\t3. Unesite 3-znamenkasti CVV (Card Verification Value): ";
            string cvv;
            cin>>cvv;
            setCVV(cvv);

            cout<<"\n\t** Uspjesno ste unijeli CVV za bankovnu karticu.\n\n\t4. Unesite 4-znamenkasti PIN kod od racuna (bankovne kartice): ";
            string pin;
            cin>>pin;
            setPinKod(pin);
            cout<<"\n\t** Uspjesno unesen PIN za stedni racun (bankovnu karticu).\n\n\t  Podaci se pripremaju za pohranu..."<<endl;
            this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            t = time(0);
            now = localtime(&t);
            cout<<"\n\t[KREIRANJE NOVOG RACUNA]: Da li zelite sacuvati kreirani nalog sa sljedecim podacima? (Y/N)\n\t_________________________________________\n\t| Broj racuna: "<<brojKartice<<"\t\t|\n\t| Vrsta racuna: Stedni\t\t\t|\n\t| Datum isteka (mjesec/godina): "<<noviDatum<<"\t|\n\t| Stanje: 0.00 KM\t\t\t|\n\t| Dozvoljeno prekoracenje: 0.00 KM\t|\n\t| CVV (Card Verification Value): "<<cvv<<"\t|\n\t| PIN kod: "<<pin<<"\t\t\t\t|\n\t| ";
            cout<<setfill('0')<<setw(2)<<now->tm_mday<<"."<<setfill('0')<<setw(2)<<(now->tm_mon+1)<<"."<<(now->tm_year + 1900)<<". godine u "<<setfill('0')<<setw(2)<<now->tm_hour<<":"<<setfill('0')<<setw(2)<<now->tm_min<<" sati\t|\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\t  Unos: ";
        }
};

vector<TekuciRacun> tekuciRacuni;
vector<StedniRacun> stedniRacuni;

void load_baza()
{
    TekuciRacun noviTekuci;
    noviTekuci.setBrojKartice("1234567891234567");
    noviTekuci.setDatumIstekaKartice("03/25");
    noviTekuci.setStanjeRacuna(1000.00);
    noviTekuci.setDozvoljenoPrekoracenje(3000);
    noviTekuci.setCVV("123");
    noviTekuci.setPinKod("1234");
    tekuciRacuni.push_back(noviTekuci);

    StedniRacun noviStedni;
    noviStedni.setBrojKartice("2345678912345678");
    noviStedni.setDatumIstekaKartice("08/30");
    noviStedni.setStanjeRacuna(2000.00);
    noviStedni.setDozvoljenoPrekoracenje(6000);
    noviStedni.setCVV("456");
    noviStedni.setPinKod("4567");
    stedniRacuni.push_back(noviStedni);
}

#endif // RACUNI_H_INCLUDED
