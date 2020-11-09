#include "music.h"

/* -------------------------- chrd -------------------------- */
static t_class *chrd_class;

typedef struct _chrd {
	t_music z;
	unsigned all:1;  /* all-outlets toggle */
	unsigned midi:1; /* midi-note toggle */
	t_outlet **outs; /* outlets */
} t_chrd;

static void chrd_midi(t_chrd *y ,t_floatarg f) {
	y->midi = f;
}

static void chrd_all(t_chrd *y ,t_floatarg f) {
	y->all = f;
}

static double chrd_note(t_music *x ,int d) {
	if (!d) return x->flin.fp[0];
	int n = x->siz - (x->siz > 1);
	int i = (d - (d>0)) % n ,neg = i<0;
	i += n * neg + 1;
	t_float step = x->flin.fp[i];
	return (x->oct * ((d - !neg)/n - neg) + x->flin.fp[0] + step);
}

static void chrd_float(t_chrd *y ,t_float f) {
	t_music *x = &y->z;
	int d = f;
	double nte = chrd_note(x ,d);
	if (f != d)
	{	int dir = f<0 ? -1 : 1;
		double nxt = chrd_note(x ,d+dir);
		nte += dir * (f-d) * (nxt-nte);   }
	int n = x->flin.ninlets-1 ,i = (d - (d>0)) % n;
	i += (i<0)*n + 1;
	if (!d) i = 0;
	outlet_float(y->outs[i] ,y->midi ? nte : ntof(&x->note ,nte));
}

static void chrd_bang(t_chrd *y) {
	t_music *x = &y->z;
	int n = x->siz ,i = x->flin.ninlets;
	i = y->all ? i : (n>i ? i : n);
	for (t_outlet **op = y->outs+i; op-- ,i--;)
	{	double nte = chrd_note(x ,i);
		outlet_float(*op ,y->midi ?
			nte : ntof(&x->note ,nte));   }
}

static void *chrd_new(t_symbol *s ,int ac ,t_atom *av) {
	int n = (ac<3 ? 3 : ac);
	t_chrd *y = (t_chrd *)music_new(chrd_class ,n);
	t_music *x = &y->z;

	y->outs = (t_outlet **)getbytes(x->flin.ninlets * sizeof(t_outlet *));
	t_float *fp = x->flin.fp;
	t_outlet **op = y->outs;
	fp[0]=69 ,fp[1]=7 ,fp[2]=12;

	for (int i=0; n--; op++,fp++,i++)
	{	*op = outlet_new(&x->flin.x_obj ,&s_float);
		floatinlet_new(&x->flin.x_obj ,fp);
		if (i<ac) *fp = atom_getfloat(av++);   }

	return (y);
}

static void chrd_free(t_chrd *y) {
	t_music *x = &y->z;
	flin_free(&x->flin);
	freebytes(y->outs ,x->flin.ninlets * sizeof(t_outlet *));
}

void chrd_setup(void) {
	chrd_class = music_setup(gensym("chrd")
		,(t_newmethod)chrd_new ,(t_method)chrd_free ,sizeof(t_chrd));
	class_addbang(chrd_class ,chrd_bang);
	class_addfloat(chrd_class ,chrd_float);
	class_addmethod(chrd_class ,(t_method)chrd_midi
		,gensym("midi") ,A_FLOAT ,0);
	class_addmethod(chrd_class ,(t_method)chrd_all
		,gensym("all") ,A_FLOAT ,0);
}
