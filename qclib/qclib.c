/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 erysdren (it/she)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 ******************************************************************************/

/*
 * headers
 */

/* std */
#include <stdio.h>
#include <string.h>

/* qcvm */
#include "qcvm.h"

/* qclib */
#include "qclib.h"

/* print text */
void qclib_print(qcvm_t *qcvm)
{
	int i;

	for (i = 0; i < qcvm_get_argc(qcvm); i++)
	{
		fprintf(stdout, "%s", qcvm_get_parm_string(qcvm, i));
	}

	fflush(stdout);
}

qcvm_export_t export_print =
{
	.func = qclib_print,
	.name = "print",
	.type = QCVM_VOID,
	.argc = 2,
	.args[0] = {.name = "s", .type = QCVM_STRING},
	.args[1] = {.name = "...", .type = QCVM_VARGS}
};

/* spawn entity */
void qclib_spawn(qcvm_t *qcvm)
{
	qcvm_return_entity(qcvm, qcvm_add_entity(qcvm));
}

qcvm_export_t export_spawn =
{
	.func = qclib_spawn,
	.name = "spawn",
	.type = QCVM_ENTITY,
	.argc = 0
};

/* get length of string */
void qclib_strlen(qcvm_t *qcvm)
{
	qcvm_return_float(qcvm, (float)strlen(qcvm_get_parm_string(qcvm, 0)));
}

qcvm_export_t export_strlen =
{
	.func = qclib_strlen,
	.name = "strlen",
	.type = QCVM_FLOAT,
	.argc = 1,
	.args[0] = {.name = "s", .type = QCVM_STRING}
};

/* return a concat of two strings */
void qclib_strcat(qcvm_t *qcvm)
{
	/* variables */
	const char *s[8];
	char buf[512];
	char *ptr;
	int i;

	ptr = buf;

	/* print strings */
	for (i = 0; i < qcvm_get_argc(qcvm); i++)
	{
		s[i] = qcvm_get_parm_string(qcvm, i);
		sprintf(ptr, "%s", s[i]);
		ptr += strlen(s[i]);
	}

	qcvm_return_string(qcvm, buf);
}

qcvm_export_t export_strcat =
{
	.func = qclib_strcat,
	.name = "strcat",
	.type = QCVM_STRING,
	.argc = 3,
	.args[0] = {.name = "s1", .type = QCVM_STRING},
	.args[1] = {.name = "s2", .type = QCVM_STRING},
	.args[2] = {.name = "...", .type = QCVM_VARGS}
};

/* float to string */
void qclib_ftos(qcvm_t *qcvm)
{
	/* variables */
	float f;
	char buf[64];

	/* get parms */
	f = qcvm_get_parm_float(qcvm, 0);

	/* sprintf */
	if (f == (int)f)
		sprintf(buf, "%d", (int)f);
	else
		sprintf(buf, "%0.4f", f);

	/* return */
	qcvm_return_string(qcvm, buf);
}

qcvm_export_t export_ftos =
{
	.func = qclib_ftos,
	.name = "ftos",
	.type = QCVM_STRING,
	.argc = 1,
	.args[0] = {.name = "f", .type = QCVM_FLOAT}
};

/* vector to string */
void qclib_vtos(qcvm_t *qcvm)
{
	/* variables */
	qcvm_vec3 v;
	char buf[64];

	/* get parms */
	v = qcvm_get_parm_vector(qcvm, 0);

	/* sprintf */
	sprintf(buf, "%0.4f %0.4f %0.4f", v.x, v.y, v.z);

	/* return */
	qcvm_return_string(qcvm, buf);
}

qcvm_export_t export_vtos =
{
	.func = qclib_vtos,
	.name = "vtos",
	.type = QCVM_STRING,
	.argc = 1,
	.args[0] = {.name = "v", .type = QCVM_VECTOR}
};

/* get substring */
void qclib_substring(qcvm_t *qcvm)
{
	/* variables */
	char buf[512];
	int start;
	int len;
	const char *str;

	/* get parms */
	str = qcvm_get_parm_string(qcvm, 0);
	start = (int)qcvm_get_parm_float(qcvm, 1);
	len = (int)qcvm_get_parm_float(qcvm, 2);

	/* copy string */
	memcpy(buf, str + start, len);

	/* return */
	qcvm_return_string(qcvm, buf);
}

qcvm_export_t export_substring =
{
	.func = qclib_substring,
	.name = "substring",
	.type = QCVM_STRING,
	.argc = 3,
	.args[0] = {.name = "s", .type = QCVM_STRING},
	.args[1] = {.name = "start", .type = QCVM_FLOAT},
	.args[2] = {.name = "len", .type = QCVM_FLOAT}
};

/* install qclib default builtin functions */
void qclib_install(qcvm_t *qcvm)
{
	qcvm_add_export(qcvm, &export_print);
	qcvm_add_export(qcvm, &export_spawn);
	qcvm_add_export(qcvm, &export_strlen);
	qcvm_add_export(qcvm, &export_strcat);
	qcvm_add_export(qcvm, &export_substring);
	qcvm_add_export(qcvm, &export_vtos);
	qcvm_add_export(qcvm, &export_ftos);
}
