Repositório do Projeto de Iniciação Científica "Modelagem Termodinâmica de Soluções de Interesse para a Indústria de Alimentos"
===============================================================================================================================

Nesse repositório está o código-fonte dos programas utilizados para
conversão e ajuste dos valores de atividade da água de acordo com a
lista de modelos adotados.

O Projeto
---------

Este projeto faz uso da *GNU Scientific Library* para ajustar e avaliar
diversos modelos propostos na literatura para a relação entre a atividade
da água em uma solução e sua composição.

Representa a parte computacional de um projeto de iniciação científica com
início em Setembro de 2020 e término em Setembro de 2021.

Instalação
----------

Primeiramente se faz necessária a instalação da *GNU Scientific Library*.
As instruções variam de sistema a sistema, estando disponíveis
[no site do projeto](https://www.gnu.org/software/gsl/).

Em seguida basta clonar o repositório e compilar os executáveis:

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica
$ make
```

Uso
---

Para fazer uso dos executáveis, é necessário levar alguns detalhes em conta.
Primeiramente, dentre os dados experimentais dos arquivos fornecidos, não deve
figurar a situação obtida ao se analisar água pura ou qualquer outra situação
na qual o valor do coeficiente osmótico da solução (a razão entre os logaritmos
naturais da atividade da água e de sua concentração) não esteja bem definido.

Além disso, o programa assume que os arquivos sejam planilhas em formato .csv,
nas quais a primeira linha apresenta os nomes dos componentes, a primeira coluna
os valores da propriedade associada à atividade da água, e as próximas colunas
os valores da propriedade associada à composição de cada componente:

```
aw,componente,substancia
0.99,0.006,0.004
0.97,0.015,0.022
0.88,0.123,0.045
...
```

Para ajustar os dados de coeficiente osmótico, usando o programa `FitWaterActivity`
é necessário que os dados estejam expressos como relações entre atividade da água
e fração molar, como acima. Caso contrário, é preciso convertê-los usando o programa
`ConvertWaterActivity`. Os dois programas estarão no subdiretório `bin` do diretório
no qual o código foi compilado. Para informações sobre como utilizar o programa,
deve ser invocada a opção `-h`:

```
$ ./bin/ConvertWaterActivity -h
$ ./bin/FitWaterActivity -h
```

Autor
-----

Pedro Callil <pedrocallil@usp.br>

