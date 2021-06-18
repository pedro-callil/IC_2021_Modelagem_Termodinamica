LC		= lualatex
LCFLAGS		= -shell-escape
BC		= bibtex

LSRC		= main.tex
LSRCDEPS	= abntex2-modelo-include-comandos.aux \
		  aminoacid_aw_avgs.csv \
		  carbohydrate_aw_avgs.csv \
		  dilution_mono.csv \
		  ebrahimi_mannose.csv \
		  ebrahimi_mannose_norrish.csv \
		  ebrahimi_mannose_uniquac.csv \
		  ebrahimi_mannose_virial.csv \
		  fructose_violin.csv \
		  ge_and_wang_bpe.csv \
		  ge_and_wang_fpd.csv \
		  glucose_a_w_and_phi.dat \
		  glucose_violin.csv \
		  iter_norrish.csv \
		  iter_uniquac.csv \
		  iter_virial.csv \
		  main.tex \
		  norrish_violin.csv \
		  romero_glycine_288_15_K.csv \
		  romero_glycine_293_15_K.csv \
		  romero_glycine_298_15_K.csv \
		  romero_glycine_303_15_K.csv \
		  stokes_61_sucrose_mannitol_nor.csv \
		  stokes_61_sucrose_mannitol_uni.csv \
		  stokes_61_sucrose_mannitol_vir.csv \
		  sucrose_violin.csv \
		  uniquac_violin.csv \
		  velezmoro_maltose_25.csv \
		  velezmoro_maltose_30.csv \
		  velezmoro_maltose_35.csv \
		  virial_violin.csv

BSRC		= main
BSRCDEPS	= bibliography.bib

LSOUT		= main.pdf
RFILE		= report/relatorioIniciacaoCientificaAtividadeDaAgua.pdf

.PHONY: all bib clean

all: $(LSRC) $(LSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRC); \
	$(LC) $(LCFLAGS) $(LSRC); \
		if [ ! -d "./report" ]; then mkdir report; fi; \
		cp $(LSOUT) $(RFILE)

bib: $(LSRC) $(LSRCDEPS) $(BSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRC); \
		$(BC) $(BSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
				if [ ! -d "./report" ]; then mkdir report; fi; \
				cp $(LSOUT) $(RFILE)

clean:
	rm -f main-* \
		main.aux \
		*.auxlock \
		*.bbl \
		*.blg \
		*.brf \
		*.gnuplot \
		*.idx \
		*.lof \
		*.log \
		*.lot \
		*.pdf \
		*.toc


