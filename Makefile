
pok3r:
	echo "Make Pok3r App"
	make -f Makefile.app_pok3r
	echo "Make TMK Pok3r"
	make -f Makefile.tmk_pok3r

pok3r_rgb:
	make -f Makefile.tmk_pok3r_rgb

vortex_core:
	make -f Makefile.tmk_vortex_core

all: pok3r pok3r_rgb vortex_core

