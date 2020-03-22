#include <iostream>
#include <Python.h>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Python function called by Cpp!" << endl;

    //这一条代码很重要，决定用cpp程序会调用哪一个环境下的python解释器
    Py_SetPythonHome(L"C:/Users/YueJian/Anaconda3"); 
    // 初始化Python环境
    Py_Initialize();

    // 判断初始化是否成功  
    if (!Py_IsInitialized())
    {
        cout << "Initialize failed ..." << endl;
        // 关闭 Python 脚本解释器，释放内存。
        Py_Finalize();
        return -1;
    }

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;

    // 添加模块路径,相当于把python文件的路径加入环境变量
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('E:\\Cpp_example\\CppCallPython')");
    //打印当前执行环境当中的环境变量
    PyRun_SimpleString("print(sys.path)");

    // 导入模块
    pModule = PyImport_ImportModule("DemoForCpp");
    if (!pModule) // 检查模块是否导入成功
    {
        cout << "Python file import failed ..." << endl;
        Py_Finalize();
        return -1;
    }
    else
    {
        // 导入函数
        pFunc = PyObject_GetAttrString(pModule, "run"); //python 脚本里的函数名
        if (!pFunc) // 检查函数是否导入成功
        {
            cout << "Function import failed ..." << endl;
            Py_Finalize();
            return -1;
        }

        //C++类型转换为python类型
        PyObject* pParams = Py_BuildValue("(s)", "Michael");

        char* result;

        pArg = PyEval_CallObject(pFunc, pParams); // 调用函数
           //获取结果，python类型转换为C++类型。
        PyArg_Parse(pArg, "s", &result);

        cout << result << endl;
    }

    Py_Finalize();

    return 0;
}