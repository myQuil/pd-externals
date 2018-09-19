# Makefile for myQwil

  lib.name = myQwil

# <> >< #<> #><
# #+ #- #* #/ #> #<
# #== #!= #>= #<=
# #| #|| #& #&&
# #<< #>> #% #^
  class.sources = muse.c chrd.c rand.c rind.c ntof.c fton.c sploat.c gloat.c \
	logb.c 0x23logb.c graid.c same.c ceil.c radx.c !.c !~.c 0x5e.c \
	0x3c0x3e.c 0x3e0x3c.c 0x230x3c0x3e.c 0x230x3e0x3c.c \
	0x230x2b.c 0x230x2d.c 0x230x2a.c 0x230x2f.c 0x230x3e.c 0x230x3c.c \
	0x230x3d0x3d.c 0x230x210x3d.c 0x230x3e0x3d.c 0x230x3c0x3d.c \
	0x230x7c.c 0x230x7c0x7c.c 0x230x26.c 0x230x260x26.c \
	0x230x3c0x3c.c 0x230x3e0x3e.c 0x230x25.c 0x230x5e.c \
	0x23min.c 0x23max.c 0x23pow.c 0x23div.c 0x23mod.c \
	0x400x2d.c 0x400x25.c 0x40div.c 0x40mod.c 0x400x2f.c 0x40pow.c \
	0x400x3c0x3c.c 0x400x3e0x3e.c

  datafiles = !~-help.pd !-help.pd ^-help.pd 2^.pd ad.pd ad~.pd adac~.pd \
	ceil-help.pd cpt.pd cupq.pd cupqb.pd cupqbl.pd fkick~.pd fmbloc~.pd \
	freqm~.pd graid-help.pd chrd-help.pd hotbinops1-help.pd hotbinops2-help.pd \
	hotbinops3-help.pd logb-help.pd manscratch.pd mantissa.pd mantissal.pd \
	mantouch.pd mantr.pd mix~.pd muse-help.pd ne-aliases-help.pd ntof-help.pd \
	pad.pd pad~.pd radx-help.pd rand-help.pd revbinops-help.pd rind-help.pd \
	ruse-help.pd same-help.pd sound.pd sploat-help.pd \
	README.md LICENSE.md

  include Makefile.pdlibbuilder
