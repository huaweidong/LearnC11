#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
/*
[capture_block](parameters) mutable exception_specification->return_type{ body }
捕捉块(catpure block): 指定如何捕捉所在作用域中的变量，并供给lambda主体使用。

参数(parameter): (可选)lambda表达式使用的参数列表。只有在不使用任何参数，并且没有自定mutable、一个exception_specification 和一个return_type的情况下可以忽略该列表，返回类型在某些情况下也是可以忽略的，详见对return_type的说明：eg: [] {return 10;}
参数列表和普通函数的参数列表类似，区别如下：
参数不能有默认值。
不允许变长参数列表。
不允许未命名的参数。

mutable：（可选）如果所在作用域的变量是通过值捕捉到，那么lambda表达式主体中可以使用这些变量的副本。这些副本默认标记为const，因此lambda表达式的主体不能修改这些副本的值。如果lambda表达式标记为mutable，那么这些副本则不是const，因此主体可以修改这些本地副本。

exception_specification：（可选）用于指定lambda可以抛出的异常。

return_type：（可选）返回值的类型。如果忽略了return_type，那么编译器会根据以下原则判断返回类型：

如果lambda表达式主体的形式为{return expression;}那么表达式return_type的类型为expression的类型。

其他情况下的return_type为void。

*/

/* 将Lambda用作返回值
这个函数的主体部分创建了一个lambda表达式，这个lambda表达式通过值捕捉所在作用域的变量，并返回一个整数，这个返回的整数是传给multiplyBy2Lambda()的值的两倍。这个multiplyBy2Lambda()函数的返回值类型为 function<int(void)>，即一个不接受参数并返回一个整数的函数。函数主体中定义的lambda表达式正好匹配这个原型。变量x通过值捕捉，因此，在lambda表达式从函数返回之前，x值的一份副本绑定至lambda表达式中的x。
*/
function<int(void)> multplyBy2Lambda(int x)
{
    return [=]()->int{return 2*x;};
}
/*
mutiplyBy2Lambda()示例通过值捕捉了变量x:[=]。假设这个函数重写为通过引用捕捉变量：[&],则代码不能正常工作。
lambda表达式会在程序后面执行，而不会在mutiplyBy2Lambda()函数的作用域中执行，在那里x的引用不再有效。
*/

/*将lambda表达式用作参数
*/
void testCallBack(const vector<int>& vec, const function<bool(int)>& callback)
{
    for(auto i : vec)
    {
        if(!callback(i)) {
            break;
        }
        cout << i << " ";
    }
}

int main()
{
    [] {cout << "Hello from Lambda" << endl; } ();  // 尾部的()，这对括号使得这个lambda表达式立即执行

    string result = [](const string& str) -> string { return "Hello from " + str; }("second Lambda");
    cout << result << endl;
    // 这个例子中的返回值可以忽略
    //string result = [](const string & str){ return "Hello from " + str; }("second Lambda");

    // 还可以保存lambda表达式的指针，并且通过函数指针执行这个lambda表达式。
    auto fn = [](const string& str) { cout <<  "Hello from " + str << endl;};
    fn("world");
    fn("hello");
    /* Output
    Hello from Lambda
Hello from second Lambda
Hello from world
Hello from hello
    */

    /*
    捕捉块
    lambda表达式的方括号部分称为lambda捕捉块(capture block)，在这里可以指定如何从所在作用域中捕捉变量。捕捉变量的意思是可以在lambda表达式主体中使用这个变量。有两种方式：

[=]：通过值捕捉所有变量

[&]：通过引用捕捉所有变量

指定空白的捕捉块[]表示不从所在作用域中捕捉变量。还可以酌情决定捕捉那些变量以及这些变量的捕捉方法，方法是指定一个捕捉列表，其中带有可选的默认捕捉选项。前缀为&的变量通过引用捕捉。不带前缀的变量通过值捕捉。
    */
    
    auto fn2 = multplyBy2Lambda(5);
    cout << fn2() << endl;

    vector<int> vec(10);
    int index = 0;
    generate(vec.begin(), vec.end(), [&index]{return ++index; });
    for_each(vec.begin(), vec.end(), [](int i) { cout << i << " ";});
    testCallBack(vec, [](int i) { return i < 6;});

    return 0;
}
