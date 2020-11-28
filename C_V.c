#include <stdio.h>
#include <math.h>
void aplica_luhn(long int numero, int * soma);
int valida_soma(int num);
int verifica_operado(long int numero_cartao, int tamanho, int* ptr_operadora);
void cont_cartao(long int numero_cartao, int* tamanho);
void executar(long int input);
int main(){
    long int input=1;
    while (input !=0)
    {
        printf("\n\nEnter the credit card number without points or space or enter 0 to exit.\n");
        scanf("%ld", &input);
        if(input != 0)
        executar(input);
    }
    return 0;
}
void executar(long int input){
    int soma_numr, valid_num=99999,  valid_operadora, operadora, tamanho_num=0;
    cont_cartao(input, &tamanho_num);
    // Verifica o tamanho do numero
    if(tamanho_num < 13 || tamanho_num > 16)
    {
        if(tamanho_num < 13)
        printf("%ld Very short number", input);
        else
        printf("%ld Very large number", input);
    }
    else
    {
        valid_operadora = verifica_operado(input,tamanho_num, &operadora);
        if(valid_operadora == 0)
            printf("%ld Unknown operator", input);
        else{
            aplica_luhn(input, &soma_numr);
            valid_num = valida_soma(soma_numr);
            if(tamanho_num == 13){
                if(operadora == 4){
                    if(valid_num == 1)
                        printf("%ld, Visa, valid", input);
                    else
                        printf("%ld, Visa, invalid", input);
                }
                else
                printf("%ld Unknown operator", input);

            }
            else if(tamanho_num == 14){
                if(operadora == 30 || operadora == 36 || operadora == 38){
                    if(valid_num == 1)
                        printf("%ld, Diners, valid", input);
                    else
                        printf("%ld, Diners, invalid", input);
                }
                else
                printf("%ld Unknown operator", input);
            }
            else if(tamanho_num == 15){
                if(operadora == 34 || operadora == 37){
                     if(valid_num == 1)
                        printf("%ld, Amex, valid", input);
                    else
                        printf("%ld, Amex, invalid", input);
                }
                else if(operadora == 2014 || operadora == 2149){
                    if(valid_num == 1)
                        printf("%ld, enRoute, valid", input);
                    else
                        printf("%ld, enRoute, invalid", input);
                }
                else if(operadora == 2131 || operadora == 1800){
                    if(valid_num == 1)
                        printf("%ld, JCB, valid", input);
                    else
                        printf("%ld, JCB, invalid", input);
                }
                else
                printf("%ld Unknown operator", input);

            }
            else if(tamanho_num == 16){
                if(operadora >= 51 && operadora <= 55){
                    if(valid_num == 1)
                        printf("%ld, Mastercard, valid", input);
                    else
                        printf("%ld, Mastercard, invalid", input);
                }
                else if(operadora == 4){
                    if(valid_num == 1)
                        printf("%ld, Visa, valid", input);
                    else
                        printf("%ld, Visa, invalid", input);
                }
                else if(operadora == 6011){
                    if(valid_num == 1)
                        printf("%ld, Discover, valid", input);
                    else
                        printf("%ld, Discover, invalid", input);
                }
                else if(operadora == 3){
                    if(valid_num == 1)
                        printf("%ld, JCB, valid", input);
                    else
                        printf("%ld, JCB, invalid", input);
                }
                else if (operadora == 50) {
                    if(valid_num ==1)
                        printf("%ld, Aura, valid\n", input);
                    else
                        printf("%ld, Aura, invalid\n", input);
                }
                else
                printf("%ld Unknown operator", input);
            }
        }
    }
}
void cont_cartao(long int numero_cartao, int* tamanho){
        while(numero_cartao !=0){
            numero_cartao = numero_cartao / 10;
            *tamanho= *tamanho +1;
        }
}
int verifica_operado(long int numero_cartao, int tamanho, int* ptr_operadora){
        int potencia, operadora, invalido;
        //para descobrir o prefixo da operadora, utilizo da seguinte formula matematica: numero_do_cartao/10(elevado ao tamanho do numero)-2, para obter os dois primeiros digitos (prefixo)
        potencia= tamanho -2;
        operadora = numero_cartao / pow(10, potencia);
        if(operadora > 49 && operadora < 56 || operadora > 35 && operadora < 39 || operadora == 34 || operadora == 30){
            //Retorno o prefixo
            *ptr_operadora = operadora;
            return 1;
        }
         //para descobrir o prefixo da operadora, utilizo da seguinte formula matematica: numero_do_cartao/10(elevado ao tamanho do numero)-4, para obter os quatro primeiros digitos (prefixo)
        potencia= tamanho -4;
        operadora = numero_cartao / pow(10, potencia);
        if(operadora == 6011 || operadora == 2014 || operadora == 2149 || operadora == 2131 || operadora == 1800){
            //Retorno o prefixo
            *ptr_operadora = operadora;
            return 1;
        }
         //para descobrir o prefixo da operadora, utilizo da seguinte formula matematica: numero_do_cartao/10(elevado ao tamanho do numero)-1, para obter o primeiro digito (prefixo)
        potencia= tamanho -1;
        operadora = numero_cartao / pow(10, potencia);
        if(operadora == 3 || operadora == 4){
            //Retorno o prefixo
            *ptr_operadora = operadora;
            return 1;
        }
        else
        return 0;
}
int valida_soma(int num){
    if( num % 10 == 0)
    return 1;
    else
    return 0;
}
void aplica_luhn(long int numero, int * soma){
    int unidade, soma_num=0,par_impar = 1, aux;
    long int new_num =0;
    while(numero != 0){
        //Separa a unidade
        unidade = numero % 10;
        numero/= 10;
        //Verifica numeros pares para multiplicar
        if(par_impar % 2 == 0){
            unidade*=2;
        }
        //Se a unidade for uma dezena, separamos em unidade mais uma vez
        if(unidade >= 10){
           int aux = unidade % 10;
           unidade/=10;
           new_num= new_num * 10 + aux;
           new_num= new_num * 10 + unidade;
           soma_num+= aux;
        }
        else
            new_num= new_num * 10 + unidade;
    par_impar++;
    soma_num+= unidade;
    }
    //retorna a soma das unidades
    *soma= soma_num;
}
