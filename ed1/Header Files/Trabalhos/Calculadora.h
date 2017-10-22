typedef struct calculadora Calculadora;

Calculadora * criar_calc();
void destruir_calc(Calculadora * calc);

int status_ok (Calculadora * calc);
void imprimir_calc(Calculadora * calc);

void limpar_calc(Calculadora * calc);
void empilhar_operando(Calculadora * calc, int operando);
void somar(Calculadora * calc);
void subtrair(Calculadora * calc);
void multiplicar(Calculadora * calc);
void dividir(Calculadora * calc);