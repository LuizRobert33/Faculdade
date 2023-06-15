#include <iostream>
using namespace std;
int main(){
    int D,T,R,refeicao,refeicoes[20];
   

    cout << "Digite seu tempo a dormir -- Tempo de voo -- E o numero de refeicoes\n";
    cin >> D >> T >> R;
    cout << "em quantos minutos cada refeicao e feita\n";
    for ( int i = 0; i < R ; i++)
    {
        cin >> refeicao;
        refeicoes[i] = refeicao;
        
        cout << refeicoes[i];
    }
    
    return 0;
}