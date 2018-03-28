
app_pok3r:
	echo "Make Pok3r App"
	make -f util/Makefile.app_pok3r
tmk_pok3r:
	echo "Make TMK Pok3r"
	make -f util/Makefile.tmk_pok3r

pok3r: app_pok3r tmk_pok3r

tmk_pok3r_rgb:
	echo "Make TMK Pok3r RGB"
	make -f util/Makefile.tmk_pok3r_rgb

pok3r_rgb: tmk_pok3r_rgb

app_vortex_core:
	echo "Make Vortex Core App"
	make -f util/Makefile.app_vortex_core
tmk_vortex_core:
	echo "Make TMK Vortex Core"
	make -f util/Makefile.tmk_vortex_core

vortex_core: app_vortex_core tmk_vortex_core

all: pok3r pok3r_rgb vortex_core

