#include "m_pd.h"
#include "math.h"

/* -------------------------- ceil -------------------------- */
static t_class *ceil_class;

typedef struct {
	t_object obj;
	t_float f;
} t_ceil;

static void ceil_bang(t_ceil *x) {
	outlet_float(x->obj.ob_outlet ,ceil(x->f));
}

static void ceil_float(t_ceil *x ,t_float f) {
	outlet_float(x->obj.ob_outlet ,ceil(x->f=f));
}

static void *ceil_new(t_floatarg f) {
	t_ceil *x = (t_ceil *)pd_new(ceil_class);
	outlet_new(&x->obj ,&s_float);
	x->f = f;
	return (x);
}

void ceil_setup(void) {
	ceil_class = class_new(gensym("ceil")
		,(t_newmethod)ceil_new ,0
		,sizeof(t_ceil) ,0
		,A_DEFFLOAT ,0);
	class_addbang  (ceil_class ,ceil_bang);
	class_addfloat (ceil_class ,ceil_float);
}
