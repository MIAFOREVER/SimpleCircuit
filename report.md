# 实验报告
## 运算符重载
...
## 继承
使用了Gate作为基类 AndGate,OrGate,NotGate,XorGate,Port为派生类.
## 多态
Gate 作为抽象类,仅仅定义接口
```
virtual string name() = 0;
virtual void connect(Gate*, int) = 0;
virtual void disconnect(Gate*, int) = 0;
virtual void run() = 0;
virtual node* getNode() = 0;
virtual void setPortState(int state) = 0;
virtual void printError(int errorNum) = 0;
virtual int getId() = 0;
virtual void setId(int num) = 0;
```
后面的AndGate,OrGate,NotGate,XorGate,Port派生类都用来实现接口
## 封装
封装......肯定封装了
## 异常
一个输出端可以连接多个输入端,但是一个输入端只能连接一个输出端!</br>电路如果短路会在运行那一步提示</br>
`The gate cause short circuit.`
