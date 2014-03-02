#include <iostream>
#include <fstream>
#include <sys/time.h>
using namespace std;

/*!
 * \file
 * \brief Kod zrodlowy programu.
 *
 * Plik zawierajacy wszystkie funkcje programu.
 */


/*!
 * \brief Czyta dane z pliku i zapisuje w tablicy.
 *
 * Funkcja czyta dane z pliku, ignorujac pierwszy element (jest to liczba okreslajaca ilosc elementow tablicy), 
 * wpisuje je w poszczegolne elementy tablicy tab.
 *
 * \param tab[] - tablica, do ktorej zapisywane sa kolejne liczby z pliku
 * \param ilosc - zmienna okreslajaca wielkosc tablicy
 * \param nazwa - zmienna okreslajaca nazwe pliku, z ktorego czytane sa liczby
 */
void wypelnij(int tab[], int ilosc, const char * nazwa) {
	fstream plik(nazwa);
	plik.ignore(1000,'\n');
	for (int i=0; i<ilosc; i++)
	plik>>tab[i];
	}

/*!
 * \brief Wyswietla tablice
 *
 * Funkcja wyswietla tablice wczytana wczesniej przez funkcje wypelnij.
 *
 * \param tab[] - tablica, ktora ma zostac wyswietlona
 * \param ilosc - zmienna okreslajaca wielkosc tablicy
 */
void wyswietl(int tab[], int ilosc) {
	for(int i=0; i<ilosc; i++) { cout<<tab[i]<<" "; }
	}

/*!
 * \brief Mnozy kazdy element tablicy razy 2
 *
 * Funkcja podwaja kazdy z elementow tablicy tab_1 i zapisuje wynik mnozenia w tablicy tab_2.
 *
 * \param tab_1[] - tablica, ktorej elementy sa wymnazane przez 2
 * \param tab_1[] - tablica, do ktorej zapisywany jest wynik mnozenia
 * \param ilosc - zmienna okreslajaca wielkosc tablicy
 */
void mnozenie(int tab_1[], int tab_2[], int ilosc) {
	for(int i=0; i<ilosc; i++) { tab_2[i]=2*tab_1[i]; }
	}

/*!
 * \brief Porownuje dwie tablice
 *
 * Funkcja sprawdza czy kazdy element tablicy tab_1 jest taki sam jak tab_2. Jesli tak, funkcja zwraca wartosc \return true,
 * jesli nie - funkcja zwraca wartosc \return false.
 *
 * \param tab_1[] - tablica, ktorej elementy sa porownywane z elementami tablicy tab_2
 * \param tab_1[] - tablica, ktorej elementy sa porownywane z elementami tablicy tab_1
 * \param ilosc - zmienna okreslajaca wielkosc tablicy
 */
bool porownanie(int tab_1[], int tab_2[], int ilosc){
	for(int i=0; i<ilosc; i++){
		if (tab_1[i]==tab_2[i]);
		else
			return false;}
	return true;
	}

/*!
 * \brief Funkcja glowna programu
 *
 * Czyta plik, ktory ma przetworzyc, tworzy tablice dynamiczne tab1-3, w ktorych nastepnie zapisuje odpowiednio:
 * \param tab1 - elementy wczytane z pliku, ktore ma przetworzyc
 * \param tab2 - tablica zawierajaca przetworzone funkcja mnozenie elementy
 * \param tab3 - tablica, ktora zawiera elementy wczytane z pliku sluzacym do sprawdzenia poprawnosci wyniku mnozenia
 * Funkcja czyta pierwsza liczbe zapisana w pliku "tablica". Wpisuje te wartosc do zmiennej n, ktora okresla wielkosc tablicy.
 * Nastepuje przepisanie danych z pliku "tablica" do tab1 za pomoca funkcji wypelnij, oraz wyswietlenie jej za pomoca funkcji wyswietl.
 * Nastepnie przed wykonaniem mnozenia, zapisywany jest czas systemowy funkcja gettimeofday. W zmiennej t1 zapisywany jest czas w
 * mikrosekundach za pomoca tv_usec. Po wykonaniu mnozenia ponownie pobierany jest czas do zmiennej t2, a nastepnie nastepuje odejmowanie t2-t1
 * co pozwala na sprawdzenie dlugosci wykonywania algorytmu.
 * Po wykonaniu mnozenia wczytywane sa dane do tablicy tab3 z pliku, w ktorym zapisany jest oczekiwany wynik operacji mnozenia. Nastepnie
 * porownywane sa tab2 (wynik mnozenia) z tab3. Jesli kazdy element tab2 i tab3 jest taki sam, oznacza to ze algorytm zostal dobrze
 * zaimplementowany i program zostal wykonany prawidlowo.
 * Na koniec wyswietlony oraz zapisany do pliku "wynik" zostaje czas wykonania algorytmu.
 *
 */
int main()
{
	timeval stoper;
	double t1, t2, czas;

	int n;
	fstream plik("tablica");
	ofstream wynik("wynik", ios::app);	
	plik>>n;
	cout<< "Liczba elementow tablicy: "<< n <<endl;

	int *tab1 = new int[n];
	int *tab2 = new int[n];
	int *tab3 = new int[n];

	wypelnij(tab1, n, "tablica");
cout<<"Tablica: "<<endl;
	wyswietl(tab1,n);

/*uruchomienie stopera*/
gettimeofday(&stoper, NULL);
t1=stoper.tv_usec;

	mnozenie(tab1, tab2, n);

/*zatrzymanie stopera*/
gettimeofday(&stoper, NULL);
t2=stoper.tv_usec;
czas=t2-t1;

cout<<endl<<"Tablica po pomnozeniu: "<<endl;
	wyswietl(tab2,n);
	
	wypelnij(tab3, n, "tablica2");
	
// Porownanie tablic: obliczonej i zawierajacej prawidlowa odpowiedz
if (porownanie(tab2, tab3, n)==true){
	cout<<"\n\nWynik poprawny"<<endl;}
else cout<<"\n\nWynik niepoprawny"<<endl;

	delete [] tab1;
	delete [] tab2;
	delete [] tab3;

cout<<"Czas dzialania algorytmu: "<<czas<<" mikrosekund."<<endl<<endl;
wynik<<"Czas dzialania algorytmu: "<<czas<<" mikrosekund."<<endl;
wynik.close();

	return 0;
}
