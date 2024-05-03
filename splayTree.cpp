#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
ofstream fout("output.txt");
class nodABC{
    int valoare;
    nodABC* fiu_stanga;
    nodABC* fiu_dreapta;
    nodABC* parinte;
public:
    nodABC(int val) : valoare(val) {
        fiu_stanga = 0;
        parinte = 0;
        fiu_dreapta = 0;
    }
    nodABC(int val, nodABC par) : valoare(val), parinte(&par){
        fiu_stanga = 0;
        fiu_dreapta = 0;
    }
    void afisare();
    friend class ABC;
    char caracterizare(){
        if(parinte == 0){
            return 'R';
        }
        else
        {
            if(fiu_dreapta == 0 && fiu_stanga == 0){
                return 'F';
            }
            else
            {
                return 'N';
            }
        }
    }
    int get_valoare() {return valoare;}
    nodABC* get_parinte() {return parinte;}
    friend void muta_nod(nodABC* a, nodABC* b);
    bool verificare();
};
class ABC{
    nodABC* radacina;
public:
    ABC(nodABC* rad){
        radacina = rad;
    }
    ABC(){radacina = 0;}
    void inserare(nodABC* nod);
    void afisare();
    void afisare_lant(nodABC nod);
    void stergere(nodABC* nod);
    void actualizare_radacina();
    void zigleft(nodABC* par, nodABC* fiu);
    void zigright(nodABC* par, nodABC* fiu);
    void zigzigleft(nodABC* bun, nodABC* par, nodABC* fiu);
    void zigzigright(nodABC* bun, nodABC* par, nodABC* fiu);
    void zigzagleft(nodABC* bun, nodABC* par, nodABC* fiu);
    void zigzagright(nodABC* bun, nodABC* par, nodABC* fiu);
    void splaying(nodABC* nod);
    nodABC* cautare(int valoare);
    nodABC* succesor(nodABC* nod);
    nodABC* predecesor(nodABC* nod);
    nodABC* get_rad(){return radacina;};
    nodABC* minim(nodABC* nod_start);
    nodABC* maxim(nodABC* nod_start);
    bool verificare(nodABC* nod);
};
void ABC::inserare(nodABC* nod){
    nodABC* par = radacina;
    if(par == 0){
        radacina = nod;
    }
    else
    {
        while(true){
            if(nod->valoare <= par->valoare){
                if(par->fiu_stanga == 0){
                    par->fiu_stanga = nod;
                    nod->parinte = par;
                    break;
                }
                else
                {
                    par = par->fiu_stanga;
                }
            }
            else
            {
                if(par->fiu_dreapta == 0){
                    par->fiu_dreapta = nod;
                    nod->parinte = par;
                    break;
                }
                else
                {
                    par = par->fiu_dreapta;
                }

            }
        }
    }
}
void nodABC::afisare(){
    fout << caracterizare() << ": " << valoare << " - ";
    if(fiu_stanga == 0){
        fout << "zero ";
    }
    else
    {
        fout << fiu_stanga->valoare << " ";
    }
    if(fiu_dreapta == 0){
        fout << "zero\n";
    }
    else
    {
        fout << fiu_dreapta->valoare << "\n";
    }
}
void ABC::afisare_lant(nodABC nod){
    nod.afisare();
    if(nod.fiu_stanga != 0){
        afisare_lant(*nod.fiu_stanga);
    }
    if(nod.fiu_dreapta != 0){
        afisare_lant(*nod.fiu_dreapta);
    }
}
void ABC::afisare(){
    if(radacina != 0){
        afisare_lant(*radacina);
    }
    else
    {
        cout << "arbore vid\n";
    }
}
nodABC* ABC::cautare(int valoare){
    if(radacina == 0){
        return 0;
    }
    nodABC* nod_curent = radacina;
    while(true){
        if(nod_curent->valoare == valoare){
            return nod_curent;
        }
        if(nod_curent->valoare < valoare){
            if(nod_curent->fiu_dreapta == 0){
                return 0;
            }
            else
            {
                nod_curent = nod_curent->fiu_dreapta;
            }
        }
        else
        {
            if(nod_curent->fiu_stanga == 0){
                return 0;
            }
            else
            {
                nod_curent = nod_curent->fiu_stanga;
            }
        }
    }
}
nodABC* ABC::minim(nodABC* nod_start){
    nodABC* nod_curent = nod_start;
    while(nod_curent->fiu_stanga != 0){
        nod_curent = nod_curent->fiu_stanga;
    }
    return nod_curent;
}
nodABC* ABC::maxim(nodABC* nod_start){
    nodABC* nod_curent = nod_start;
    while(nod_curent->fiu_dreapta != 0){
        nod_curent = nod_curent->fiu_dreapta;
    }
    return nod_curent;
}
nodABC* ABC::succesor(nodABC* nod){
    if(nod->fiu_dreapta != 0){
        return minim(nod->fiu_dreapta);
    }
    nodABC* par = nod->parinte;
    nodABC* fiu = nod;
    while(par != 0 && par->fiu_dreapta == fiu){
        fiu = par;
        par = par->parinte;
    }
    return par;
}
nodABC* ABC::predecesor(nodABC* nod){
    if(nod->fiu_stanga != 0){
        return maxim(nod->fiu_stanga);
    }
    nodABC* par = nod->parinte;
    nodABC* fiu = nod;
    while(par != 0 && par->fiu_stanga == fiu){
        fiu = par;
        par = par->parinte;
    }
    return par;
}
void ABC::actualizare_radacina(){
    nodABC* rad = radacina;
    while(rad->parinte !=0){
        rad = rad->parinte;
    }
    radacina = rad;
}
void muta_nod(nodABC* a, nodABC* b){
    if(b->parinte->fiu_dreapta == b){
        b->parinte->fiu_dreapta = 0;
    }
    else
    {
        b->parinte->fiu_stanga = 0;
    }
    if(a->parinte != 0){
        b->parinte = a->parinte;
        if(a->parinte->fiu_stanga == a){
            a->parinte->fiu_stanga = b;
        }
        else
        {
            a->parinte->fiu_dreapta = b;
        }
    }
    else
    {
        b->parinte = 0;
    }

}
void ABC::stergere(nodABC* nod){
    if(nod->fiu_stanga == 0 && nod->fiu_dreapta == 0){
        if(nod->parinte !=0){
            if(nod->parinte->fiu_stanga == nod){
                nod->parinte->fiu_stanga = 0;
            }
            else
            {
                nod->parinte->fiu_dreapta = 0;
            }
        }
        else
        {
            radacina = 0;
        }
    }
    else
    {
        if(nod->fiu_stanga == 0){
            nodABC* nod_aux = nod->fiu_dreapta;
            muta_nod(nod, nod_aux);
            if(nod == radacina){
                radacina = nod_aux;
            }
        }
        else
        {
            if(nod->fiu_dreapta == 0){
                nodABC* nod_aux = nod->fiu_stanga;
                muta_nod(nod, nod_aux);
                if(nod == radacina){
                    radacina = nod_aux;
                }
            }
            else
            {
                nodABC* suc = succesor(nod);
                if(nod->fiu_dreapta == suc){
                    muta_nod(nod, suc);
                    if(nod == radacina){
                        radacina = suc;
                    }
                    if(nod->fiu_dreapta != 0){
                        suc->fiu_stanga = nod->fiu_stanga;
                    }
                }
                else
                {
                    if(suc->fiu_dreapta != 0){
                        muta_nod(suc, suc->fiu_dreapta);
                    }
                    muta_nod(nod, suc);
                    if(nod == radacina){
                        radacina = suc;
                    }
                    suc->fiu_stanga = nod->fiu_stanga;
                    suc->fiu_dreapta = nod->fiu_dreapta;
                    if(nod->fiu_stanga != 0){
                        nod->fiu_stanga->parinte = suc;
                    }
                    if(nod->fiu_dreapta != 0)
                    {
                        nod->fiu_dreapta->parinte = suc;
                    }
                }
            }
        }
    }
    delete nod;
    actualizare_radacina();
}
void ABC::zigleft(nodABC* par, nodABC* fiu){
    radacina = fiu;
    par->parinte = fiu;
    fiu->parinte = 0;
    if(fiu->fiu_dreapta != 0)
        fiu->fiu_dreapta->parinte = par;
    par->fiu_stanga = fiu->fiu_dreapta;
    fiu->fiu_dreapta = par;
}
void ABC::zigright(nodABC* par, nodABC* fiu){
    radacina = fiu;
    par->parinte = fiu;
    fiu->parinte = 0;
    if(fiu->fiu_stanga != 0)
        fiu->fiu_stanga->parinte = par;
    par->fiu_dreapta = fiu->fiu_stanga;
    fiu->fiu_stanga = par;
}
void ABC::zigzigleft(nodABC* bun, nodABC* par, nodABC* fiu){
    if(radacina == bun){
        radacina = fiu;
    }
    else
    {
        if(bun->parinte->fiu_stanga == bun){
            bun->parinte->fiu_stanga = fiu;
        }
        else
        {
            bun->parinte->fiu_dreapta = fiu;
        }
    }
    fiu->parinte = bun->parinte;
    par->parinte = fiu;
    bun->parinte = par;

    if(fiu->fiu_dreapta != 0)
        fiu->fiu_dreapta->parinte = par;
    par->fiu_stanga = fiu->fiu_dreapta;
    fiu->fiu_dreapta = par;

    if(par->fiu_dreapta != 0)
        par->fiu_dreapta->parinte = bun;
    bun->fiu_stanga = par->fiu_dreapta;
    par->fiu_dreapta = bun;
}
void ABC::zigzigright(nodABC* bun, nodABC* par, nodABC* fiu){
    if(radacina == bun){
        radacina = fiu;
    }
    else
    {
        if(bun->parinte->fiu_stanga == bun){
            bun->parinte->fiu_stanga = fiu;
        }
        else
        {
            bun->parinte->fiu_dreapta = fiu;
        }
    }
    fiu->parinte = bun->parinte;
    par->parinte = fiu;
    bun->parinte = par;
    if(fiu->fiu_stanga != 0)
    {
        fiu->fiu_stanga->parinte = par;
    }
    par->fiu_dreapta = fiu->fiu_stanga;
    fiu->fiu_stanga = par;
    if(par->fiu_stanga != 0){
        par->fiu_stanga->parinte = bun;
    }
    bun->fiu_dreapta = par->fiu_stanga;
    par->fiu_stanga = bun;
}
void ABC::zigzagleft(nodABC* bun, nodABC* par, nodABC* fiu){
    if(radacina == bun){
        radacina = fiu;
    }
    else
    {
        if(bun->parinte->fiu_stanga == bun){
            bun->parinte->fiu_stanga = fiu;
        }
        else
        {
            bun->parinte->fiu_dreapta = fiu;
        }
    }
    fiu->parinte = bun->parinte;
    bun->parinte = fiu;
    par->parinte = fiu;

    if(fiu->fiu_dreapta != 0)
        fiu->fiu_dreapta->parinte = par;
    par->fiu_stanga = fiu->fiu_dreapta;
    fiu->fiu_dreapta = par;

    if(fiu->fiu_stanga != 0)
        fiu->fiu_stanga->parinte = bun;
    bun->fiu_dreapta = fiu->fiu_stanga;
    fiu->fiu_stanga = bun;
}
void ABC::zigzagright(nodABC* bun, nodABC* par, nodABC* fiu){
    if(radacina == bun){
        radacina = fiu;
    }
    else
    {
        if(bun->parinte->fiu_stanga == bun){
            bun->parinte->fiu_stanga = fiu;
        }
        else
        {
            bun->parinte->fiu_dreapta = fiu;
        }
    }
    fiu->parinte = bun->parinte;
    bun->parinte = fiu;
    par->parinte = fiu;

    if(fiu->fiu_stanga != 0)
        fiu->fiu_stanga->parinte = par;
    par->fiu_dreapta = fiu->fiu_stanga;
    fiu->fiu_stanga = par;

    if(fiu->fiu_dreapta != 0)
        fiu->fiu_dreapta->parinte = bun;
    bun->fiu_stanga = fiu->fiu_dreapta;
    fiu->fiu_dreapta = bun;
}
bool nodABC::verificare(){
    if(fiu_stanga !=0){
        if(fiu_stanga->valoare > valoare){
            return 0;
        }
    }
    if(fiu_dreapta !=0){
        if(fiu_dreapta->valoare < valoare){
            return 0;
        }
    }
    return 1;
}
bool ABC::verificare(nodABC* nod){
    if(nod->verificare() == 0){
        return 0;
    }
    if(nod->fiu_stanga != 0){
        if(verificare(nod->fiu_stanga) == 0){
            return 0;
        }
    }
    if(nod->fiu_dreapta != 0){
        if(verificare(nod->fiu_dreapta) == 0){
            return 0;
        }
    }
    return 1;
}
void ABC::splaying(nodABC* nod){
    while(radacina != nod){
        if(nod->parinte == radacina){
            if(nod->parinte->fiu_stanga == nod){
                zigleft(nod->parinte, nod);
            }
            else
            {
                zigright(nod->parinte, nod);
            }
        }
        else
        {
            if(nod->parinte->parinte->fiu_stanga == nod->parinte){
                if(nod->parinte->fiu_stanga == nod){
                    zigzigleft(nod->parinte->parinte, nod->parinte, nod);
                }
                else
                {
                    zigzagright(nod->parinte->parinte, nod->parinte, nod);
                }
            }
            else
            {
                if(nod->parinte->fiu_stanga == nod){
                    zigzagleft(nod->parinte->parinte, nod->parinte, nod);
                }
                else
                {
                    zigzigright(nod->parinte->parinte, nod->parinte, nod);
                }
            }
        }
    }
}
int main()
{
    ifstream fin("input.txt");
    string keyword;
    int k, valoare;
    int prev_size = 0;
    ABC arbore;
    fin >> k;

    auto start = std::chrono::high_resolution_clock::now();
    for(int contor = 0; contor < k; contor++){
        fin >> keyword;
        if(keyword == "INSERT"){
            fin >> valoare;
            nodABC* nodtemp = new nodABC(valoare);
            if(contor == 0){
                arbore = ABC(nodtemp);
            }
            else
            {
                arbore.inserare(nodtemp);
                arbore.splaying(nodtemp);
            }
        }
        else
        {
            if(keyword == "SEARCH"){
                fin >> valoare;
                bool gasit;
                nodABC* ptr = arbore.cautare(valoare);
                if(ptr == 0){
                    gasit = 0;
                }
                else
                {
                    gasit = 1;
                    arbore.splaying(ptr);
                }

            }
            else
            {
                if(keyword == "DELETE"){
                    fin >> valoare;
                    nodABC* nodtemp = arbore.cautare(valoare);
                    if(nodtemp != 0){
                        arbore.stergere(nodtemp);
                    }
                }
                else
                {
                    if(keyword == "MINIM"){
                        int mn = arbore.minim(arbore.get_rad())->get_valoare();
                    }
                    else
                    {
                        if(keyword == "MAXIM"){
                            int mx = arbore.maxim(arbore.get_rad())->get_valoare();
                        }
                    }
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " ms" << std::endl;

}
