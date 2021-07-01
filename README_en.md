Repository for the Undergraduate Research Project "Thermodynamical Modelling of Solutions Related to the Food Industry"
=======================================================================================================================

Stored here are the files comprising the data and source code utilised in the
undergraduate research project "Thermodynamical Modelling of Solutions Related
to the Food Industry".

The Project
-----------

This is the repository of data and source code from an undergradute research
project active from September 2020 to September 2021, aiming to assess a few
model correlating water activity and composition of a mixture, being comprised
of two parts: water activity data from the literature and the source code of two
programs, responsible for the conversion of data from several properties to water
activity and the regression analysis of the application of each model to the
converted data.

The data are spread over two directories: `data/converted/` stores data suitable
for analysis and `data/originals/` stores the original data, as seen in the
literature. Besides, to analyse the effects of a few differences among the data
(as chemical nature, dilution, number of solutes, *etc*), they are listed in the
files stored in `data/lists/`.

The code compiles to two command-line utilities: `ConvertWaterActivity` can be used
for conversion from literature data to data suitable to be fed to `FitWaterActivity`,
which fits the models to the data.

This project links the GNU Scientific Library (GSL) to perform nonlinear
least-squares fitting.

Installation
------------

To utilise the command-line utilities written, one needs to install the
dependencies, clone this repository and compile the source code within.

The installation of the GNU Scientific Library is required. Instructions
are available in the [project's website](https://www.gnu.org/software/gsl/).

Besides, one needs to install Git, GCC, Make and the libraries BLAS/CBLAS.

Afterwards, one needs only to clone this repository and compile the source:

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica
$ make
```
Both utilities will be available in the subdirectory `bin/`.

To simply obtain the data sets analysed, one needs only to clone the repository,
and they will be stored in the subdirectory `data/`; the previous requirements
are no longer needed.

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica/data
```

Use
---

To run the utilities, one needs to consider a few details. Firstly, among the
experimental data in the files passed to the program, no conditions in which
the osmotic coefficient is undefined can be included. For instance, pure water
(water activity and molar fraction of one) must be excluded.

Besides, the utilities assume that the files are spreadsheets in `.csv` format,
in which the first line stores the names of each solute in the mixture, the first
column in the lines following it stores water activity values and the other columns
store, for each solute, its molar fraction, as shown below:

```
aw,first_solute,second_solute,...
0.99,0.006,0.004,...
0.97,0.015,0.022,...
0.88,0.123,0.045,...
...
```

To fit the models to the data through `FitWaterActivity` the data are required to
be stored as shown above, as relations between water activity and molar fraction.
Otherwise, one needs to convert them to the suitable format, through the utility
`ConvertWaterActivity`. Both utilities shall be available in the subdirectory
`bin/`, after compilation. For more information, one might be interested in the
user manual shown through the help option `-h`:

```
$ ./bin/ConvertWaterActivity -h
$ ./bin/FitWaterActivity -h
```

Two `bash` scripts, dependent on GNU Datamash, can be run to obtain the results as
shown in the report. They may be, respectively, run through the commands below:

```
$ ./src/gen_data_and_print_table
$ ./src/test_and_train
```

Report
------

If one is interested in the LaTeX source for the report, it's available in the
subdirectory `doc/`. To compile it, are required TeX Live 2021, gnuplot and, again,
Make.

```
$ git clone https://github.com/pedro-callil/IC_2021_Modelagem_Termodinamica
$ cd IC_2021_Modelagem_Termodinamica/doc
$ make biben # for english version
$ make bibpt # for portuguese version
$ make bib # for both
```

The final report(s) will be available in the subdirectory `doc/report/`.

Author
------

Pedro Callil <pedrocallil@usp.br>

