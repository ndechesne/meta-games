SUMMARY = "Turn-based strategy game inspired by the history of human civilization."
DESCRIPTION = "Freeciv is distributed under the GPL and implemented for X. \
 Freeciv is a turn-based strategy game, in which \
 each player becomes leader of a civilization, fighting to obtain \
 the ultimate goal: The extinction of all other civilizations. \
 "

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=0636e73ff0215e8d672dc4c32c317bb3"

SECTION = "games"

DEPENDS = "gtk+ readline libsdl-mixer bzip2"

SRC_URI = "\
${SOURCEFORGE_MIRROR}/freeciv/freeciv-${PV}.tar.bz2 \
file://allow-root.patch \
file://wait-server-start.patch \
"

S = "${WORKDIR}/freeciv-${PV}"
B = "${WORKDIR}/build-${PV}"

inherit autotools pkgconfig

EXTRA_OECONF = "\
--enable-shared --without-ggz-dir --enable-client=${FREECIV_GUI} \
SDL_CONFIG=${STAGING_BINDIR_CROSS}/sdl-config \
"

acpaths = "-I ${S}/m4 -I ${S}/dependencies/m4"

PACKAGES =+ "${PN}-common ${PN}-server ${PN}-client-common ${PN}-gtk2"

do_install_append() {
        rm -Rf ${D}/${datadir}/appdata
}

RDEPENDS_${PN} = "freeciv-server freeciv-client"

FILES_${PN}-common = "\
${libdir}/libfreeciv.so.0.0.0 \
${libdir}/libfreeciv.so.0 \
${datadir}/po \
${datadir}/icons/hicolor/*/*/freeciv-client.png \
"

RDEPENDS_${PN}-server = "freeciv-common"
FILES_${PN}-server = "\
${bindir}/freeciv-server \
${datadir}/freeciv/default \
${datadir}/freeciv/default.serv \
${datadir}/freeciv/nation \
${datadir}/icons/hicolor/*/*/freeciv-server.png \
"

FILES_${PN}-client-common = "\
${datadir}/freeciv/helpdata.txt \
${datadir}/freeciv/flags \
${datadir}/freeciv/misc \
${datadir}/freeciv/amplio2.tilespec \
${datadir}/freeciv/amplio2 \
${datadir}/freeciv/stdsounds.soundspec \
${datadir}/freeciv/stdsounds \
${datadir}/icons/hicolor/*/*/freeciv-modpack.png \
"

RDEPENDS_${PN}-gtk2 = "freeciv-common freeciv-client-common"
RPROVIDES_${PN}-gtk2 = "freeciv-client"
FILES_${PN}-gtk2 = "\
${bindir}/freeciv-gtk2 \
${datadir}/freeciv/themes/gui-gtk-2.0 \
${datadir}/freeciv/gtk_menus.xml \
"
