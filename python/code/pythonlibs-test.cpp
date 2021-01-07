#include <Python.h>
#include <iostream>
int main() {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(R"(sys.path.append('.'))");
    PyObject* pName = PyUnicode_DecodeFSDefault(R"(cmy-test)");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != NULL) {
        std::cout << "find it!" << std::endl;
        PyObject* pFunc = PyObject_GetAttrString(pModule, R"(add)");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* pArgs = PyTuple_New(2);
            PyObject* pValue = PyLong_FromLong(12);
            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyLong_FromLong(13);
            PyTuple_SetItem(pArgs, 1, pValue);
            pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue != NULL) {
                std::cout << PyLong_AsLong(pValue) << std::endl;
                Py_DECREF(pValue);
            } else {
                std::cout << "no return value!" << std::endl;
            }

            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            Py_DECREF(pArgs);

        } else {
            std::cout << "未找到函数" << std::endl;
        }
    } else {
        std::cout << "not find!" << std::endl;
    }

    return 0;
}