#include<iostream>
using namespace std;
class HighGui
{
public:
	HighGui(){}
	~HighGui(){}
	void firstPage()
	{
		cout << "1.Create a gate(or a port).\n";
		cout << "2.Connect two gates.\n";
		cout << "3.Disconnect two gates.\n";
		cout << "4.Run the program.\n";
		cout << "5.Display the gate.\n";
		cout << "6.Clear all connection.\n";
		cout << "7.Set the port sign.\n";
		cout << "8.Rename the port name.\n";
		cout << "9.Quit.\n";
		cout << "\n\nType your choice.\n";
	}
	void setPort()
	{
		cout << "Please write the id of port and the 0 or 1 level.\n";
		cout << "eg: 12 0\n";
	}
	void gateCreatePage()
	{
		cout << "1.Create a and_gate.\n";
		cout << "2.Create an or_gate.\n";
		cout << "3.Create a not_gate.\n";
		cout << "4.Create a xor_gate.\n";
		cout << "5.Create a port.\n";
	}
	void gateConnectPage()
	{
		cout << "Connect two gates like\n";
		cout << "For example:\n";
		cout << "Gate : A->out connect B->input_1 The id of A is 5 ,the id of B is 3,the port id(only 0 or 1) of B is 1\n";
		cout << "You needs type:\n";
		cout << "5 3 1\n";
	}
	void gateDisconnect()
	{
		cout << "Disconnect two gates like\n";
		cout << "For example:\n";
		cout << "Gate : A->out connect B->input_0\n";
		cout << "You needs type id of A,id of B ,input port id of B\n";
	}
	void clear()
	{
		system("cls");
	}
};