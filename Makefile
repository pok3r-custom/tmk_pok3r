
pok3r:
	make -f Makefile.app_pok3r
	make -f Makefile.tmk_pok3r

pok3r_rgb:
	make -f Makefile.tmk_pok3r_rgb

vortex_core:
	make -f Makefile.tmk_vortex_core

all: pok3r pok3r_rgb vortex_core

