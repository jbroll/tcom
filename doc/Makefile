# $Id$

all: tcom.n.html server.html

tcom.n.html: tcom.n.xml xslt.tcl refentry2html.xsl
	tclsh xslt.tcl tcom.n.xml refentry2html.xsl $@

server.html: server.xml xslt.tcl article2html.xsl
	tclsh xslt.tcl server.xml article2html.xsl $@
