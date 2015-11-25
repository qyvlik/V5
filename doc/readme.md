# 编译单元

编译单元是一个文件。除非声明文件为静态链接库，否则，会重新构建多次。

函数式编程。

一个文件中，可以拥有普通变量，函数。

要防止循环引用。

# 变量类型

支持 `variant`，或者明确指明变量类型。

# 函数声明

```
function z() {
    return "";
}

function z() -> string {
    return "";
}
```

以上两种声明均可，可以不声明返回值类型。

函数不支持同名函数重载。

不支持原型。

# 数据类型

## 基本数据类型

int
double 
real, float
bool

## 复杂数据类型

string
list
map
var
function

## 对象

object
