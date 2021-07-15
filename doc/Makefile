LC		= lualatex
LCFLAGS		= -shell-escape
BC		= bibtex

LSRC		= main_pt.tex
LSRCEN		= main_en.tex
LSRCDEPS	= abntex2-modelo-include-comandos.aux \
		  aminoacid_aw_avgs.csv \
		  carbohydrate_aw_avgs.csv \
		  dilution_mono.csv \
		  ebrahimi_mannose.csv \
		  ebrahimi_mannose_norrish.csv \
		  ebrahimi_mannose_uniquac.csv \
		  ebrahimi_mannose_virial.csv \
		  ebrahimi_xylose_norrish.csv \
		  ebrahimi_xylose_uniquac.csv \
		  ebrahimi_xylose_virial.csv \
		  ellerton_glycylglycine_norrish.csv \
		  ellerton_glycylglycine_uniquac.csv \
		  ellerton_glycylglycine_virial.csv \
		  fructose_violin.csv \
		  ge_and_wang_bpe.csv \
		  ge_and_wang_fpd.csv \
		  glucose_a_w_and_phi.dat \
		  glucose_violin.csv \
		  iter_norrish.csv \
		  iter_uniquac.csv \
		  iter_virial.csv \
		  ninni_arginine_norrish.csv \
		  ninni_arginine_uniquac.csv \
		  ninni_arginine_virial.csv \
		  norrish_violin.csv \
		  pressure_fructose.csv \
		  pressure_glucose.csv \
		  romero_glycine_288_15_K.csv \
		  romero_glycine_293_15_K.csv \
		  romero_glycine_298_15_K.csv \
		  romero_glycine_303_15_K.csv \
		  stokes_61_sucrose_mannitol_nor.csv \
		  stokes_61_sucrose_mannitol_uni.csv \
		  stokes_61_sucrose_mannitol_vir.csv \
		  stokes_sucrose_norrish.csv \
		  stokes_sucrose_uniquac.csv \
		  stokes_sucrose_uniquac_orig.csv \
		  stokes_sucrose_virial.csv \
		  sucrose_violin.csv \
		  test_and_train_diff_norrish.csv \
		  test_and_train_diff_uniquac.csv \
		  test_and_train_diff_virial.csv \
		  test_and_train_norrish.csv \
		  test_and_train_uniquac.csv \
		  test_and_train_virial.csv \
		  uniquac_violin.csv \
		  velezmoro_maltose_25.csv \
		  velezmoro_maltose_30.csv \
		  velezmoro_maltose_35.csv \
		  violin_alanine_uniquac.csv \
		  violin_fructose_uniquac.csv \
		  violin_glucose_uniquac.csv \
		  violin_glycine_uniquac.csv \
		  violin_sucrose_uniquac.csv \
		  virial_violin.csv

BSRC		= main_pt
BSRCEN		= main_en
BSRCDEPS	= bibliography.bib

LSOUT		= main_pt.pdf
LSOUTEN		= main_en.pdf
RFILE		= report/relatorioIniciacaoCientificaAtividadeDaAgua.pdf
RFILEEN		= report/undergraduateResearchProjectReportWaterActivity.pdf
RFILEME		= report/relatorioEstagioModuloDois.pdf
RFILECA		= report/cartaApresentacaoSeparada.pdf

.PHONY: all pt en bib bibpt biben clean

all: pt en

pt: $(LSRC) $(LSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRC); \
	$(LC) $(LCFLAGS) $(LSRC); \
		if [ ! -d "./report" ]; then mkdir report; fi; \
		cp $(LSOUT) $(RFILE)

en: $(LSRCEN) $(LSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRCEN); \
	$(LC) $(LCFLAGS) $(LSRCEN); \
		if [ ! -d "./report" ]; then mkdir report; fi; \
		cp $(LSOUTEN) $(RFILEEN)

bib: bibpt biben

bibpt: $(LSRC) $(LSRCDEPS) $(BSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRC); \
		$(BC) $(BSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
				if [ ! -d "./report" ]; then mkdir report; fi; \
				cp $(LSOUT) $(RFILE)

biben: $(LSRCEN) $(LSRCDEPS) $(BSRCDEPS)
	$(LC) $(LCFLAGS) $(LSRCEN); \
		$(BC) $(BSRCEN); \
			$(LC) $(LCFLAGS) $(LSRCEN); \
			$(LC) $(LCFLAGS) $(LSRCEN); \
			$(LC) $(LCFLAGS) $(LSRCEN); \
				if [ ! -d "./report" ]; then mkdir report; fi; \
				cp $(LSOUTEN) $(RFILEEN)

internship: $(LSRC) $(LSRCDEPS) $(BSRCDEPS)
	sed -i 's/%\\input{carta/\\input{carta/g' $(LSRC)
	sed -i 's/Relatório Final de Iniciação Científica\/Tecnológica/Relatório Quadrimestral do Segundo Módulo de Estágio/g' $(LSRC)
	$(LC) $(LCFLAGS) $(LSRC); \
		$(BC) $(BSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
			$(LC) $(LCFLAGS) $(LSRC); \
				if [ ! -d "./report" ]; then mkdir report; fi; \
				cp $(LSOUT) $(RFILEME)
	sed -i 's/\\input{carta/%\\input{carta/g' $(LSRC)
	sed -i 's/Relatório Quadrimestral do Segundo Módulo de Estágio/Relatório Final de Iniciação Científica\/Tecnológica/g' $(LSRC)
	pdfseparate -f 5 -l 5 $(RFILEME) $(RFILECA)

clean:
	rm -f main_pt-* \
		main_en-* \
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


