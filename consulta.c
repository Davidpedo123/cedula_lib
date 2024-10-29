#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char** formatear_cedula(PyObject* args) {
    PyObject* arg;

    // Parsear los argumentos de Python
    if (!PyArg_ParseTuple(args, "O", &arg)) {
        return NULL;
    }

    // Verificar si el argumento es una lista de cadenas
    if (PyList_Check(arg)) {
        int num_items = PyList_Size(arg);
        char** resultado = (char**) malloc((num_items + 1) * sizeof(char*));

        // Recorrer cada elemento de la lista
        for (int i = 0; i < num_items; i++) {
            PyObject* item = PyList_GetItem(arg, i);
            if (!PyUnicode_Check(item)) {
                PyErr_SetString(PyExc_TypeError, "Todos los elementos de la lista deben ser cadenas.");
                return NULL;
            }
            const char* cedula = PyUnicode_AsUTF8(item);

            // Quitar caracteres no numéricos y contar la longitud real de la cédula
            char cedula_limpia[12];  // Suficiente para 11 caracteres + '\0'
            int j = 0;
            for (int k = 0; cedula[k] != '\0' && j < 11; k++) {
                if (isdigit(cedula[k])) {
                    cedula_limpia[j++] = cedula[k];
                }
            }
            cedula_limpia[j] = '\0';

            // Verificar la longitud de la cédula limpia
            int cedula_len = strlen(cedula_limpia);
            if (cedula_len == 10) {
                // Agregar un '0' al principio si la cédula tiene 10 caracteres
                memmove(cedula_limpia + 1, cedula_limpia, 10);
                cedula_limpia[0] = '0';
                cedula_len = 11;
            } else if (cedula_len != 11) {
                PyErr_SetString(PyExc_ValueError, "Cada cédula en la lista debe tener exactamente 11 caracteres o ser ajustable a 10 con un '0' al principio.");
                return NULL;
            }

            // Formatear la cédula con guiones en posiciones específicas
            resultado[i] = (char*) malloc(14 * sizeof(char));  // Ajustar tamaño del buffer a 14 caracteres
            sprintf(resultado[i], "%c%c%c-%c%c%c%c%c%c%c-%c",
                    cedula_limpia[0], cedula_limpia[1], cedula_limpia[2],
                    cedula_limpia[3], cedula_limpia[4], cedula_limpia[5],
                    cedula_limpia[6], cedula_limpia[7], cedula_limpia[8],
                    cedula_limpia[9], cedula_limpia[10]);

        }

        resultado[num_items] = NULL; // Marcar el final del arreglo de cadenas
        return resultado;
    } else {
        PyErr_SetString(PyExc_TypeError, "Se esperaba una lista de cadenas.");
        return NULL;
    }
}

// Función de Python que llama a formatear_cedula
static PyObject* cedula_formatear_cedula(PyObject* self, PyObject* args) {
    char** cedulas_formateadas = formatear_cedula(args);
    if (cedulas_formateadas == NULL) {
        return NULL;
    }

    // Crear una lista de Python para almacenar las cédulas formateadas
    PyObject* resultado = PyList_New(0);

    // Recorrer las cédulas formateadas y agregarlas a la lista de Python
    for (int i = 0; cedulas_formateadas[i] != NULL; i++) {
        PyObject* cedula_py = Py_BuildValue("s", cedulas_formateadas[i]);
        PyList_Append(resultado, cedula_py);
        free(cedulas_formateadas[i]);
    }

    free(cedulas_formateadas); // Liberar la memoria de la lista de cédulas formateadas
    return resultado;
}

// Definición de los métodos del módulo
static PyMethodDef cedula_methods[] = {
    {"formatear_cedula", cedula_formatear_cedula, METH_VARARGS, "Formatea una cédula."},
    {NULL, NULL, 0, NULL}
};

// Definición de la estructura del módulo
static struct PyModuleDef cedula_module = {
    PyModuleDef_HEAD_INIT,
    "cedula_lib",
    "Módulo en C para formatear cédulas.",
    -1,
    cedula_methods
};

// Función de inicialización del módulo
PyMODINIT_FUNC PyInit_cedula_lib(void) {
    return PyModule_Create(&cedula_module);
}