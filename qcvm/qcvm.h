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

#pragma once
#ifndef _QCVM_H_
#define _QCVM_H_

/*
 *
 * types
 *
 */

/* qcvm runtime */
typedef struct qcvm_runtime qcvm_t;

/* export */
typedef void (*qcvm_export_t)(qcvm_t *qcvm);

/* vector */
typedef struct qcvm_vec3
{
	float x, y, z;
} qcvm_vec3;

/*
 *
 * functions
 *
 */

/*
 * qcvm_bootstrap.c
 */

/* open progs.dat file and return qcvm runtime handle */
qcvm_t *qcvm_open(const char *filename);

/* destroy qcvm runtime handle */
void qcvm_close(qcvm_t *qcvm);

/*
 * qcvm_utils.c
 */

/* set various parameter types */
void qcvm_set_parm_vector(qcvm_t *qcvm, int parm, float a, float b, float c);
void qcvm_set_parm_int(qcvm_t *qcvm, int parm, int val);
void qcvm_set_parm_float(qcvm_t *qcvm, int parm, float val);

/* get various parameter types */
int qcvm_get_argc(qcvm_t *qcvm);
qcvm_vec3 qcvm_get_parm_vector(qcvm_t *qcvm, int parm);
const char *qcvm_get_parm_string(qcvm_t *qcvm, int parm);
int qcvm_get_parm_int(qcvm_t *qcvm, int parm);
float qcvm_get_parm_float(qcvm_t *qcvm, int parm);

/* return various types to previous function */
void qcvm_return_string(qcvm_t *qcvm, const char *s);
void qcvm_return_vector(qcvm_t *qcvm, float a, float b, float c);
void qcvm_return_int(qcvm_t *qcvm, int val);
void qcvm_return_float(qcvm_t *qcvm, float val);

/* search all functions in the qcvm and return its function number if found */
int qcvm_get_function(qcvm_t *qcvm, const char *name);

/* add export to qcvm */
void qcvm_add_export(qcvm_t *qcvm, qcvm_export_t export);

/*
 * qcvm_runtime.c
 */

/* execute qcvm runtime loop */
void qcvm_run(qcvm_t *qcvm, int func);

#endif /* _QCVM_H_ */
