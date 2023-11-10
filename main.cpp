#include <iostream>
#include <math.h>
#include <string>

using namespace std;

float Unidade()
{
    int n;
    float unidade;

    cout << "Digite o numero equivalente a unidade desejada" << endl;
    cout << "1 --- 10 ^12 - tera" << endl
         << "2 --- 10 ^9 - giga" << endl
         << "3 --- 10 ^6 - mega" << endl
         << "4 --- 10 ^3 - kilo" << endl
         << "5 --- 10 ^0 - decimal" << endl
         << "6 --- 10 ^-3 - mili" << endl
         << "7 --- 10 ^-6 - micro" << endl
         << "8 --- 10 ^-9 - nano" << endl
         << "9 --- 10 ^-12 - pico" << endl;

    cout << "Opcao desejada: ";
    cin >> n;

    switch (n)
    {

    case 1:
        unidade = pow(10, 12);
        break;

    case 2:
        unidade = pow(10, 9);
        break;

    case 3:
        unidade = pow(10, 6);
        break;

    case 4:
        unidade = pow(10, 3);
        break;

    case 5:
        unidade = pow(10, 0);
        break;

    case 6:

        unidade = pow(10, -3);
        break;

    case 7:
        unidade = pow(10, -6);
        break;

    case 8:
        unidade = pow(10, -9);
        break;

    case 9:
        unidade = pow(10, -12);
        break;

    default:
        break;
    }

    return unidade;
}

float Omega0(float l, float c)
{

    float omg = 1 / sqrt(l * c);

    return omg;
}

float Sigma(float r, float c)
{
    float sig = 0;
    sig = 1 / (2 * r * c);

    return sig;
}

float OmegaD(float r, float c, float l)
{
    float sigma = Sigma(r, c);
    float omega0 = Omega0(l, c);

    float omegaD;

    omegaD = sqrt(pow(omega0, 2) - pow(sigma, 2));

    return omegaD;
}

void SuperAmortecido(float sigma, float omega0, float V0, float I0, float r, float c)
{
    float s1 = 0, s2 = 0, A1 = 0, A2 = 0;

    s1 = -sigma + (sqrt(pow(sigma, 2) - pow(omega0, 2))); /*(duvida)*/
    s2 = -sigma - (sqrt(pow(sigma, 2) - pow(omega0, 2)));

    float x = (-V0 + (r * I0)) / (r * c);

    A2 = ((-s1 * V0) + x) / (-s1 + s2);
    A1 = V0 - A2;

    float y = A2 * s2;
    float w = A1 * s1;
    float z = s1 - s2;

    float tm = (log10(-y / w) / log10(2.71828)) / z;
    float vtm = (A1 * exp(s1 * tm)) + (A2 * exp(s2 * tm));

    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl
         << "A1 = " << A1 << endl
         << "A2 = " << A2 << endl;

    cout << "TM = " << tm << "(s)" << endl;
    cout << "V(TM) = " << vtm << "(V)" << endl;
}

void Criticamente(float sigma, float omega0, float V0, float I0, float r, float c)
{

    float A1 = 0, A2 = 0;
    float s1 = -sigma, s2 = -sigma;

    float x = (-V0 + (r * I0)) / (r * c);

    A2 = V0;
    A1 = x + (sigma * V0);

    float tm = (((-A2 * sigma) / A1) + 1) / sigma;
    float vtm = (A1 * tm + A2) * (exp(-sigma * tm));

    cout << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl
         << "A1 = " << A1 << endl
         << "A2 = " << A2 << endl
         << "TM = " << tm << "(s)" << endl
         << "V(TM) = " << vtm << "(V)" << endl;
}

void Subamortecido(float sigma, float omega0, float V0, float I0, float r, float c, float l)
{

    float B1 = 0, B2 = 0;
    float omegad = OmegaD(r, c, l);
    float x = (-V0 + (r * I0)) / (r * c);

    B1 = V0;

    B2 = (x - (sigma * B1)) / omegad;
    if (B2 == 0)
    {
        B2 = 0;
    }

    float tm = atan((B2 * omegad - B1 * sigma) / (B2 * sigma + B1 * omegad)) / omegad;

    if (tm < 0)
    {
        tm = tm + (3.141592654 / omegad);
    }

    float vtm = exp(-sigma * tm) * ((B1 * cos(omegad * tm) + (B2 * sin(omegad * tm))));

    cout << "OmegaD = " << omegad << " (rad/s)" << endl;
    cout << "B1 = " << B1 << endl
         << "B2 = " << B2 << endl
         << "TM = " << tm << "(s)" << endl
         << "V(TM) = " << vtm << "(V)" << endl;
}

int main()
{
    while (1)

    {

        float c, l, r;
        float I0 = 0, V0 = 0;
        float uni;

        float sigma = 0, omega0 = 0;

        cout << "Digite o valor do resistor equivalente (sem unidade): ";
        cin >> r;
        uni = Unidade();
        r = r * uni;

        cout << "Digite o valor do indutor equivalente (sem unidade): ";
        cin >> l;
        uni = Unidade();
        l = l * uni;

        cout << "Digite o valor do capacitor equivalente (sem unidade): ";
        cin >> c;
        uni = Unidade();
        c = c * uni;

        cout << "Digite o valor do V(0): ";
        cin >> V0;
        uni = Unidade();
        V0 = V0 * uni;

        cout << "Digite o valor do I(0): ";
        cin >> I0;
        uni = Unidade();
        I0 = I0 * uni;

        sigma = Sigma(r, c);
        omega0 = Omega0(l, c);

        if (sigma > omega0)
        {
            cout << "\n---------------circuito superamortecido---------------" << endl
                 << endl;
            cout << "Sigma = " << sigma << "(s^-1)" << endl;
            cout << "Omega0 = " << omega0 << "(rad/s)" << endl;
            SuperAmortecido(sigma, omega0, V0, I0, r, c);
        }
        else if (sigma == omega0)
        {
            cout << "\n---------------circuito criticamente amortecido---------------" << endl
                 << endl;
            cout << "Sigma = " << sigma << "(s^-1)" << endl;
            cout << "Omega0 = " << omega0 << "(rad/s)" << endl;
            Criticamente(sigma, omega0, V0, I0, r, c);
        }
        else if (sigma < omega0)
        {
            cout << "\n---------------circuito subamortecido---------------" << endl
                 << endl;
            cout << "Sigma = " << sigma << "(s^-1)" << endl;
            cout << "Omega0 = " << omega0 << "(rad/s)" << endl;
            Subamortecido(sigma, omega0, V0, I0, r, c, l);
        }

        cout << endl
             << endl
             << "Dupla: Avani Maria da Fonseca e Wesley Alves da Silva" << endl;

        system("pause");
    }

    return 0;
}
