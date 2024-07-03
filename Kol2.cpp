#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2

enum class StanDopuszczenia
{
	dopuszczony,
	niedopuszczony
};

class Wlasciciel
{};

class Samochod
{
private:
	char numerRejestracyjny[10];
	int stanLicznika;
	StanDopuszczenia stanDopuszczeniaDoJazdy;
	Wlasciciel wlasciciel;
	static Samochod* instancjaWzorcowa;
	const int WAR_POCZ = 10000;

public:
	void setStanLicznika(int stanLicznika)
	{
		if (stanLicznika < 0)
			throw invalid_argument("Stan licznika nie mo¿e byæ ujemny.");
		else
			this->stanLicznika = stanLicznika;
	}

	int getStanLicznika() { return stanLicznika; }

	StanDopuszczenia getStanDopuszczeniaDoJazdy() { return stanDopuszczeniaDoJazdy; }

	Samochod(const char* numerRejestracyjny, int stanLicznika, StanDopuszczenia stanDopuszczeniaDoJazdy, Wlasciciel wlasiciel)
	{
		strncpy(this->numerRejestracyjny, numerRejestracyjny, 10);
		setStanLicznika(stanLicznika);
		this->stanDopuszczeniaDoJazdy = stanDopuszczeniaDoJazdy;
		this->wlasciciel = wlasiciel;
	}

	Samochod()
	{
		if (!instancjaWzorcowa)
			throw logic_error("Brak instancji wzorcowej");
 
		strncpy(this->numerRejestracyjny, instancjaWzorcowa->numerRejestracyjny, 10);
		this->stanLicznika = instancjaWzorcowa->stanLicznika;
		this->stanDopuszczeniaDoJazdy = instancjaWzorcowa->stanDopuszczeniaDoJazdy;
		this->wlasciciel = instancjaWzorcowa->wlasciciel; 
	}

	virtual double zasieg()
	{
		return 800.0;
	}

	operator double()
	{
		double WSP_SPRAW = (stanDopuszczeniaDoJazdy == StanDopuszczenia::dopuszczony) ? 1.0 : 0.2;
		double wartosc = (WAR_POCZ - 0.2 * stanLicznika) * WSP_SPRAW;

		if (wartosc < 400)
			return 400;
		else
			return wartosc;
	}

	bool operator!=(const Samochod& rhs)
	{
		return abs(stanLicznika - rhs.stanLicznika) > 20 || stanDopuszczeniaDoJazdy != rhs.stanDopuszczeniaDoJazdy;
	}

};

class SamochodElektryczny : public Samochod
{
private:
	int stanBaterii;
public:
	void setStanBaterii(int stanBaterii)
	{
		if (stanBaterii < 0 || stanBaterii > 100)
			throw invalid_argument("Stan baterii nie jest w zakresie 0-100%.");
		else
			this->stanBaterii = stanBaterii;
	}

	SamochodElektryczny(const char* numerRejestracyjny, int stanLicznika, StanDopuszczenia stanDopuszczeniaDoJazdy, Wlasciciel wlasiciel, int stanBaterii)
		:Samochod(numerRejestracyjny, stanLicznika, stanDopuszczeniaDoJazdy, wlasiciel)
	{
		setStanBaterii(stanBaterii);
	}

	double zasieg() override
	{
		if (getStanDopuszczeniaDoJazdy() == StanDopuszczenia::niedopuszczony)
			throw invalid_argument("Samochod jest niedopuszczony do jazdy.");
		else
			return static_cast<double>(2.5 * stanBaterii);
	}

};


int main()
{

}

#endif
