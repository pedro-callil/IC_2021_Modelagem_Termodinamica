Repositório do Projeto de Iniciação Científica "Modelagem Termodinâmica de Soluções de Interesse para a Indústria de Alimentos"
===============================================================================================================================

Nesse repositório estão o código-fonte dos programas utilizados para
conversão e ajuste dos valores de atividade da água de acordo com a
lista de modelos adotados, e uma coleção de dados da literatura
associando valores de atividade de água com composições de misturas.

O Projeto
---------

Este é o repositório de dados e código-fonte de um projeto de iniciação científica,
realizado entre Setembro de 2020 e Setembro de 2021, que visa avaliar alguns modelos
que associam composição e atividade da água em uma mistura, consistindo de duas
partes: dados de atividade de água e dois programas, para converter a ajustar dados
da literatura.

Os dados estão divididos em dois diretórios: `data/converted/` apresenta
dados prontos para servir de input ao programa, e `data/originals/` apresenta
os dados como vistos nas fontes, sendo necessária a sua conversão. Além disso,
em `data/lists/` os conjuntos de dados estão classificados em algumas categorias
para facilitar a análise de diferentes efeitos.

Os programas consistem de dois executáveis:  `ConvertWaterActivity` é responsável
por converter os dados provenientes da literatura em dados aptos a serem alimentados
ao executável `FitWaterActivity`, que é responsável por analisar os dados de
atividade da água de acordo com os modelos.

Este projeto faz uso da *GNU Scientific Library* para as regressões não-lineares.

Instalação
----------

Caso exista interesse pelos executáveis, é necessário obter as dependências,
clonar o repositório e compilar o programa.

É necessária a instalação da *GNU Scientific Library*.
As instruções variam de sistema a sistema, estando disponíveis
[no site do projeto](https://www.gnu.org/software/gsl/).

Além disso, é necessário instalar Git, GCC e Make, além das bibliotecas
BLAS/CBLAS.

Em seguida basta clonar o repositório e compilar os executáveis:

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica
$ make
```

Os dois executáveis estarão no subdiretório `bin/`.

Caso o interesse seja apenas pelo conjunto de dados, basta clonar o repositório,
e os dados estarão no subdiretório `data/`; as exigências anteriores não são, nesse
caso, necessárias.

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica/data
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

Relatório
---------

Caso exista interesse no relatório final do projeto, o arquivo `.tex` que constitui
seu código-fonte está disponível no diretório `doc`. Para compilar o relatório, é
necessário TeX Live 2021, gnuplot, e, novamente, Make:

```
$ cd doc
$ make bib
```

O relatório final estará disponível no subdiretório `doc/report`.

Autor
-----

Pedro Callil <pedrocallil@usp.br>

